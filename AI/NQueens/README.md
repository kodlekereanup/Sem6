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

* The Board probably should have padding of -1's all around it to make sure the piece doesn't 
	go out of the board boundary

* For any (i, j):
	* UpDirection:    (i - 1, j) | value(i - 1, j) != -1
	* DownDirection:  (i + 1, j) | value(i + 1, j) != -1
	* LeftDirection:  (i, j - 1) | value(i, j - 1) != -1
	* RightDirection: (i, j + 1) | value(i, j + 1) != -1
	* LeftDiag      : Assign Slope = -1
	* RigthDiag     : Assign Slope = +1

