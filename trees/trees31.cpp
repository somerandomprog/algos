#include <fstream>
#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

struct node {
	node* left;
	node* right;
	int value;

	int height = 0;
	int max_length = 0;

	int leaves = 0;
	int incoming = 0;
	int rooted = 0;

	~node() {
		delete left;
		delete right;
	}
};

void insert(node** root, int v) {
	if (*root == nullptr) *root = new node{ nullptr, nullptr, v };

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

void compute_height_length(node* node, int& max_length) {
	if (!node) return;
	compute_height_length(node->left, max_length);
	compute_height_length(node->right, max_length);

	if (!node->left && !node->right) {
		node->height = 0;
		node->max_length = 0;
		node->leaves = 1;
	}
	else if (!node->right) {
		node->height = node->left->height + 1;
		node->max_length = node->left->height + 1;
		node->leaves = node->left->leaves;
	}
	else if (!node->left) {
		node->height = node->right->height + 1;
		node->max_length = node->right->height + 1;
		node->leaves = node->right->leaves;
	}
	else {
		node->height = max(node->left->height, node->right->height) + 1;
		node->max_length = node->left->height + node->right->height + 2;
		node->leaves = node->left->height == node->right->height 
			? (node->left->leaves + node->right->leaves)
			: (node->left->height > node->right->height ? node->left->leaves: node->right->leaves);
	}

	max_length = max(max_length, node->max_length);
}

void compute_paths(node* root, node* node, int max_length) {
	if (!node) return;

	if (node->max_length < max_length) node->rooted = 0;
	else {
		if (node->left && node->right) node->rooted = node->left->leaves * node->right->leaves;
		else node->rooted = node->left ? node->left->leaves : node->right->leaves;
	}

	if (node == root) node->incoming = 0;
	if (node->left && node->right) {
		if (node->left->height != node->right->height) {
			node->left->incoming = node->left->height > node->right->height ? node->incoming + node->rooted : node->rooted;
			node->right->incoming = node->left->height > node->right->height ? node->rooted : node->incoming + node->rooted;
		}
		else {
			node->left->incoming = node->rooted + node->left->leaves * (node->incoming / node->leaves);
			node->right->incoming = node->rooted + node->right->leaves * (node->incoming / node->leaves);
		}
	}
	else if (node->left && !node->right) {
		node->left->incoming = node->incoming + node->rooted;
	}
	else if(!node->left && node->right) {
		node->right->incoming = node->incoming + node->rooted;
	}

	compute_paths(root, node->left, max_length);
	compute_paths(root, node->right, max_length);
}

void traverse_find(node* root, int& key) {
	if (!root) return;
	traverse_find(root->right, key);
	if ((root->incoming + root->rooted) % 2 == 1 && root->value > key) key = root->value;
	traverse_find(root->left, key);
}

int main() {
	ifstream in{ "tst.in" };
	ofstream out{ "tst.out" };

	node* root = nullptr;
	string s; int v;

	while (getline(in, s)) {
		if (s == "") continue;
		v = std::stoi(s);
		insert(&root, v);
	}

	int max_length = numeric_limits<int>::min(), key = numeric_limits<int>::min();
	compute_height_length(root, max_length);
	compute_paths(root, root, max_length);
	traverse_find(root, key);
	if (key != numeric_limits<int>::min()) root = delete_tree(root, key);

	traverse(out, root);
}