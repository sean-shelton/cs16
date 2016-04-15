// stringbst.cpp
// Implements class StringBST
// Sean Shelton, Patrick Vidican
// 3/6/16

#include "stringbst.h"

#include <iostream>
using std::cout;

// constructor sets up empty tree
StringBST::StringBST() : root(0) { } // ORIGINAL CONSTRUCTOR
/*StringBST::StringBST() {
    root = NULL;
}*/

// destructor deletes all nodes
StringBST::~StringBST() {
    clear(root);
}

// recursive helper for destructor
void StringBST::clear(Node *n) {
    if (n) {
        clear(n->left);
        clear(n->right);
        delete n;
    }
}

// insert value in tree; return false if duplicate
bool StringBST::insert(string value) {
    // handle special case of empty tree first
    if (!root) {
        root = new Node(value);
        return true;
    }
    // otherwise use recursive helper
    return insert(value, root);
}

// recursive helper for insert (assumes n is never 0)
bool StringBST::insert(string value, Node *n) {
    if (value == n->info)
        return false;
    if (value < n->info) {
        if (n->left)
            return insert(value, n->left);
        else {
            n->left = new Node(value);
            return true;
        }
    }
    else {
        if (n->right)
            return insert(value, n->right);
        else {
            n->right = new Node(value);
            return true;
        }
    }
}

// print tree data pre-order
void StringBST::printPreOrder() const {
    printPreOrder(root);
}

// recursive helper for printPreOrder()
void StringBST::printPreOrder(Node *n) const {
    if (n) {
        cout << n->info << " ";
        printPreOrder(n->left);
        printPreOrder(n->right);
    }
}

// remove value from tree
void StringBST::remove(string value) { // public remove
    // IMPLEMENT
    // (add helpers below if you use recommended recursive technique)
    remove(value, root);
}

void StringBST::remove(string value, Node* &n) { // private remove
    if (n->info == value)
        removeThis(n);
    else {
        //if (!insert(value, n)) {
            if ((value < n->info) && (n->left) /*!= 0*/) {
                remove(value, n->left);
            }
            if ((value > n->info) && (n->right) /*!= 0*/) {
                remove(value, n->right);
            }
        //}
    }
}

void StringBST::removeThis(Node* &n) {
    if (n == 0)
        return;
    else {
        //if (n->left == 0 && n->right == 0) { //left and right are null
        if (!(n->left) && !(n->right)) { // leaf case
            Node* replace = n;
            n = NULL;
            delete replace;
        }
    
        else if (!(n->left) /*&& n->right != 0*/) { //left is null
            Node* replace = n;
            n = n->right;
            delete replace;
        }
    
        else if (/*n->left != 0 &&*/ !(n->right))  { //right is null
            Node* replace = n;
            n = n->left;
            delete replace;
        }
    
        else if (n->left /*!= 0*/ && n->right /*!= 0*/) { // both left and right are not null
            n->info = maxValue(n->left);
            remove(n->info, n->left); 
        }
    }
}

string StringBST::maxValue(Node *n) const {
    if (n->right != NULL) 
        return maxValue(n->right);
    else
        return n->info;
}