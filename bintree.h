// created by Lynn Bak
// file bintree.h
// Prototype for bintree.cpp
// The purpose of this program is to create a binary search tree called
// BinTree with multiple functions. 

#ifndef BINTREE_H
#define BINTREE_H

#include "nodedata.h"

// ---------------------------------------------------------------------------
// BinTree class: a binary search tree 
//
//   Create and destroy a binary search tree
//   -- initializes an empty binary search tree (BinTree) object using a
//      default constructor
//   -- creates a BinTree object using copy constructor, which uses the
//      private copyHelper function
//   -- deletes the data and deallocates memory using destructor
//		(makeEmpty and a private helper, makeEmptyHelper, perform this task)
//
//   Features
//	 -- determines whether a BinTree object is empty or not 
//   -- assigns the data of a BinTree object to another by making a copy of  
//	    the contents in the BinTree 
//   -- determines whether a BinTree object has the same data and structure
//		as another object using the public functions, operator == and !=, and
//      a private function, equalityHelper
//   -- inserts a new data into a BinTree object
//	 -- retrieves a pointer to the data (NodeData used in this program) 
//      of a given data object; If the data whose value is equivalent to the
//      the data in the given object is found, another given pointer will 
//      point to the object in BinTree
//	 -- finds the depth of a given data in the tree (works with a private
//	    function, getDepthHelper
//   -- fills an array of data pointers (NodeData*) by using an inorder
//      traversal of the tree; leaves the tree empty (works with a private
//      function, treeToArrayHelper)
//	 -- builds a balanced BinTree from a sorted array of data pointers
//	    (NodeData*) (works with a private helper function, arrayToTreeHelper)
//
//	 Display a binary tree in 2 ways
//   -- displays a binary tree as though you are viewing it from the side
//		(a private function, sideways, performs the task)
//   -- displays a list of data in a binary tree through an inorder traversal
//
// Implementation and assumptions:
//   -- The BinTree class is developed in a way for users to use any type 
//      of data. 
//   -- This program is developed with using a NodeData object of
//      string type. 
//   -- The getDepth() function is implemented based on that whether 
//      a BinTree object is a binary search tree is unknown.
//   -- When a user is trying to print the data in an empty tree, the user
//      is prompted with a message, "Tree is empty."
//   
// ---------------------------------------------------------------------------

class BinTree{
	// overloaded output operator <<
	friend ostream& operator<<(ostream&, const BinTree&); 

public:
	BinTree();										// default constructor
	~BinTree();											// destructor
	void makeEmpty();									// makeEmpty
	bool isEmpty() const;								// isEmpty
	bool operator==(const BinTree&) const;				// operator ==
	bool operator!=(const BinTree&) const;				// opearotr !=
	bool insert(NodeData*);								// insert
	bool retrieve(const NodeData&, NodeData*&) const;	// retrieve
	int getDepth(const NodeData&) const;				// getDepth
	NodeData* getRoot() const;							// getRoot
	void bstreeToArray(NodeData* []);					// bstreeToArray
	void arrayToBSTree(NodeData* []);					// arrayToBSTree
	void displaySideways() const;						// displaySideways

private:
	struct Node{
		NodeData* data;			// pointer to a data object
		Node* left;				// pointer to left child/subtree
		Node* right;			// pointer to right child/subtree
	};
	Node* root;					// pointer to the root of a BinTree object

	// utility functions
	void makeEmptyHelper(Node*&);						//makeEmptyHelper
	bool equalityHelper(Node*, Node*) const;			//equalityHelper
	int getDepthHelper(const Node*, const NodeData&, int)const; //depthHelper
	void treeToArrayHelper(int&, NodeData* [], Node*);	//treeToArrayHelper
	Node* arrayToTreeHelper(int, int, NodeData* []);	//arrayToTreeHelper
	void sideways(Node*, int) const;					//sideways
	void outputInOrderHelper(ostream&, Node*) const;	//outputInrOrderHelper

};

#endif
