#include <fstream>
#include <iostream>
#include <string>
using namespace std;

struct node {
	node* left;
	node* right;
	int value;

	~node() {
		delete left;
		delete right;
	}
};

void insert(node** root, int v) {
	if (*root == nullptr) *root = new node { nullptr, nullptr, v };

	if (v == (*root)->value) return;
	else if (v < (*root)->value) insert(&(*root)->left, v);
	else insert(&(*root)->right, v);
}

void traverse(ofstream& out, node* root) {
	if (root == nullptr) return;
	out << root->value << endl;
	traverse(out, root->left);
	traverse(out, root->right);
}

int main()
{
	ifstream in{ "input.txt" };
	ofstream out{ "output.txt" };

	node* root = nullptr;
	string s; int v;
	while (getline(in, s)) {
		v = std::stoi(s);
		insert(&root, v);
	}

	traverse(out, root);
}