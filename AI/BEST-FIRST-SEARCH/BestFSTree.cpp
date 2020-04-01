#include <iostream>

struct Node {
	char data;
	int heuristic;
	Node* left;
	Node* right;

	Node() {};
	Node(char, int, Node*, Node*);
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
	//Tree() { root = new Node; }
	Node* insert(char, int);
	void bestFirstSearch();
	void display(Node*);
};

Node* Tree :: insert(char d, int v) {
	Node* in = new Node(d, v, nullptr, nullptr);

	if(root == nullptr)	root = in;
	else _insert(root, in);
	return root;
}

void Tree :: _insert(Node*& root, Node* in) {
	if(in->data < root->data) {
		if(root->left == nullptr)
			root->left = in;
		else _insert(root->left, in);
	} else if(in->data > root->data) {
		if(root->right == nullptr)
			root->right = in;
		else _insert(root->right, in);
	}
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

void Tree :: _walk(Node* root) {
	_walk(root->left);
	std::cout << root->data << " : " << root->heuristic << "\n";
	_walk(root->right);
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