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

int min_tree(node* root) {
	if (root->left == nullptr) return root->value;
	return min_tree(root->left);
}

node* delete_tree(node* root, int v) {
	if (root == nullptr) return root;
	if (v < root->value) root->left = delete_tree(root->left, v);
	else if (v > root->value) root->right = delete_tree(root->right, v);
	else if (root->left != nullptr && root->right != nullptr) {
		root->value = min_tree(root->right);
		root->right = delete_tree(root->right, root->value);
	}
	else {
		if (root->left != nullptr) root = root->left;
		else if (root->right != nullptr) root = root->right;
		else root = nullptr;
	}
	return root;
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

	int dv;
	in >> dv;

	node* root = nullptr;
	string s; int v;

	while (getline(in, s)) {
		if (s == "") continue;
		v = std::stoi(s);
		insert(&root, v);
	}

	root = delete_tree(root, dv);
	traverse(out, root);
}