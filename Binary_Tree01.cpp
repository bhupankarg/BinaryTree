#include <iostream>
#include <queue>
using namespace std;

class BinaryTree {
public:
	int data;
	BinaryTree* leftChild;
	BinaryTree* rightChild;
	BinaryTree() {}
	BinaryTree(int data) {
		this->data = data;
		leftChild = nullptr;
		rightChild = nullptr;
	}
	int insert_leaf_node(int);
	void pre_order_display(BinaryTree*);
	void in_order_display(BinaryTree*);
	void post_order_display(BinaryTree*);
	void level_order_display();
	int count_nodes(BinaryTree*);
	int count_height(BinaryTree*);
	int count_leaf_node(BinaryTree*);
private:
	BinaryTree* create_leaf(int);
};

BinaryTree* root = nullptr;

BinaryTree* BinaryTree :: create_leaf(int data) {
	return (new BinaryTree(data));
}

int BinaryTree :: insert_leaf_node(int data) {
	BinaryTree* newLeaf = create_leaf(data);
	if(newLeaf == nullptr) {
		return -1;
	}
	if(root != nullptr) {
		queue<BinaryTree*> tempQueue;
		tempQueue.push(root);
		while(true) {
			BinaryTree* temp = tempQueue.front();
			tempQueue.pop();
			if(temp->leftChild == nullptr) {
				temp->leftChild = newLeaf;
				return 1;
			}
			if(temp->rightChild == nullptr) {
				temp->rightChild = newLeaf;
				return 1;
			}
			tempQueue.push(temp->leftChild);
			tempQueue.push(temp->rightChild);
		}
	}
	root = newLeaf;
	return 1;
}

void BinaryTree :: pre_order_display(BinaryTree* root) {
	if(root != nullptr) {
		cout << root->data << " ";
		pre_order_display(root->leftChild);
		pre_order_display(root->rightChild);
	}
}

void BinaryTree :: in_order_display(BinaryTree* root) {
	if(root != nullptr) {
		in_order_display(root->leftChild);
		cout << root->data << " ";
		in_order_display(root->rightChild);
	}
}

void BinaryTree :: post_order_display(BinaryTree* root) {
	if(root != nullptr) {
		post_order_display(root->leftChild);
		post_order_display(root->rightChild);
		cout << root->data << " ";
	}
}

void BinaryTree :: level_order_display() {
	queue<BinaryTree*> tempQueue;
	tempQueue.push(root);
	while(!tempQueue.empty()) {
		BinaryTree* temp = tempQueue.front();
		tempQueue.pop();
		cout << temp->data << " ";
		if(temp->leftChild != nullptr) tempQueue.push(temp->leftChild);
		if(temp->rightChild != nullptr) tempQueue.push(temp->rightChild);
	}
}

int BinaryTree :: count_nodes(BinaryTree* root) {
	if(root != nullptr) {
		int leftCount = count_nodes(root->leftChild);
		int rightCount = count_nodes(root->rightChild);
		return leftCount + rightCount + 1;
	}
	return 0;
}

int BinaryTree :: count_height(BinaryTree* root) {
	if(root != nullptr) {
		int leftHeight = count_height(root->leftChild);
		int rightHeight = count_height(root->rightChild);
		return (leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1);
	}
	return 0;
}

int BinaryTree :: count_leaf_node(BinaryTree* root) {
	if(root != nullptr) {
		int leftCount = count_leaf_node(root->leftChild);
		int rightCount = count_leaf_node(root->rightChild);
		if(root->leftChild == nullptr && root->rightChild == nullptr) {
			return leftCount + rightCount + 1;
		}
		return leftCount + rightCount;
	}
	return 0;
}

int main() {
	int data, choice, ret;
	bool exitMenu = false;
	BinaryTree binaryTree;
	while(true) {
		cout << endl;
		cout << "1 -> Insert leaf node to binary tree" << endl;
		cout << "2 -> Pre-order display" << endl;
		cout << "3 -> In-order display" << endl;
		cout << "4 -> Post-order display" << endl;
		cout << "5 -> Level order display" << endl;
		cout << "6 -> Count the total number of nodes" << endl;
		cout << "7 -> Count height of the Binary tree" << endl;
		cout << "8 -> Count total leaf nodes of the Binary tree" << endl;
		cout << "0 -> Exit menu" << endl;
		cout << "Enter your choice..." << endl;
		cin >> choice;
		switch(choice) {
			case 1:
				cout << "Enter the data: ";
				cin >> data;
				ret = binaryTree.insert_leaf_node(data);
				if(ret == -1)
					cout << "Error: Heap overflow" << endl;
				else
					cout << data << " is inserted successfully" << endl;
				break;
			case 2:
				if(root == nullptr) {
					cout << "Error: Empty binary tree. Nothing to display." << endl;
				} else {
					cout << "Pre-order display..." << endl; 
					binaryTree.pre_order_display(root);
				}
				break;
			case 3:
				if(root == nullptr) {
					cout << "Error: Empty binary tree. Nothing to display." << endl;
				} else {
					cout << "In-order display..." << endl;
					binaryTree.in_order_display(root);
				}
				break;
			case 4:
				if(root == nullptr) {
					cout << "Error: Empty binary tree. Nothing to display." << endl;
				} else {
					cout << "Post-order display..." << endl;
					binaryTree.post_order_display(root);
				}
				break;
			case 5:
				if(root == nullptr) {
					cout << "Error: Empty binary tree. Nothing to display." << endl;
				} else {
					cout << "Level order display..." << endl;
					binaryTree.level_order_display();
				}
				break;
			case 6:
				cout << "Total nodes in the Binary tree are..." << endl;
				cout << binaryTree.count_nodes(root);
				break;
			case 7:
				cout << "The height of Binary tree is..." << endl;
				cout << binaryTree.count_height(root);
				break;
			case 8:
				cout << "Total leaf nodes in Binary tree..." << endl;
				cout << binaryTree.count_leaf_node(root);
				break;
			case 0:
				exitMenu = true;
				break;
			default:
				cout << "Error: Wrong choice. Enter again." << endl;
			break;
		}
		if(exitMenu) break;
	}
	return 0;
}