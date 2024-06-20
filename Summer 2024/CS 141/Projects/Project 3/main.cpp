///  @brief CS 141 Project - Word Search
///  @author [Shazaib Dawood]
///  @date May 25, 2024
///  CS 141 Summer 2024, Professor Koehler

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

// The puzzle will always have exactly 20 columns
const int numCols = 20;

// reads in the 2D array puzzle and word bank from file input
void readPuzzle(char puzzle[][numCols], string wordBank[], const string &filename,
    int numRows, int numWords);

// Searches the entire puzzle, but may use helper functions to implement logic
void searchPuzzle(const char puzzle[][numCols], const string wordBank[], 
    vector <string> &discovered, int numRows, int numWords);

// Printer function that outputs a vector
void printVector(const vector <string> &v);
    
// Helper Functions
bool searchNorth(int x, int y, int numRows, string word, const char puzzle[][numCols]);
bool searchSouth(int x, int y, int numRows, string word, const char puzzle[][numCols]);
bool searchEast(int x, int y, int numRows, string word, const char puzzle[][numCols]);
bool searchWest(int x, int y, int numRows, string word, const char puzzle[][numCols]);
bool searchNEast(int x, int y, int numRows, string word, const char puzzle[][numCols]);
bool searchNWest(int x, int y, int numRows, string word, const char puzzle[][numCols]);
bool searchSEast(int x, int y, int numRows, string word, const char puzzle[][numCols]);
bool searchSWest(int x, int y, int numRows, string word, const char puzzle[][numCols]);


int main()
{
    int numRows = 1, numWords = 1;
    string filename;
    // Acquire the filename from userinput and open it for reading
    cout << "Enter file name: " << endl;
    cin >> filename;

    // Testing "toystory_puzzle.txt"
    // filename = "toystory_puzzle.txt";

    // Grab the array row dimension and amount of words from the file
    ifstream inFS;
    inFS.open(filename);
    if(!inFS.is_open())
    {
        cout << "File not opened" << endl;
        return -1;
    }

    cout << "File successfully opened" << endl;
    inFS >> numRows;
    inFS >> numWords;
    inFS.close();

    // declare a 2D array
    char puzzle[numRows][numCols];

    // create a 1D array for words
    string wordBank[numWords];
  
    // Implement function (below) to build the puzzle
    readPuzzle(puzzle, wordBank, filename, numRows, numWords); 

    cout << endl;
    cout << "\t\t\t\t\t" << "Words to be found:" << endl;
    for(int i = 0; i < numWords; i++)
    {
        cout << wordBank[i] << " ";
    }
    cout << endl;

    cout << endl;
    for(int i = 0; i < numRows; i++)
    {
        for(int j = 0; j < numCols; j++)
        {
            cout << puzzle[i][j] << " ";
        }
        cout << endl;
    }
    
    // set up discovery vector
    vector <string> discovered;

    // Search for Words
    // Implement function (below) to search and find words in the puzzle
    //       You should probably also implement helper functions to properly
    //       decompose your program and reduce its complexity.
    searchPuzzle(puzzle, wordBank, discovered, numRows, numWords);    

    // Sort vector
    // Not needed in this particular case as wordBank is written in alphabetical order.
    sort(discovered.begin(), discovered.end());

    // Print vector of discovered words
    printVector(discovered);

    return 0;
}

// Implement the buildPuzzle function using file IO to fill the 2D array 
//       and word bank based on the contents in the file provided as an argument.
// Hint: Use dummy variables to skip over initial portion of the file you already
//       read in previously.
void readPuzzle(char puzzle[][numCols], string wordBank[], const string &filename,
    int numRows, int numWords)
{
    ifstream inFS;
    inFS.open(filename);
    if(!inFS.is_open())
    {
        cout << "File not opened" << endl;
        return;
    }

    inFS >> numRows;
    inFS >> numWords;

    for(int i = 0; i < numRows; i++)
    {
        for(int j = 0; j < numCols; j++)
        {
            inFS >> puzzle[i][j];
        }
    }

    for(int i = 0; i < numWords; i++)
    {
        inFS >> wordBank[i];
    }
    inFS.close();
}

