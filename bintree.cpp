// created by Lynn Bak
// file bintree.cpp
// Implementation of the class BinTree 

#include "bintree.h"

// ---------------------------------------------------------------------------
// Default constructor
// Creates a new BinTree object. 

BinTree::BinTree(){
	root = NULL;
}

// ---------------------------------------------------------------------------
// Destructor
// Deletes all data and memory allocated for an object

BinTree::~BinTree(){
	makeEmpty();
}

// ---------------------------------------------------------------------------
// makeEmpty 
// Clears all the data and memory which were dynamically allocated for a
// BinTree object

void BinTree::makeEmpty(){
	makeEmptyHelper(root);
}

void BinTree::makeEmptyHelper(Node*& root){
	if (root != NULL){
		makeEmptyHelper(root->left);
		makeEmptyHelper(root->right);
		delete root->data;
		root->data = NULL;
		delete root;
		root = NULL;
	}
}

// ---------------------------------------------------------------------------
// isEmpty
// Determines whether a BinTree object is empty

bool BinTree::isEmpty() const{
	return root == NULL;
}

// ---------------------------------------------------------------------------
// operator ==
// Determines whether a BinTree object (this) has the same data and 
// structure as another object

bool BinTree::operator==(const BinTree& treeToCompare) const{
	return equalityHelper(root, treeToCompare.root);
}

bool BinTree::equalityHelper(Node* currNode, Node* compareNode) const{
	// 2 base cases
	if (currNode == NULL && compareNode == NULL){
		return true;
	}else if (currNode == NULL || compareNode == NULL){
		return false;
	}else{
		return *currNode->data == *compareNode->data 
			&& equalityHelper(currNode->left, compareNode->left) 
			&& equalityHelper(currNode->right, compareNode->right);
	}
}

// ---------------------------------------------------------------------------
// operator !=
// Determines whether a BinTree object (this) doesn't contain the same data
// and structure as another object

bool BinTree::operator!=(const BinTree& treeToCompare) const{
	return !(*this == treeToCompare);
}
	
// ---------------------------------------------------------------------------
// insert
// Inserts a new data into a BinTree object

bool BinTree::insert(NodeData* newData){
	Node* ptr = new Node;

	// checking for out of memory
	if (ptr == NULL){
		return false;
	}

	ptr->data = newData;
	ptr->left = NULL;
	ptr->right = NULL;

	if (isEmpty()){
		root = ptr;
	}

	else{
		Node* current = root;
		bool inserted = false;		

		while (!inserted){
			// the current data is greater than newData
			// look at the left subtree
			if (*current->data > *newData){
				if (current->left == NULL){
					current->left = ptr;
					inserted = true;
				}
				else{
					current = current->left;
				}
			}
			// the current data is less than newData
			else if (*current->data < *newData){
				if (current->right == NULL){
					current->right = ptr;
					inserted = true;
				}
				else{
					current = current->right;
				}
			}
			// the current data is equal to/duplicate of newData
			// deletes the pre-allocated memory for data 
			else{
				delete ptr->data;
				delete ptr;
				ptr = NULL;
				break;
			}
		}
	}
	
	return true;
}

//---------------------------------------------------------------------------
// retrieve
// Retrieves a NodeData pointer of a given NodeData object
// If the data whose value is equivalent to the data in the given object is
// found, the second parameter will point to the object in the tree.
bool BinTree::retrieve(const NodeData& target, NodeData*& container) const{
	container = NULL;              // NULL if not found
    
    if (!isEmpty()) {
        
        Node* current = root;   // walking pointer
        bool stop = false;      // whether stopped yet
        
        // if item is less than current item, walk left subtree,
        // otherwise walk right subtree until found, or the end
        // of the tree is reached
        while (!stop) {
            if (*current->data != target) {
                if (target < *current->data) {
                    if (current->left == NULL) {     // found end
                        stop = true;
                        return false;
                    }
                    else
                        current = current->left;     // one step left
                }
                else {
                    if (current->right == NULL) {    // found end
                        stop = true;
                        return false;
                    }
                    else
                        current = current->right;    // one step right
                }
            }
            else {
                stop = true;
                container = current->data;
                return true;
            }
        }
    }
    return false;
}

