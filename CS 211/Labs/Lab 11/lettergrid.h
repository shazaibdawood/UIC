/*lettergrid.h*/

// 
// Starter code written by Prof. Scott Reckinger
// Univeristy of Illinois, Chicago
//

//
// LetterGrid
//
// The LetterGrid class provides a grid (2D array) abstraction.
// The size set in the constructor cannot change.  
// All elements are initialized to a whitespace ' '
//
// Example usage:
//   LetterGrid  M;  // 4x4 grid, initialized to ' '
//   LetterGrid  G(6,7); // 6 rows, 7 columns
//   M = G; // M is now an identical copy of G
//   setCellValue(1,2,'X'); // sets the element (1,2) to 'X'
//   char let = getCellValue(1,2); // let is a copy of element (1,2)

#pragma once

#include <iostream>
#include <exception>
#include <stdexcept>
#include <algorithm>

using namespace std;

class LetterGrid {
private:
    struct ROW {
        char*  Cols;     // dynamic array of column elements
        size_t NumCols;  // total # of columns (0..NumCols-1)
    };

    ROW* Rows;        // dynamic array of ROWs
    size_t  NumRows;  // total # of rows (0..NumRows-1)
    
public:
    //
    // default constructor:
    //
    // Called automatically to construct a 4x4 grid.  
    // All elements are initialized to a whitespace ' '.
    // Example usage:
    //   LetterGrid  M;  // 4x4 grid, initialized to ' '
    //
    //--------------------------------------------------------
    // TODO (warm-up): provide descriptive comments to show 
    //                 full understanding of the code for 
    //                 the constructor
    //--------------------------------------------------------
    LetterGrid() {
        Rows = new ROW[4];  // allocates memory for 4 rows.
        NumRows = 4; // sets number of rows to 4

        for (size_t r = 0; r < NumRows; ++r) { // loops numRow times
            Rows[r].Cols = new char[4]; // allocates for columns
            Rows[r].NumCols = 4;

            for (size_t c = 0; c < Rows[r].NumCols; ++c) {
                Rows[r].Cols[c] = ' ';  // init each column to whitespace
            }
        }
    }

    //
    // parameterized constructor:
    //
    // Called automatically to construct a grid  
    // with R rows, where each row has C columns. 
    // All elements are initialized to a whitespace ' '.
    // Example usage:
    //   LetterGrid  G(6,7); // 6 rows, 7 columns
    //
    //--------------------------------------------------------
    // TODO (warm-up): provide descriptive comments to show 
    //                 full understanding of the code for 
    //                 the parameterized constructor
    //--------------------------------------------------------
    LetterGrid(size_t R, size_t C) {
        if (R < 1) { // fails if size of rows is < 1 
            throw invalid_argument("LetterGrid::constructor: # of rows");
        }
        if (C < 1) { // fails if size of columns is < 1 
            throw invalid_argument("LetterGrid::constructor: # of cols");
        }
        
        Rows = new ROW[R]; // allocates memory or given rows   
        NumRows = R; // sets rows to given rows

        for (size_t r = 0; r < NumRows; ++r) { // loops thru each row
            Rows[r].Cols = new char[C]; // allocates memory or columns in each row
            Rows[r].NumCols = C;

            for (size_t c = 0; c < Rows[r].NumCols; ++c) { // loops thru columns
                Rows[r].Cols[c] = ' '; // sets them to whitespace  
            }
        }
    }


    //
    // copy constructor:
    //
    // Called automatically to construct a grid that contains a 
    // copy of an existing grid.  
    // Example usage: passing a LetterGrid as a parameter-by-value
    //
    //  void somefunction(LetterGrid G2) // <--- G2 is a copy of G
    //  { ... }
    //
    //  void main() {
    //      LetterGrid G;
    //      ...
    //      somefunction(G);
    //  }
    //
    //--------------------------------------------------------
    // TODO (warm-up): provide descriptive comments to show 
    //                 full understanding of the code for 
    //                 the copy constructor
    //--------------------------------------------------------
    LetterGrid(const LetterGrid& other) {
        this->Rows = new ROW[other.NumRows]; // allocates memory for rows of new array  
        this->NumRows = other.NumRows; // set numRows from other

        for (size_t r = 0; r < other.NumRows; ++r) { // go thru each row of other
            size_t other_numcols = other.Rows[r].NumCols;
            // get num of columns from other 
            this->Rows[r].Cols = new char[other_numcols]; // allocate memory for columns of row
            this->Rows[r].NumCols = other_numcols;
            // set num of columns
            for (size_t c = 0; c < other_numcols; ++c) { // loop thru each column and copy values
                this->Rows[r].Cols[c] = other.Rows[r].Cols[c];
            }
        }
    }
    
