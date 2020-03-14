# Basic Idea: 
	Place queens in such a way that no other queen is in it's attacking field.

# Attacking Field: 
	If a queen is placed in ith row and jth column, no other queen should be placed
	in (i, j) and left, right diagonals.

## Left Diagonal for any (i, j)  : i == j
## Right Diagonal for any (i, j) : (i + j) / 2

* Board is a N x N  matrix of integers
* Integers represent the cost
* Every position where a queen is placed is represented by a 1.
* Store a vector that contains the indices of the queens' positions on the board, column-wise.

