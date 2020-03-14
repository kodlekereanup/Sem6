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
	* _UpDirection_:    (i - 1, j) | value(i - 1, j) != -1
	* _DownDirection_:  (i + 1, j) | value(i + 1, j) != -1
	* _LeftDirection_:  (i, j - 1) | value(i, j - 1) != -1
	* _RightDirection_: (i, j + 1) | value(i, j + 1) != -1
	* _LeftDiag_      : Assign Slope = -1
	* _RigthDiag_     : Assign Slope = +1

