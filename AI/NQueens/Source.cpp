#include <iostream>
#include <vector>
#include "Board.h"

int main() {
    
    int boardSize = 8;
    Board board(boardSize);
    board.displayBoard();
    
    std::vector<int> queenIndex(boardSize + 2);
    
    // solve using hill climbing
   // nQueens(board, queenIndex);

    return 0;
}
