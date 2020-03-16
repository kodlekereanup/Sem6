#include <vector>
#include <iostream>

class Board {
    public:
        int n = 8;
        std::vector<std::vector<int>> board;

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

/*
 * TODO: 
 * Generate heuristics initially
 * Check if number of attacka are 0
 * If not, move the pieces in such a way that it reduces the heuristics
 * If a dead end is reached, randomrestart
 *
 * MORE FORMAL ALGORITHM
 *
 * Set the board to a random state
 * calculate the heuristics in the current state
 * while(values in the board is not 0) 
 * 	move the pieces in such a way that it reduces the values
 * 	bring it closer to 0 in each step
 *
 * 	if at anu point a dead end is reached (define dead end)
 * 	then NQRandomRestart 
 *	
 * Print all solutions as we keep going, keep a flag to ensure no solution is repeated twice
 *
 * HEURISTIC FUNCTION:
 * 	At any position, check the number of attacking queens using
 * 	[ N(N-1) ] / 2
 *
 * 	We can classify the attacks into three:
 * 		HORIZONTAL ATTACK: When two or more queens are in the same row
 *		VERTICAL ATTACK:   When two or more queens are in the same column
 *		DIAGONAL ATTACK:
 *			LEFT DIAGONAL
 *			RIGHT DIAGONAL
 *
 * Calculate this value at every state, filling every square
 * Main aim is to reduce all these ints to zeros.
 *
 * For any N, the number of solutions is given by:
 * 	this seems a bit difficult than I thought
 *
 *
 */