//---------------------------------------------------------------------------
// getDepth
// Finds the depth of a given value in the tree

int BinTree::getDepth(const NodeData& target) const{ 
	if(root == NULL){
		return 0;
	}
	int depth = 0;		// the depth of a node at the root is 1
	return getDepthHelper(root, target, depth);
}

int BinTree::getDepthHelper(const Node* current, const NodeData& target, 
							int depth) const{
	
	if (*current->data == target){
		depth++;
	}

	if (current->left != NULL && depth == 0){
		depth += getDepthHelper(current->left, target, depth);
	}

	if (current->right != NULL && depth == 0){
		depth += getDepthHelper(current->right, target, depth);
	}

	if (*current->data != target && depth != 0){
		depth++;
	}

	return depth;
}

//-----------------------------------------------------------------------------
// getRoot
NodeData* BinTree::getRoot() const {
    return root->data;
}

//---------------------------------------------------------------------------
// bstreeToArray
// Fills an array of NodeData* by using an inorder traversal of the tree
// Leaves the tree empty

void BinTree::bstreeToArray(NodeData* arrayToFill[]){
	if (!isEmpty()){
		int index = 0;
		treeToArrayHelper(index, arrayToFill, root);
		this->makeEmpty();
	}
	else{
		arrayToFill = NULL;
	}
}

void BinTree::treeToArrayHelper(int& index, NodeData* arrayToFill[], 
								Node* current){
	if (current != NULL){
		treeToArrayHelper(index, arrayToFill, current->left);

		NodeData* newDataPtr;	// to point to the data object in the tree
		newDataPtr = current->data;

		// the array pointer points to the data object in the tree
		arrayToFill[index] = newDataPtr; 

		// a pre-existing pointer to NodeData in the tree is disconnected.
		current->data = NULL;

		index++;

		treeToArrayHelper(index, arrayToFill, current->right);
	}
}

//---------------------------------------------------------------------------
// arrayToBSTree
// Builds a balanced BinTree from a sorted array (assumed) of NodeData* 

void BinTree::arrayToBSTree(NodeData* copyFrom[]){
	if (copyFrom == NULL){
		root = NULL;
	}
	else {
		int arraySize = 0;

		// finding the size of array
		while (copyFrom[arraySize] != NULL){
			arraySize++;
		}
		int start = 0;
		// the last subscript is arraySize - 1
		root = arrayToTreeHelper(start, arraySize - 1, copyFrom);
	}
}

BinTree::Node* BinTree::arrayToTreeHelper(int start, int end, 
										  NodeData* copyFrom[]){
	// base case 
	if (start > end){
		return NULL;
	}
	int mid = start + (end - start) / 2; 

	// creates a new node to build a BinTree
	Node* newNode = new Node;
	newNode->data = copyFrom[mid];
	// the array pointer to data is disconnected
	copyFrom[mid] = NULL;

	newNode->left = arrayToTreeHelper(start, mid - 1, copyFrom);
	newNode->right = arrayToTreeHelper(mid + 1, end, copyFrom);

	return newNode;
}

//---------------------------------------------------------------------------
// displaySideways 
// Displays a binary tree as though you are viewing it from the side;
// hard coded displaying to standard output.

void BinTree::displaySideways() const {
   sideways(root, 0);
}

void BinTree::sideways(Node* current, int level) const {
   if (current != NULL) {
      level++;
      sideways(current->right, level);

      // indent for readability, 4 spaces per depth level 
      for(int i = level; i >= 0; i--) {
          cout << "    ";
      }

      cout << *current->data << endl;      // display information of object
      sideways(current->left, level);
   }
}

// ---------------------------------------------------------------------------
// operator<<
// Overloaded output operator for class BinTree
// Displayed through an inorder traversal

ostream& operator<<(ostream& output, const BinTree& tree){
	if (tree.root == NULL){
		output << "Tree is empty." << endl;
	}
	else{
		tree.outputInOrderHelper(output, tree.root);
		output << endl;
	}
	return output;
}

void BinTree::outputInOrderHelper(ostream& output, Node* root) const{
	if (root != NULL){
		outputInOrderHelper(output, root->left);
		output << *root->data;
		outputInOrderHelper(output, root->right);
	}
}

