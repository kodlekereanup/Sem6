#include <vector>
#include <iostream>

class Board {
    public:
        int n = 8;
        std::vector<std::vector<int>> board;

        Board();
        // Initialize N x N grid (matrix) with 0's
        // Add padding of -1s all around the board
        void displayBoard();
};

Board :: Board() {
    
    std::cout << "\n Enter the size of the board:";
    std::cin >> n;

    std::vector<int> pad(n + 2, -1); 
    board.push_back(pad);
    for(int i = 0; i < n; i++) { 
        std::vector<int> te;
        te.push_back(-1);
        for(int j = 0; j < n; j++)
            te.push_back(0);
        te.push_back(-1);
        board.push_back(te);
    }
    board.push_back(pad);

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

