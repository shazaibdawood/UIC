#include <iostream>
#include "piece.h"

using namespace std;

//const int N = 8; // this is now defined in piece.h

void displayBoard(Piece* board[N][N]) {
    cout << "  01234567  " << endl;
    cout << ' ' << '-';
    for (int c = 0; c < N; c++) {
        cout << '-';
    }
    cout << '-' << ' ' << endl;
    for (int r = 0; r < N; ++r) {
        cout << r << '|';
        for (int c = 0; c < N; ++c) {
            cout << board[r][c]->display();
        }
        cout << '|' << r;
        cout << endl;
    }
    cout << ' ' << '-';
    for (int c = 0; c < N; c++) {
        cout << '-';
    }
    cout << '-' << ' ';;
    cout << endl;
    cout << "  01234567  " << endl;
}

void movePiece(Piece* board[N][N], int begRow, int begCol, int endRow, int endCol) {
    //---------------------------------------------------------------------------------------------
    // TODO: write the movePiece() function
    //
    //       movePiece() should move the piece from (begRow,begCol) on the board
    //                                           to (endRow,endCol)
    //                                                                     
    //       moving a piece on the board involves careful memory management:
    //          - free up the space on the board where the piece will move to
    //          - rewire the piece that is being moved to its new location on the board
    //          - construct a new empty space piece and wire it to the spot the moved piece vacated
    //---------------------------------------------------------------------------------------------

    delete board[endRow][endCol];

    board[endRow][endCol] = board[begRow][begCol];

    board[endRow][endCol]->setRow(endRow);
    board[endRow][endCol]->setCol(endCol);

    board[begRow][begCol] = new Space(begRow, begCol);
}

  
        

int main() {

    Piece* chessBoard[N][N];

    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
            chessBoard[r][c] = new Space(r,c);
        }
    }

    delete chessBoard[1][1];
    chessBoard[1][1] = new Pawn(1,1);
    delete chessBoard[7][4];
    chessBoard[7][4] = new Pawn(7,4);
    delete chessBoard[1][6];
    chessBoard[1][6] = new Pawn(1,6);
    delete chessBoard[5][6];
    chessBoard[5][6] = new Pawn(5,6);
    delete chessBoard[3][1];
    chessBoard[3][1] = new Knight(3,1);
    delete chessBoard[6][2];
    chessBoard[6][2] = new Queen(6,2);
    delete chessBoard[3][3];
    chessBoard[3][3] = new King(3,3);
    delete chessBoard[5][4];
    chessBoard[5][4] = new Bishop(5,4);
    delete chessBoard[2][5];
    chessBoard[2][5] = new Rook(2,5);

    cout << endl;
    cout << "The chess board:" << endl << endl;
    displayBoard(chessBoard);
    cout << endl;

    int begRow = -1, begCol = -1;
    int endRow = -1, endCol = -1;

    cout << "Which piece do you want to move?" << endl;
    while (begRow < 0 || begRow >= N) {
        cout << "   Enter the position row (0-7): ";
        cin >> begRow;
        cout << endl;
    }
    while (begCol < 0 || begCol >= N) {
        cout << "   Enter the position column (0-7): ";
        cin >> begCol;
        cout << endl;
    }
    
    cout << "Where would you like to move the " << chessBoard[begRow][begCol]->display() << " piece to?" << endl;
    while (endRow < 0 || endRow >= N) {
        cout << "   Enter the position row (0-7): ";
        cin >> endRow;
        cout << endl;
    }
    while (endCol < 0 || endCol >= N) {
        cout << "   Enter the position column (0-7): ";
        cin >> endCol;
        cout << endl;
    }

    bool canItMove = false;
    
    //---------------------------------------------------------------------------------------------
    // TODO: check if the piece at (begRow, begCol) on chessBoard 
    //         can legally move to (endRow, endCol)
    //       if it is a legal move, then set canItMove = true and print out:
    //          The <pieceChar> piece at (<begRow>,<begCol>) CAN be moved to (<endRow>,<endCol>)
    //              ex: The Q piece at (6,2) CAN be moved to (3,5)
    //       if it is NOT a legal move, then set canItMove = false and print out:
    //          The <pieceChar> piece at (<begRow>,<begCol>) CANNOT be moved to (<endRow>,<endCol>)
    //              ex: The Q piece at (6,2) CANNOT be moved to (3,4)
    //---------------------------------------------------------------------------------------------

    cout << endl;
    if(chessBoard[begRow][begCol]->isMoveLegal(endRow, endCol)){
        canItMove = true;
        cout << "The " << chessBoard[begRow][begCol]->display() << " piece at (" << chessBoard[begRow][begCol]->getRow() << "," << chessBoard[begRow][begCol]->getCol() << ") CAN be moved to (" << endRow << "," << endCol << ")" << endl;
    } else {
        cout << "The " << chessBoard[begRow][begCol]->display() << " piece at (" << chessBoard[begRow][begCol]->getRow() << "," << chessBoard[begRow][begCol]->getCol() << ") CANNOT be moved to (" << endRow << "," << endCol << ")" << endl;
    }

    if (canItMove) {
        movePiece(chessBoard,begRow,begCol,endRow,endCol);
        cout << "The updated chess board:" << endl << endl;
        displayBoard(chessBoard);
        cout << endl;
    }


    //--------------------------------------------------------------
    // TODO: free all the memory allocated for the chessBoard pieces
    //--------------------------------------------------------------

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            delete chessBoard[i][j];
        }
    }
    return 0;
}