/// @ brief: iterate over every character in direction of travel until 
///          character doesn't match with characters in the word being searched for or index is out of bounds. 
///          If all characters match then return true or else return false as soon as either conditons are false.
/// @ param - x: int of current row
/// @ param - y: int of current column
/// @ param - numRows: int of the number of rows in 2d array
/// @ param - word: current word in wordBank being searched for
/// @ param - puzzle: 2d char array
bool searchWest(int x, int y, int numRows, string word, const char puzzle[][numCols])
{
    int wordLen = word.size();

    for(int i = 0; i < wordLen; i++)
    {
        if(y > numCols || puzzle[x][y] != word[i])
        {
            return false;
        }
        y++;
    }

    return true;
}

/// @ brief: iterate over every character in direction of travel until 
///          character doesn't match with characters in the word being searched for or index is out of bounds. 
///          If all characters match then return true or else return false as soon as either conditons are false.
/// @ param - x: int of current row
/// @ param - y: int of current column
/// @ param - numRows: int of the number of rows in 2d array
/// @ param - word: current word in wordBank being searched for
/// @ param - puzzle: 2d char array
bool searchNorth(int x, int y, int numRows, string word, const char puzzle[][numCols])
{
    int wordLen = word.size();

    for(int i = 0; i < wordLen; i++)
    {
        if(x < 0 || puzzle[x][y] != word[i])
        {
            return false;
        }
        x--;
    }

    return true;
}

/// @ brief: iterate over every character in direction of travel until 
///          character doesn't match with characters in the word being searched for or index is out of bounds. 
///          If all characters match then return true or else return false as soon as either conditons are false.
/// @ param - x: int of current row
/// @ param - y: int of current column
/// @ param - numRows: int of the number of rows in 2d array
/// @ param - word: current word in wordBank being searched for
/// @ param - puzzle: 2d char array
bool searchEast(int x, int y, int numRows, string word, const char puzzle[][numCols])
{
    int wordLen = word.size();

    for(int i = 0; i < wordLen; i++)
    {
        if(y < 0 || puzzle[x][y] != word[i])
        {
            return false;
        }
        y--;
    }

    return true;
}

/// @ brief: iterate over every character in direction of travel until 
///          character doesn't match with characters in the word being searched for or index is out of bounds. 
///          If all characters match then return true or else return false as soon as either conditons are false.
/// @ param - x: int of current row
/// @ param - y: int of current column
/// @ param - numRows: int of the number of rows in 2d array
/// @ param - word: current word in wordBank being searched for
/// @ param - puzzle: 2d char array
bool searchSouth(int x, int y, int numRows, string word, const char puzzle[][numCols])
{
    int wordLen = word.size();

    for(int i = 0; i < wordLen; i++)
    {
        if(x > numRows || puzzle[x][y] != word[i])
        {
            return false;
        }
        x++;
    }

    return true;
}

/// @ brief: iterate over every character in direction of travel until 
///          character doesn't match with characters in the word being searched for or index is out of bounds. 
///          If all characters match then return true or else return false as soon as either conditons are false.
/// @ param - x: int of current row
/// @ param - y: int of current column
/// @ param - numRows: int of the number of rows in 2d array
/// @ param - word: current word in wordBank being searched for
/// @ param - puzzle: 2d char array
bool searchNWest(int x, int y, int numRows, string word, const char puzzle[][numCols])
{
    int wordLen = word.size();

    for(int i = 0; i < wordLen; i++)
    {
        if(x < 0 || y > numCols || puzzle[x][y] != word[i])
        {
            return false;
        }
        x--;
        y++;
    }

    return true;
}