    //
    // copy operator=:
    //
    // Called automatically when one object is assigned into another.
    //
    // Example usage:
    //   LetterGrid  M;  // 4x4 grid, initialized to ' '
    //   LetterGrid  G(6,7); // 6 rows, 7 columns
    //   M = G; // M is now an identical copy of G
    //
    //--------------------------------------------------------
    // TODO (warm-up): provide descriptive comments to show 
    //                 full understanding of the code for 
    //                 the assignment operator =
    //--------------------------------------------------------
    LetterGrid& operator=(const LetterGrid& other) {
        if (this == &other) { // check for self-assignment
            return *this;
        }
        
        for (size_t r = 0; r < NumRows; ++r) {
            delete[] Rows[r].Cols; // free column memory
        }
        delete[] Rows; // free row memory
        
        this->Rows = new ROW[other.NumRows];  // same as copy constructor
        this->NumRows = other.NumRows;
        
        for (size_t r = 0; r < other.NumRows; ++r) {
            size_t other_numcols = other.Rows[r].NumCols;
            
            this->Rows[r].Cols = new char[other_numcols];
            this->Rows[r].NumCols = other_numcols;
            
            for (size_t c = 0; c < other_numcols; ++c) {
                this->Rows[r].Cols[c] = other.Rows[r].Cols[c];
            }
        }
        return *this;
    }

    //
    // destructor:
    //
    // Called automatically to free the memory associated 
    //  with a LetterGrid object when it goes out of scope
    //
    //--------------------------------------------------------
    // TODO (warm-up): provide descriptive comments to show 
    //                 full understanding of the code for 
    //                 the assignment operator =
    //--------------------------------------------------------
    virtual ~LetterGrid() {
        for (size_t r = 0; r < NumRows; ++r) {
            delete[] Rows[r].Cols; // free columns
        }
        delete[] Rows; // free rows
    }

    //
    // output
    //
    // Outputs the contents of the grid.
    //
    //--------------------------------------------------------
    // TODO (warm-up): provide descriptive comments to show 
    //                 full understanding of the code for 
    //                 the output method
    //--------------------------------------------------------
    void output() const {
        for (size_t r = 0; r < NumRows; ++r) { // loop through row
            cout << "| "; // print |
            for (size_t c = 0; c < Rows[r].NumCols; ++c) { // loop through columns
                cout << Rows[NumRows-r-1].Cols[c] << " | ";
            }
            cout << endl; // go to next line
        }
    }


    //
    // numrows()
    //
    // This getter returns the # of rows in the LetterGrid.  
    //  The indices for these rows are 0..numrows-1.
    //
    size_t numrows() const {
        //--------------------------------------------------------
        // TODO (task I): write numrows()
        //--------------------------------------------------------
        return NumRows; //modify this line
    }
  

    //
    // numcols()
    //
    // This getter returns # of columns in row r of the LetterGrid.  
    //  The indices for these columns are 0..numcols-1.  
    //  Note that the # of columns can be different row-by-row 
    //  since "jagged" rows are supported, i.e. LetterGrids are 
    //  not necessarily rectangular, despite all provided 
    //  constructors only creating rectangular grids
    //  
    size_t numcols(size_t r) const {
        //--------------------------------------------------------
        // TODO (task I): write numcols(); throw an error for 
        //                invalid input values of r 
        //--------------------------------------------------------
        if (r < 0 || r >= NumRows) {
            throw invalid_argument("LetterGrid::numcols: # of rows");
        }
        return Rows[r].NumCols; //modify this line
    }


    //
    // size()
    //
    // This getter returns the total # of elements in the LetterGrid.
    //  Note that the # of columns can be different row-by-row 
    //  since "jagged" rows are supported, i.e. LetterGrids are 
    //  not necessarily rectangular, despite all provided 
    //  constructors only creating rectangular grids
    //  
    size_t size() const {
        //--------------------------------------------------------
        // TODO (task I): write size(); make sure to handle 
        //                non-rectangular grids 
        //--------------------------------------------------------
        int count = 0;
        for(int i = 0; i < NumRows; i++){
            count += Rows[i].NumCols;
        }
        return count; //modify this line
    }


    //
    // setCellValue()
    //
    // This setter sets the element at location (r,c) to <value>
    //
    //  Example usage:
    //    setCellValue(1,2,'X'); // sets the element (1,2) to 'X'
    //
    void setCellValue (size_t r, size_t c, char value) {
        //--------------------------------------------------------
        // TODO (task I): write setCellValue(); throw errors for 
        //                invalid input values of r or c
        //--------------------------------------------------------

        if (r < 0 || r >= NumRows) {
            throw invalid_argument("LetterGrid::numcols: # of rows");
        }
        if(c < 0 || c >= Rows[r].NumCols){
            throw invalid_argument("LetterGrid::numcols: # of rows");
        }

        Rows[r].Cols[c] = value;
    }

    //
    // getCellValue()
    //
    // This getter returns the characters at location (r,c)
    //
    //  Example usage:
    //   char let = getCellValue(1,2); // let is a copy of element (1,2)
    //
    char getCellValue (size_t r, size_t c) const {
        //--------------------------------------------------------
        // TODO (task I): write getCellValue(); throw errors for 
        //                invalid input values of r or c
        //--------------------------------------------------------
        if (r < 0 || r >= NumRows) {
            throw invalid_argument("LetterGrid::numcols: # of rows");
        }
        if(c < 0 || c >= Rows[r].NumCols){
            throw invalid_argument("LetterGrid::numcols: # of rows");
        }

        return Rows[r].Cols[c]; //modify this line
    }

};
