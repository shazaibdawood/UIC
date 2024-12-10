#ifndef _PIECE_H
#define _PIECE_H

const int N = 8;

using namespace std;

// First, the Piece abstract base class 

class Piece {

    public:  
        Piece() {} // default contstructor (do nothing)
        Piece(int r, int c) { // parameterized contstructor 
            setRow(r);
            setCol(c);
        } 
        virtual ~Piece() {} // destructor (do nothing)
        
        virtual char display( ) = 0; // pure virtual function
        virtual bool isMoveLegal(int newRow, int newCol) = 0; // pure virtual function
    
        int getRow() {return myRow;}
        void setRow(int row) {myRow = row;}
        int getCol() {return myCol;}
        void setCol(int col) {myCol = col;}
        
    private:
        int myRow; // current row for this piece on the gameboard
        int myCol; // current column for this piece on the gameboard

}; // Piece (abstract base class)


// then, all the derived subtype classes


class King : public Piece {
    
    public:  
        King(int r, int c) { // parameterized contstructor 
            setRow(r);
            setCol(c);
        } 
        virtual ~King() {} // destructor (do nothing)
        
        char display() {
            return 'K';
        }

        bool isMoveLegal(int newRow, int newCol) {
            
            //-----------------------------
            // TODO: write this function
            //-----------------------------
            if(display() != 'K'){
                return false;
            }
            if(newRow < 0 || newRow >= N || newCol < 0 || newCol >= N){
                return false;
            }
            if(getRow() == newRow && getCol() == newCol){
                return false;
            }

            int rowCalc = abs(newRow - getRow());
            int colCalc = abs(newCol - getCol());

            return rowCalc <= 1 && colCalc <= 1;
        } 

}; // King


class Queen : public Piece {
    
    public:  
        Queen(int r, int c) { // parameterized contstructor 
            setRow(r);
            setCol(c);
        } 
        virtual ~Queen() {} // destructor (do nothing)
        
        char display() {
            return 'Q';
        }

        bool isMoveLegal(int newRow, int newCol) {
            
            //-----------------------------
            // TODO: write this function
            //-----------------------------
            
            if(display() != 'Q'){
                return false;
            }
            if(newRow < 0 || newRow >= N || newCol < 0 || newCol >= N){
                return false;
            }
            if(getRow() == newRow && getCol() == newCol){
                return false;
            }

            int rowCalc = abs(newRow - getRow());
            int colCalc = abs(newCol - getCol());

            return (rowCalc == colCalc) || (newRow == getRow() && newCol != getCol()) || (newRow != getRow() && newCol == getCol());
            } 

}; // Queen


class Rook : public Piece { // parameterized contstructor 
    
    public:  
        Rook(int r, int c) {
            setRow(r);
            setCol(c);
        } 
        virtual ~Rook() {} // destructor (do nothing)
        
        char display() {
            return 'R';
        }

        bool isMoveLegal(int newRow, int newCol) {
            
            //-----------------------------
            // TODO: write this function
            //-----------------------------
            
            if(display() != 'R'){
                return false;
            }
            if(newRow < 0 || newRow >= N || newCol < 0 || newCol >= N){
                return false;
            }
            if(getRow() == newRow && getCol() == newCol){
                return false;
            }

            // int rowCalc = abs(newRow - getRow());
            // int colCalc = abs(newCol - getCol());

            return (newRow == getRow() && newCol != getCol()) || (newRow != getRow() && newCol == getCol());
            
        } 

}; // Rook


class Bishop : public Piece {
    
    public:  
        Bishop(int r, int c) { // parameterized contstructor 
            setRow(r);
            setCol(c);
        }  
        virtual ~Bishop() {} // destructor (do nothing)
        
        char display() {
            return 'B';
        }

        bool isMoveLegal(int newRow, int newCol) {
            
            //-----------------------------
            // TODO: write this function
            //-----------------------------
            
            if(display() != 'B'){
                return false;
            }
            if(newRow < 0 || newRow >= N || newCol < 0 || newCol >= N){
                return false;
            }
            if(getRow() == newRow && getCol() == newCol){
                return false;
            }

            int rowCalc = abs(newRow - getRow());
            int colCalc = abs(newCol - getCol());

            return (rowCalc == colCalc);
            
        } 

}; // Bishop


class Knight : public Piece {
    
    public:  
        Knight(int r, int c) { // parameterized contstructor 
            setRow(r);
            setCol(c);
        } 
        virtual ~Knight() {} // destructor (do nothing)
        
        char display() {
            return 'N';
        }

        bool isMoveLegal(int newRow, int newCol) {
            
            //-----------------------------
            // TODO: write this function
            //-----------------------------

            if(display() != 'N'){
                return false;
            }
            if(newRow < 0 || newRow >= N || newCol < 0 || newCol >= N){
                return false;
            }
            if(getRow() == newRow && getCol() == newCol){
                return false;
            }

            int rowCalc = abs(newRow - getRow());
            int colCalc = abs(newCol - getCol());

            return (rowCalc == 2 && colCalc == 1) || (rowCalc == 1 && colCalc == 2);
        } 

}; // Knight


class Pawn : public Piece {
    
    public:  
        Pawn(int r, int c) { // parameterized contstructor 
            setRow(r);
            setCol(c);
        } 
        virtual ~Pawn() {} // destructor (do nothing)
        
        char display() {
            return 'P';
        }

        bool isMoveLegal(int newRow, int newCol) {
            
            //-----------------------------
            // TODO: write this function
            //-----------------------------
            
            if(display() != 'P'){
                return false;
            }
            if(newRow < 0 || newRow >= N || newCol < 0 || newCol >= N){
                return false;
            }
            if(getRow() == newRow && getCol() == newCol){
                return false;
            }

            return (newCol == getCol() && newRow == 1 + getRow());
        } 

}; // Pawn


class Space : public Piece {
    
    public:  
        Space(int r, int c) { // parameterized contstructor 
            setRow(r);
            setCol(c);
        } 
        virtual ~Space() {} // destructor (do nothing)
        
        char display() {
            return ' ';
        }

        bool isMoveLegal(int newRow, int newCol) {
            return false;
        } 

}; // Space

#endif //_PIECE_H