/// @ brief: iterate over every character in direction of travel until 
///          character doesn't match with characters in the word being searched for or index is out of bounds. 
///          If all characters match then return true or else return false as soon as either conditons are false.
/// @ param - x: int of current row
/// @ param - y: int of current column
/// @ param - numRows: int of the number of rows in 2d array
/// @ param - word: current word in wordBank being searched for
/// @ param - puzzle: 2d char array
bool searchNEast(int x, int y, int numRows, string word, const char puzzle[][numCols])
{
    int wordLen = word.size();

    for(int i = 0; i < wordLen; i++)
    {
        if(x < 0 || y < 0 || puzzle[x][y] != word[i])
        {
            return false;
        }
        x--;
        y--;
    }

    return true;
}

/// @ brief: iterate over every character in direction of travel until 
///          character doesn't match with characters in the word being searched for or index is out of bounds. 
///          If all characters match then return true or else return false as soon as either conditons are false.
/// @ param - x: int of current row
/// @ param - y: int of current column
/// @ param - numRows: int of the number of rows in 2d array
/// @ param - word: current word in wordBank being searched for
/// @ param - puzzle: 2d char array
bool searchSWest(int x, int y, int numRows, string word, const char puzzle[][numCols])
{
    int wordLen = word.size();

    for(int i = 0; i < wordLen; i++)
    {
        if(x > numRows || y > numCols || puzzle[x][y] != word[i])
        {
            return false;
        }
        x++;
        y++;
    }

    return true;
}

/// @ brief: iterate over every character in direction of travel until 
///          character doesn't match with characters in the word being searched for or index is out of bounds. 
///          If all characters match then return true or else return false as soon as either conditons are false.
/// @ param - x: int of current row
/// @ param - y: int of current column
/// @ param - numRows: int of the number of rows in 2d array
/// @ param - word: current word in wordBank being searched for
/// @ param - puzzle: 2d char array
bool searchSEast(int x, int y, int numRows, string word, const char puzzle[][numCols])
{
    int wordLen = word.size();

    for(int i = 0; i < wordLen; i++)
    {
        if(x > numRows || y < 0 || puzzle[x][y] != word[i])
        {
            return false;
        }
        x++;
        y--;
    }

    return true;
}

// Implement searchPuzzle and any helper functions you choose to create
/// @ brief: iterate over each word in the wordBank.
///          for each word iterate over each character in puzzle.
///          call the helper functions for each character in puzzle.
///          if any of the helper functions are true then add the word being searched for into the discovered vector.
/// @ param - puzzle: 2d char array
/// @ param - wordBank: Array of words to be found in the 2d array
void searchPuzzle(const char puzzle[][numCols], const string wordBank[], 
    vector <string> &discovered, int numRows, int numWords)
{
    for(int i = 0; i < numWords; i++)
    {
        for(int x = 0; x < numRows; x++)
        {
            for(int y = 0; y < numCols; y++)
            {
                if(searchWest(x, y, numRows, wordBank[i], puzzle))
                {
                    discovered.push_back(wordBank[i]);
                }
                else if(searchNorth(x, y, numRows, wordBank[i], puzzle))
                {
                    discovered.push_back(wordBank[i]);
                }
                else if(searchEast(x, y, numRows, wordBank[i], puzzle))
                {
                    discovered.push_back(wordBank[i]);
                }
                else if(searchSouth(x, y, numRows, wordBank[i], puzzle))
                {
                    discovered.push_back(wordBank[i]);
                }
                else if(searchNWest(x, y, numRows, wordBank[i], puzzle))
                {
                    discovered.push_back(wordBank[i]);
                }
                else if(searchNEast(x, y, numRows, wordBank[i], puzzle))
                {
                    discovered.push_back(wordBank[i]);
                }
                else if(searchSWest(x, y, numRows, wordBank[i], puzzle))
                {
                    discovered.push_back(wordBank[i]);
                }
                else if(searchSEast(x, y, numRows, wordBank[i], puzzle))
                {
                    discovered.push_back(wordBank[i]);
                }
            }
        }
    }
}

// Implement printVector
void printVector(const vector <string> &v)
{
    cout << endl;
    cout << "\t\t\t\t\t" << "Words found:" << endl;
    for(int i = 0; i < v.size(); i++)
    {
        cout << v.at(i) << endl;
    }
}