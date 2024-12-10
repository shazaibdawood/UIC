#include <iostream>
#include <cstdlib>
#include <ctime>    // Enables use of time() function
#include "lettergrid.h"

using namespace std;

// checkBoardForWin() should check the input <gameboard> for
//  a winning configuration for player <letter>, which occurs
//  when <letter> appears in a streak of length <len> along 
//  any row, column, or diagonal within <gameboard>.
//
//  Win (return true) examples for <letter> = 'X', <len> = 3:
//         [3x4 grid]            [3x3 grid]           [2x3 grid]
//      | X | O |   |   |       | X | O |   |       |   | O | O |      
//      | O | X | X |   |       | X | O |   |       | X | X | X |      
//      | O | O | X | O |       | X | O |   |      
//
//  No win (return false) examples for <letter> = 'X', <len> = 4:
//         [4x4 grid]            [4x3 grid]           [3x3 grid]
//      |   | O |   |   |       |   | O |   |       | O | O | O |      
//      | O | X | X |   |       | X | O |   |       | O | X | X |      
//      | O | O | X | O |       | X | O |   |       | X | X | X |
//      | O | X | X | X |       | X | O | X | 
//  

bool checkHorizontal(LetterGrid gameboard, int len, char letter){
    for(int i = 0; i < gameboard.numrows(); i++){
        int match = 0;
        for(int j = 0; j < gameboard.numcols(i); j++){
            if(gameboard.getCellValue(i, j) == letter){
                match++;
                if(match == len){
                    return true;
                }
            }
            else {
                match = 0;
            }
        }
    }
    return false;
}

bool checkVertical(LetterGrid gameboard, int len, char letter){
    for(int j = 0; j < gameboard.numcols(0); j++){
        int match = 0;
        for(int i = 0; i < gameboard.numrows(); i++){
            if(gameboard.getCellValue(i, j) == letter){
                match++;
                if(match == len){
                    return true;
                }
            }
            else {
                match = 0;
            }
        }
    }
    return false;
}

bool checkDiagonalDown(LetterGrid gameboard, int len, char letter){
    for(int i = 0; i <= gameboard.numrows() - len; i++){
        for(int j = 0; j <= gameboard.numcols(i) - len; j++){
            int match = 0;
            for(int k = 0; k < len; k++){
                if(gameboard.getCellValue(i + k, j + k) == letter){
                    match++;
                    if(match == len){
                        return true;
                    }
                }
                else {
                    break;
                }
            }
            
        }
    }
    return false;
}

bool checkDiagonalUp(LetterGrid gameboard, int len, char letter){
    for(int i = len - 1; i < gameboard.numrows(); i++){
        for(int j = 0; j <= gameboard.numcols(i) - len; j++){
            int match = 0;
            for(int k = 0; k < len; k++){
                if(gameboard.getCellValue(i - k, j + k) == letter){
                    match++;
                    if(match == len){
                        return true;
                    }
                }
                else {
                    break;
                }
            }
            
        }
    }
    return false;
}

bool checkBoardForWin(LetterGrid gameboard, int len, char letter) {
    //--------------------------------------------------------
    // TODO (task II): write the checkForWin() function, which
    //                 should likely be decomposed into 
    //                 multiple, additional functions;
    //       e.g. a function to check for horiztonal streaks,
    //            a function to check for vetical streaks, & 
    //            function(s) to check for diagonal streaks.
    //--------------------------------------------------------
    if(checkHorizontal(gameboard, len, letter) || checkVertical(gameboard, len, letter) || checkDiagonalDown(gameboard, len, letter) || checkDiagonalUp(gameboard, len, letter)){
        return true;
    }
    return false;
}

int main() {

    // Initial game board set up
    LetterGrid gameboard;
    int gameType = 0;
    while (gameType != 1 && gameType != 2) {
        cout << "Check a Tic-Tac-Toe board (enter 1) " << endl;
        cout << "   OR a ConnectFour board (enter 2):  ";
        cin >> gameType;
        cout << endl;
    }

    srand(time(0));  // Unique seed
    int winLength = 0;
    if (gameType == 1) { 
        // Building a random Tic-Tac-Toe game board
        winLength = 3;
        LetterGrid temp(3,3);
        gameboard = temp;

        int numTurns = rand() % 10;
        for (int i = 0; i < numTurns; ++i) {
            size_t r = rand() % 3;
            size_t c = rand() % 3;
            while (gameboard.getCellValue(r,c) != ' ') {
                r = rand() % 3;
                c = rand() % 3;
            }
            if (i % 2 == 0) {
                gameboard.setCellValue(r,c,'X');
            } else {
                gameboard.setCellValue(r,c,'O');
            }
        }
    } else if (gameType == 2) {
        // Building a random Connect-Four game board
        winLength = 4;
        LetterGrid temp(6,7);
        gameboard = temp;

        int numTurns = rand() % 43;
        for (int i = 0; i < numTurns; ++i) {
            size_t c = rand() % 7;
            while (gameboard.getCellValue(gameboard.numrows()-1,c) != ' ') {
                c = rand() % 7;
            }
            size_t r = 0;
            while (gameboard.getCellValue(r,c) != ' ') {
                r++;
            }
            if (i % 2 == 0) {
                gameboard.setCellValue(r,c,'X');
            } else {
                gameboard.setCellValue(r,c,'O');
            }
        }
    }

    // Display the game board
    gameboard.output();
    cout << endl;

    // Check if the two players have a winning configuration
    bool winX = checkBoardForWin(gameboard,winLength,'X');
    bool winO = checkBoardForWin(gameboard,winLength,'O');

    // Report a winner if there is a one
    if (winX && winO ) {
        cout << "Cannot determine winner." << endl;
    } else if (winX) {
        cout << "X wins!" << endl;
    } else if (winO) {
        cout << "O wins!" << endl;
    } else {
        cout << "There is no winner." << endl;
    }

    return 0;
}
