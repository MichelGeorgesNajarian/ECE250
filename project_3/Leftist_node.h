
/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  uwuserid @uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter|Spring|Fall) 201N
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

#ifndef LEFTIST_NODE_H
#define LEFTIST_NODE_H

#include <algorithm>
// You may use std::swap and std::min

#ifndef nullptr
#define nullptr 0
#endif

template <typename Type>
class Leftist_node {
	private:
		Type element;
		Leftist_node *left_tree;
		Leftist_node *right_tree;
		int heap_null_path_length;

	public:
		Leftist_node( Type const & );

		Type retrieve() const;
		bool empty() const;
		Leftist_node *left() const;
		Leftist_node *right() const;
		int count( Type const & ) const;
		int null_path_length() const;
		void nplDistance(Leftist_node *);
		void push( Leftist_node *, Leftist_node *& );
		void clear();
		void printBT(const std::string& , Leftist_node * , bool );
};

template <typename Type>
Leftist_node<Type>::Leftist_node( Type const &obj ):
element( obj ),
left_tree( nullptr ),
right_tree( nullptr ),
heap_null_path_length( 0 ) {
	// does nothing
}

// You may need this

template <typename Type>
bool Leftist_node<Type>::empty() const {
//        evaluates to one if current node is nullptr
	return ( this == nullptr );
}

template <typename Type>
Type Leftist_node<Type>::retrieve() const {
    // return ekement of current node
    return this->element;
}

template <typename Type>
Leftist_node<Type> *Leftist_node<Type>::Leftist_node::right() const {
    // return right sub tree of current node
    return this->right_tree;
}

template <typename Type>
Leftist_node<Type> *Leftist_node<Type>::Leftist_node::left() const {
    //return left subtree of current node
    return this->left_tree;
}

template <typename Type>
int Leftist_node<Type>::null_path_length() const {
    if (empty()) {
        return -1;
    }
    // return the npl of current node
    return this->heap_null_path_length;
}

template <typename Type>
int Leftist_node<Type>::count( const Type &obj ) const {
    if (empty()) {
        return 0;
    }
    int countNum = 0;
    //going through recursively all left_tree nodes
    if(left() != nullptr){
       countNum += this->left()->count(obj);
    }
    //counting through recursively all left_tree nodes
    if (right() != nullptr){
       countNum += this->right()->count(obj);
    }
    //checking if elemnt of node is same value as object if yes then increment
    if (this->retrieve() == obj) {
	countNum++;
    }

    return countNum;
}

template <typename Type>
void Leftist_node<Type>::push( Leftist_node *newNode, Leftist_node *&curr) {
    //new node is null so nothing to add
    if (newNode == NULL){
        return;
    } else if (empty()){
	//heap is empty so heap becomes node
	curr = newNode;
    } else if (newNode->element >= this->element) {
	//if no left child then it becomes left child
        if (this->left_tree == nullptr) {
	    this->left_tree = newNode;
        } else if (this->right_tree == nullptr) {
	    // same as above but for right
	    this->right_tree = newNode;
	} else {
	    // go through recursively to the right
	    curr->right_tree->push(newNode,this->right_tree );
	}
	//if statement done to not compare if not both left and right filled
	if (this->right_tree != nullptr){
    	    if (this->left_tree->heap_null_path_length < this->right_tree->heap_null_path_length){
		//swap
	        Leftist_node *tmp;
    		tmp = this->left();
	    	this->left_tree = this->right();
		this->right_tree = tmp;
    	    }
	    // update npl
	    nplDistance(this);
	}
    } else {
	//old node in heap becomes new node to push as the node just pushed has smaller value
	curr = newNode;
	newNode->push(this, newNode);
    }
}

template <typename Type>
void Leftist_node<Type>::nplDistance(Leftist_node *node){
    //if heap is empty, then npl is -1
    if (node->right_tree == nullptr | node->left_tree == nullptr){
	node->heap_null_path_length = 0;
    } else {
	// npl if one node is always +1 bigger than right sub_tree as it is left heap
	node->heap_null_path_length = node->right_tree->heap_null_path_length + 1;
    }
}

template <typename Type>
void Leftist_node<Type>::clear(){
    //nothing to do here as everything is clear
    if (this == nullptr){
	return;
    }
    //go recursively to left subtree and delete in the end
    if (left() != nullptr){
	this->left()->clear();
    }
    //go recursively to right subtree and delete in the end
    if (right() != nullptr){
	this->right()->clear();
    }
    delete this;
}
//print funtion
template <typename Type>
void Leftist_node<Type>::printBT(const std::string& prefix, Leftist_node *node, bool isLeft){
    if(node != nullptr ){
       std::cout << prefix;

       std::cout << (isLeft ? "├──" : "└──" );
       std::cout << node->element << std::endl;
       printBT( prefix + (isLeft ? "│   " : "    "), node->right_tree, true);
       printBT( prefix + (isLeft ? "│   " : "    "), node->left_tree, false);
    }
}
						    

// You must implement everything

#endif
