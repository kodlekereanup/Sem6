#include <iostream>
#include <map>
#include <vector>
#include <queue>

// TODO: 
// Review the heuristic function
// Review the 'No Solution' condition     
// Uses the Hill Climbing Approch for path selection
// Uses BestFS for successor selection

/*
PRODUCTION RULES
1.
(0, 0) = (jug1, 0)
(0, 0) = (0, jug2)

2.
(jug1, 0) = (jug1, jug2)
(0, jug2) = (jug1, jug2)

3.
(X, Y) = (X + SOME Z, Y - Z )
	X < JUG1
	Y <= JUG2
	X + Z <= JUG1
	
(X, Y) = (X - Z, Y + SOME Z)
	Y < JUG2
	X <= JUG1
	Y + Z <= JUG2
	
4.
(X, Y) = (0, Y)
(X, Y) = (X, 0)

5.
(X, 0) = (X, J2)
	X < J1
(0, Y) = (J1, Y)
	Y < J2

*/

std::vector<std::pair<int, int>> generateStates(int j1, int j2, std::pair<int, int> curr,
														std::map<std::pair<int, int>, bool>& gen) {
	
	std::vector<std::pair<int, int>> children;
	// generate all possible states
	// use the production rules for the same
	// if a state which is aleady visited is generated, skip

	if (curr.first == 0 && curr.second == 0) {
		children.push_back({ j1, 0 });
		gen[{ j1, 0 }] = true;

		children.push_back({ 0, j2 });
		gen[{ 0, j2 }] = true;
	}
	if (curr.first == j1 && curr.second == 0) {
		if (!gen[{ j1, j2}]) {
			children.push_back({ j1, j2 });
			gen[{ j1, j2 }] = true;
		}
	}
	if (curr.first == 0 && curr.second == j2) {
		if (!gen[{ j1, j2}]) {
			children.push_back({ j1, j2 });
			gen[{ j1, j2 }] = true;
		}
	}
	// y to x
	if (curr.first != j1 && curr.second != 0) {
		
		/*
		if (curr.first == 0) {
			// becomes production number 5
			if (!gen[{j1, curr.second}]) {
				children.push_back({ j1, curr.second });
				gen[{j1, curr.second}] = true;
			}
		} */
		{

			int x = curr.first; int y = curr.second;
			//std::cout << "\n X: " << x << " Y: " << y << "\n";

			while (y > 0 && x < j1) {
				x++; y--;
			}

			//std::cout << "\n X: " << x << " Y: " << y << "\n";

			if (!gen[{x, y}]) {
				children.push_back({ x, y });
				gen[{ x, y }] = true;
			}
		}
	}
	// x to y
	if (curr.first != 0 && curr.second != j2) {

		if (curr.second == 0) {
			// becomes production number 5
			if (!gen[{curr.first, j2}]) {
				children.push_back({ curr.first, j2 });
				gen[{curr.first, j2}] = true;
			}
		}
		else {

			int x = curr.first; int y = curr.second;

			while (x > 0 && y < j2) {
				y++; 
				x--;
			}
			//std::cout << "\n X: " << x << " Y: " << y << "\n";
			if (!gen[{x, y}]) {
				children.push_back({ x, y });
				gen[{ x, y }] = true;
			}
		}
	}
	if (curr.first != 0 && curr.second != 0) {
		// how to decide which one to empty?
		if (!gen[{ 0, curr.second }]) {
			children.push_back({ 0, curr.second });
			gen[{ 0, curr.second }] = true;
		}
		else if (!gen[{ curr.first, 0 }]) {
			children.push_back({ curr.first, 0 });
			gen[{ curr.first, 0  }] = true;
		}
	}

	return children;
}

std::vector<std::pair<int, int>> BestFirstSearch(int jug1, int jug2, int goal) {

	bool goalReached = false;
	std::map<std::pair<int, int>, bool> generated;
	std::vector<std::pair<int, int>> path; // final path

	std::queue<std::pair<int, int>> q; // manage states
	q.push({ 0 , 0 }); // initialize to inital state
	generated[{ 0, 0 }] = true;

	while (!q.empty()) {

		std::pair<int, int> currentState = q.front();
		q.pop();
		path.push_back(currentState);

		// find all the children states
		std::vector<std::pair<int, int>> children = generateStates(jug1, jug2, currentState, generated);

		// BUG? 
		// children will be empty in two cases
		// 1. the node has no children, but what does this mean? -- is this even possible?
		// 2. the possible children are aleady generated and hence no
		//    pushbacks were called, so empty.

		// Check if children vector is empty instead of doing 
		// the above thing. If the children vector is empty it means
		// none of the push backs in the generateStates() function 
		// were applied and so the vector is empty 
		if(children.empty()) {
			std::cout << "NO SOLUTION\n";
			goalReached = false;
			path.clear();
			break;
		}

		// heuristics
		std::pair<int, int> best;
		int trap = goal * jug1;
		int min = abs((children.at(0).first * jug1 + children.at(0).second * jug2));
		best = children.at(0);
		

		for (std::pair<int, int> i : children) {
			int inMin = abs((i.first * jug1 + i.second * jug2));

			// find which min is closer to goal
			if (inMin < min) {
				min = inMin;
				best = i;
			}

			// solution is found, no need to generate more children
			if (best.first == goal && best.second == 0) {
				goalReached = true;
				path.push_back(best);
				break;
			}
		}

		if (goalReached) break;
		else q.push(best);

	}

	return path;
}

int main() {

	int jug1, jug2, goal;

	std::cout << "\n Enter capacity of Jug1 and Jug2:";
	std::cin >> jug1 >> jug2;
	std::cout << "\n Enter Goal:";
	std::cin >> goal;

	std::vector<std::pair<int, int>> path = BestFirstSearch(jug1, jug2, goal);
	if(!path.empty()) 
		for (std::pair<int, int> i : path) std::cout << "(" << i.first << ", " << i.second << ")\n";
	
	//_getch();
	return 0;
}
