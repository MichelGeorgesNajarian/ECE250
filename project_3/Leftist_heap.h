
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

#ifndef LEFTIST_HEAP_H
#define LEFTIST_HEAP_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Leftist_node.h"

template <typename Type>
class Leftist_heap {
	private:
		Leftist_node<Type> *root_node;
		int heap_size;

	public:
		Leftist_heap();
		~Leftist_heap();

		void swap( Leftist_heap &heap );
		

		bool empty() const;
		int size() const;
		int null_path_length() const;
		Type top() const;
		int count( Type const & ) const;

		void push( Type const & );
		Type pop();
		void clear();

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Leftist_heap<T> const & );
};

// some sample functions are given

template <typename Type>
Leftist_heap<Type>::Leftist_heap():
root_node( nullptr ),
heap_size( 0 ) {
	// does nothing
}



template <typename Type>
Leftist_heap<Type>::~Leftist_heap() {
	clear();  // might as well use it...
}

template <typename Type>
void Leftist_heap<Type>::swap( Leftist_heap<Type> &heap ) {
	std::swap( root_node, heap.root_node );
	std::swap( heap_size, heap.heap_size );
}



// Your implementation here
// STRONG HINT:  Write a default definition of each function, even if
// it only returns the default value (false, 0, or Type()).
//
// Once you have done this, you can proceed and implement the member functions
// one at a time.  If you do not, and just start implementing the member
// functions so that you can't compile and test your function, good luck. :-)

// You can modify this function however you want:  it will not be tested

//to see if heap empty or not, using heap_size
template <typename Type>
bool Leftist_heap<Type>::empty() const { 
    if (heap_size != 0){
        return false;
    }
    return true;
}

//finding size using heap_size
template <typename Type>
int Leftist_heap<Type>::size() const {
    return heap_size;
}

//returning the npl of a Leftist_node or -1 if heap empty
template <typename Type>
int Leftist_heap<Type>::null_path_length() const {
    if (empty()){
        return -1;
    }
    //calling null_path_length for node
    return this->root_node->null_path_length();
}

//
template <typename Type>
int Leftist_heap<Type>::count( const Type &obj ) const {
    if (empty()){
        return -1;
    }
    //counts recursively the nodes
    return this->root_node->count(obj);
}

template <typename Type>
Type Leftist_heap<Type>::top() const {
    if (empty()){
        throw underflow();
    }
    return this->root_node->retrieve();
}

template <typename Type>
void Leftist_heap<Type>::push( const Type &obj ){
    //creating new node with elemnt obj
    Leftist_node<Type> *newNode = new Leftist_node<Type>(obj);
    //pushing new node onto heap by calling function
    root_node->push(newNode, this->root_node);
    std::cout << std::endl;
    root_node->printBT("", this->root_node, false);
    //incrementing heap size
    heap_size++;
}

template <typename Type>
Type Leftist_heap<Type>::pop() {
    if (empty()){
	throw underflow();
    }
    //getting value to return
    Type pop_val = this->root_node->retrieve();
    //selecting left sub-heap of root node
    Leftist_node<Type> *new_root = root_node->left();
    //selecting right sub-heap of root node
    Leftist_node<Type> *new_node = root_node->right();
    //deleting current root node
    delete root_node;
    //assigning new root as the left sub-heap
    root_node = new_root;
    //pushing the right sub-heap to main one
    root_node->push(new_node, root_node);
    std::cout << std::endl;
    root_node->printBT("", this->root_node, false);
    //decreasing size
    heap_size--;
    return pop_val;
}

template <typename Type>
void Leftist_heap<Type>::clear() {
    this->root_node->clear();
    this->root_node = nullptr;
    heap_size = 0;
}

template <typename T>
std::ostream &operator<<( std::ostream &out, Leftist_heap<T> const &heap ) {
	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
