#include <iostream>
#include <vector>
#include <queue>

// GENERAL BFS SOLUTION, NO WATER JUG //

// @NOTE: 
// Heuristic value for the goal node should be zero.
// The algorithm heavily depends on the heuristic function and 
// hence if that is messed up, the algorithm's output / behaviour is 
// unpredictable. 

// @TODO: 
// Extend for N-ary children. Currently implementing for binary only.

struct Node {
private:
	char data;
	int heuristic;
	Node* left;
	Node* right;
public:
	Node() {}
	Node(char, int, Node*, Node*);
	~Node() {}
};

Node :: Node(char d, int h, Node* l, Node* r) {
	data = d;
	heuristic = h;
	left = l;
	right = r;
}

struct Tree {
private: // data
	Node* root;

private: //subroutines
	void _insert(Node*&, Node*);
	void _walk(Node*);
	//void _search(const Node*&, char);
public: 
	Tree()  { std::cout << "\n Tree Object Allocated. \n";   }
	~Tree() { std::cout << "\n Tree Object Deallocated. \n;" }
	Node* insert(char, int);
	void bestFirstSearch(Node*);
	void display(Node*);
};

// Insert - Exposed function to the user.
// @params: char d : data to be associated to the node.
//		  : int  v : heuristic to be associated to the node.
// function        : Basic null check, and call recursive private function.
//					 Only inserts unique values in the tree.
// returns		   : updated tree, with the new node inserted.
Node* Tree :: insert(char d, int v) {
	Node* in = new Node(d, v, nullptr, nullptr);

	if(root == nullptr)	root = in;
	else _insert(root, in);
	return root;
}

// Recursive Insert - private function
// @params: root : Root node of the tree
//        : in   : the node to be inserted
// function      : Follows the BST property and
//				   inserts the node in it's appropriate place.
// returns       : nil
void Tree :: _insert(Node*& root, Node* in) {
	if(in->data < root->data) {
		if(root->left == nullptr)
			root->left = in;
		else _insert(root->left, in);
	} else if(in->data > root->data) {
		if(root->right == nullptr)
			root->right = in;
		else _insert(root->right, in);
	} else std::cout << "\n  Tree only takes unique values.\n"
}

void Tree :: display(Node* root) {
	if(root == nullptr) return;
	else {
		display(root->left);
		std::cout << root->data << " : " << root->heuristic << "\n";
		display(root->right);
	}
	//else _walk();
}

// Recursive Walk  - private function
// @params : root :  Root node of the tree
// function       :  Inorder walk of the tree
// returns        :  nil
void Tree :: _walk(Node* root) {
	_walk(root->left);
	std::cout << root->data << " : " << root->heuristic << "\n";
	_walk(root->right);
}

//utility function
Node* pop_front(std::vector<Node*> vec) {
	Node* element = v.at(0);
	vec.erase(vec.begin());
	return element;
}

Node* findCurrentBest(std::vector<Node*> children) {
	Node* best = children.at(0);
	
	for(Node i : children) 
		if(i.heuristc < best.heuristic) 
			best = i;
			
	return best;
}

// find the best child //
// @NOTE: This is not greedy Best First Search. //
// In G-BFS, the decisions taken are not reversible,
// whereas in normal BFS, you can reverse (or perhaps)
// backtrack if you find a better solution at that point 
// of exploration //
void Tree :: bestFirstSearch(Node* root) {

	std::vector<Node*> path, open, children;
	// children is declared here instead of in the while
	// loop because we need to keep track of all the children
	// incase we find a better path 
	//std::queue<Node*> open; //do I need this?

	open.push_back(root);

	while(!open.empty()) {
		Node* current = open.front();
		path.push_back(current);
		open.pop_back(); 

		// generate successors step
		// @FIXME : Obviously this only works for binary trees
		// 		    once we make one for n-ary trees, this code 
		//		    will have to be extended to work for that case
		if(current->left) children.push_back(current->left);
		if(current->right) children.push_back(current->right);

		// find the best node from the children
		Node* bestNode = nullptr, *prevBestNode = nullptr; 
		// Common mistake, the pointer belongs to the name, not the 
		// dayatype in c++, which is stupid //
		bestNode = findCurrentBest(children);

		// @TODO: Handle a case where the {if} above don't get executed
		//        and the vector turns out empty. Which could mean 
		// 		  1. We reached the goal node (to confirm, check heuristic)
		//		  2. We reached a deadend, and we need to backtrack		


	}

} 

int main() {

	Tree* tree = new Tree;
	Node* root;

	root = tree->insert('B', 5);
	root = tree->insert('A', 4);
	root = tree->insert('D', 3);
	root = tree->insert('C', 2);
	root = tree->insert('E', 1);

	tree->display(root);

	std::cout << "\n";
	return 0;
}

// @TODO for BestFS
// If an invalid case is given as an input, it crashes
// This is probably because of the fact that we're not adding 
// previously generated nodes, and one case of failire is that
// all the nodes in the children vector is already generated, and 
// probably I don't have a case to handle that.
// the only thing that has to be done (probably) is that 
// return an empty vector, and if the vector returns empty, the
// input is invalid and there exists no solution
// check out input 6 2 3

// Handle target being greater than max(jug1, jug2)