# Basic Idea: 
	Place queens in such a way that no other queen is in it's attacking field.

# Attacking Field: 
	If a queen is placed in ith row and jth column, no other queen should be placed
	in (i, j) and left, right diagonals.

## Left Diagonal for any (i, j)  : i == j
## Right Diagonal for any (i, j) : (i + j) == N - 1

* Board is a N x N  matrix of integers
* Integers represent the cost
* Every position where a queen is placed is represented by a 1.
* Store a vector that contains the indices of the queens' positions on the board, column-wise.

# Heuristic Function

What would be a good Heuristic Function?

## Aim

* Minimize Heuristic Functions such that No of Attacks = 0

# Notes

* Removed:The Board probably should have padding of -1's all around it to make sure the piece doesn't 
	go out of the board boundary

* For any (i, j):
	* *UpDirection*:    (i - 1, j) | value(i - 1, j) != -1
	* *DownDirection*:  (i + 1, j) | value(i + 1, j) != -1
	* *LeftDirection*:  (i, j - 1) | value(i, j - 1) != -1
	* *RightDirection*: (i, j + 1) | value(i, j + 1) != -1
	* *LeftDiag*      : Assign Slope = -1
	* *RigthDiag*     : Assign Slope = +1

# TODO

 * Generate heuristics initially
 * Check if number of attacka are 0
 * If not, move the pieces in such a way that it reduces the heuristics
 * If a dead end is reached, randomrestart
 
## MORE FORMAL ALGORITHM
 
 * Set the board to a random state
 * calculate the heuristics in the current state
 * while(values in the board is not 0) 
 	* 	move the pieces in such a way that it reduces the values
 	* 	bring it closer to 0 in each step
 
 	* 	if at anu point a dead end is reached (define dead end)
 * 	then NQRandomRestart 
 
 * Print all solutions as we keep going, keep a flag to ensure no solution is repeated twice
 
## HEURISTIC FUNCTION:
 * 	At any position, check the number of attacking queens using
 * 	[ N(N-1) ] / 2
 
 * 	We can classify the attacks into three:
 * 		HORIZONTAL ATTACK: When two or more queens are in the same row
 *		VERTICAL ATTACK:   When two or more queens are in the same column
 		DIAGONAL ATTACK:
 			LEFT DIAGONAL
 			RIGHT DIAGONAL
 
 * Calculate this value at every state, filling every square
 * Main aim is to reduce all these ints to zeros.
 
 * For any N, the number of solutions is given by:
  	this seems a bit difficult than I thought
 