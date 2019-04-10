/*****************************************
 * UW User ID:  uwuserid
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter|Spring|Fall) 20NN
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

#ifndef DOUBLE_SENTINEL_LIST_H
#define DOUBLE_SENTINEL_LIST_H

#include <iostream>
#include "Exception.h"

template <typename Type>
class Double_sentinel_list {
	public:
		class Double_node {
			public:
				Double_node( Type const & = Type(), Double_node * = nullptr, Double_node * = nullptr );

				Type value() const;
				Double_node *previous() const;
				Double_node *next() const;

				Type         node_value;
				Double_node *previous_node;
				Double_node *next_node;
		};

		Double_sentinel_list();
		Double_sentinel_list( Double_sentinel_list const & );
		Double_sentinel_list( Double_sentinel_list && );
		~Double_sentinel_list();

		// Accessors

		int size() const;
		bool empty() const;

		Type front() const;
		Type back() const;

		Double_node *begin() const;
		Double_node *end() const;
		Double_node *rbegin() const;
		Double_node *rend() const;

		Double_node *find( Type const & ) const;
		int count( Type const & ) const;

		// Mutators

		void swap( Double_sentinel_list & );
		Double_sentinel_list &operator=( Double_sentinel_list );
		Double_sentinel_list &operator=( Double_sentinel_list && );

		void push_front( Type const & );
		void push_back( Type const & );

		void pop_front();
		void pop_back();

		int erase( Type const & );

	private:
		Double_node *list_head;
		Double_node *list_tail;
		int list_size;

		// List any additional private member functions you author here
	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Double_sentinel_list<T> const & );
};

/////////////////////////////////////////////////////////////////////////
//                      Public member functions                        //
/////////////////////////////////////////////////////////////////////////

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list():
// Updated the initialization list here
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 )
{
    Double_node *headSent = new Double_node; // created head of node
    Double_node *list_tail = new Double_node; //created tail of node

    headSent->previous_node = nullptr;
    list_tail->next_node = nullptr;
    headSent->next_node = list_tail;
    list_tail->previous_node = headSent;
}

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> const &list ):
// Updated the initialization list here
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 )
{
	// Enter your implementation here
}

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> &&list ):
// Updated the initialization list here
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 )
{
	// Enter your implementation here
}

template <typename Type>
Double_sentinel_list<Type>::~Double_sentinel_list() {
    Double_node *cur = headSent; // setting the current node as the head sentinel
    while (cur->next_node != list_tail){ // looping until that the next node after the head sentinel is the tail sentinel
        pop_front(); // remove the first element after the head sentinel
    }
    Double_node *lastSent = headSent->next_node; //selecting the tail sentinel
    delete cur; //deleting the head sentinel
    delete lastSent; //deleting the tail sentinel
}

template <typename Type>
int Double_sentinel_list<Type>::size() const {
    int numItem = 0 // this way won't overcount sentinel
    Double_node *cur = headSent;
    while (cur->next_node != list_tail) {
        numItem++;
        cur = cur->next_node;
    }
    return numItem;
}

template <typename Type>
bool Double_sentinel_list<Type>::empty() const {
    Double_node *cur = headSent;
    if (cur->next_node == list_tail) {
	return true;
    }
    return false;
}

template <typename Type>
Type Double_sentinel_list<Type>::front() const {
    if (empty()){ //checking if the list is empty
        throw underflow();
        return Type();
    }
    Double_node *firstNode = headSent->next_node; //select first node after head sentinel
    return firstNode->node_value; // return the value of the first node
}

template <typename Type>
Type Double_sentinel_list<Type>::back() const {
    if (empty()){ //checking if the list is empty
        throw underflow(); //throwing underflow
        return Type();
     }
     Double_node *lastNode = list_tail->previous_node; //taking the last element, using list_tailinel and then the previous node
     return lastNode->node_value; // return the value of the last node->node_value;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::begin() const {
     try { // trying
         return headSent->next_node; // returning address of first element OR tail
     } catch (...) { // catching if list has nothing inside of it
         return nullptr; //returning nullptr by default
     }
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::end() const {
     try { //trying
         return list_tail; // returning address of tail sentinel
     } catch (...) { // catching if list has nothing inside of it
         return nullptr; //returning nullptr by default
     }
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::rbegin() const {
    try { //trying
         return list_tail->previous_node; // returning address of last element OR head
     } catch (...) { // catching if list has nothing inside of it
         return nullptr; //returning nullptr by default
     }
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::rend() const {
    try { // trying
         return headSent; // returning address of head
     } catch (...) { // catching if list has nothing inside of it
         return nullptr; //returning nullptr by default
     }
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::find( Type const &obj ) const {
    Double_node *cur = headSent->next_node;
    while (cur->node_value != &obj) {
        if (cur->next_node == list_tail){
            return cur->node_value;
        }
        cur = cur->next_node;
    }
    return cur->node_value;
}

template <typename Type>
int Double_sentinel_list<Type>::count( Type const &obj ) const {
    int count = 0;
    Double_node *cur = headSent->next_node;
    while (cur->next_node != list_tail) {
        if (cur->node_value == &obj){
            count++;
        }
        cur = cur->next_node;
    }
    return count;
}

template <typename Type>
void Double_sentinel_list<Type>::swap( Double_sentinel_list<Type> &list ) {
	// This is done for you
	std::swap( list_head, list.list_head );
	std::swap( list_tail, list.list_tail );
	std::swap( list_size, list.list_size );
}

// The assignment operator
template <typename Type>
Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=( Double_sentinel_list<Type> rhs ) {
	// This is done for you
	swap( rhs );

	return *this;
}

// The move operator
template <typename Type>
Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=( Double_sentinel_list<Type> &&rhs ) {
	// This is done for you
	swap( rhs );

	return *this;
}

template <typename Type>
void Double_sentinel_list<Type>::push_front( Type const &obj ) {
    Double_node *newNode = new Double_node;
    newNode->node_value = &obj;
    newNode->previous_node = headSent;
    newNode->next_node = headSent->next_node;
    Double_node *curFirstNode = headSent->next_node;
    curFirstNode->previous_node = newNode;
    headFirst->next_node = newNode;
}

template <typename Type>
void Double_sentinel_list<Type>::push_back( Type const &obj ) {
    Double_node *newNode = new Double_node;
    newNode->node_value = &obj;
    newNode->previous_node = list_tail->previous_node;
    newNode->next_node = list_tail;
    Double_node *curLastNode = list_tail->previous_node;
    curLastNode->next_node = newNode;
    list_tail->previous_node = newNode;
}

template <typename Type>
void Double_sentinel_list<Type>::pop_front() {
    Double_node *tmp = headSent->next_node;
    delete headSent->next_node;
    headSent->next_node = tmp->next_node;
    Double_node *newFirst = tmp->next_node;
    newFirst->previous_node = headSent;
    delete tmp;
}

template <typename Type>
void Double_sentinel_list<Type>::pop_back() {
    Double_node *tmp = list_tail->previous_node;
    delete list_tail->previous_node;
    list_tail->previous_node = tmp->previous_node;
    Double_node *newLast = tmp->previous_node;
    newLast->next_node = list_tail;
    delete tmp;
}

template <typename Type>
int Double_sentinel_list<Type>::erase( Type const &obj ) {
    Double_node *cur = list_head->next_node;
    while (cur->next_node != nullptr) {
        if (cur->node_value == obj) {
            Double_node *tmp = cur;
            // continue here
        }
    }
	return 0;
}

template <typename Type>
Double_sentinel_list<Type>::Double_node::Double_node(
	Type const &nv,
	typename Double_sentinel_list<Type>::Double_node *pn,
	typename Double_sentinel_list<Type>::Double_node *nn ):
// Updated the initialization list here
node_value( Type() ), // This assigns 'node_value' the default value of Type
previous_node( nullptr ),
next_node( nullptr )
{
    Double_node *newNode = new Double_node;
    newNode->previous_node = pn;
    newNode->next_node = nn;
    newNode->node_value = nv;
}

template <typename Type>
Type Double_sentinel_list<Type>::Double_node::value() const {
	// Enter your implementation here
	return Type(); // This returns a default value of Type
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::Double_node::previous() const {
	// Enter your implementation here
	return nullptr;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::Double_node::next() const {
	// Enter your implementation here
	return nullptr;
}

/////////////////////////////////////////////////////////////////////////
//                      Private member functions                       //
/////////////////////////////////////////////////////////////////////////

// If you author any additional private member functions, include them here

/////////////////////////////////////////////////////////////////////////
//                               Friends                               //
/////////////////////////////////////////////////////////////////////////

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Double_sentinel_list<T> const &list ) {
	out << "head";

	for ( typename Double_sentinel_list<T>::Double_node *ptr = list.rend(); ptr != nullptr; ptr = ptr->next() ) {
		if ( ptr == list.rend() || ptr == list.end() ) {
			out << "->S";
		} else {
			out << "->" << ptr->value();
		}
	}

	out << "->0" << std::endl << "tail";

	for ( typename Double_sentinel_list<T>::Double_node *ptr = list.end(); ptr != nullptr; ptr = ptr->previous() ) {
		if ( ptr == list.rend() || ptr == list.end() ) {
			out << "->S";
		} else {
			out << "->" << ptr->value();
		}
	}

	out << "->0";

	return out;
}

#endif
