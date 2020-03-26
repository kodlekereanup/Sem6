#include <vector>
#include <iostream>

// The only job of this file is the generate the board

class Board {
    public:
        int n = 8;
        std::vector<std::vector<int>> board;

        // @param: nn: size of the board 
        Board(int nn);
        // Initialize N x N grid (matrix) with 0's
        void displayBoard();
	    void calCost(); //Heuristic function calculator
};

Board :: Board(int nn): n(nn) {
    
    for(int i = 0; i < n; i++) { 
        std::vector<int> te;
        for(int j = 0; j < n; j++)
            te.push_back(0);
        board.push_back(te);
    }

}

void Board :: displayBoard() {
    std::cout << "\n\n";
    for(std::vector<int> i : board) { 
        for(int j : i) 
            std::cout << j << " ";
        std::cout << "\n";
    }
    std::cout << "\n\n";
}


