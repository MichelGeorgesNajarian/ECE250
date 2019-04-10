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
    Double_node *tail = new Double_node; //creating new node for head
    Double_node *head = new Double_node; // creating new  node for tail
    list_head = head; //assigning head
    list_tail = tail; //assigning tail
    list_head->previous_node = nullptr; //setting previous node of head to nullptr
    list_tail->next_node = nullptr; //setting next node of tail to nullptr
    list_head->next_node = list_tail; //poiting list head next node as list tail
    list_tail->previous_node = list_head; //poiting list tail previous node as list head
}
//copy constructor
template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> const &list ):
// Updated the initialization list here
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 )
{
    Double_node *tail2 = new Double_node; //create new tail
    Double_node *head2 = new Double_node; // create new head
    list_head = head2; 
    list_tail = tail2;
    head2->previous_node = nullptr;
    tail2->next_node = nullptr;
    head2->next_node = tail2; // making them point to each other
    tail2->previous_node = head2; //making them point to each other

    Double_node *cur = list.begin();
    while (cur != list.end()) { //starting at begining of list and iterating until we reach the last one
        push_back(cur->node_value); //push the value
        cur = cur->next_node; //iterate to next node
    }
}
// move constructor
template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> &&list ):
// Updated the initialization list here
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 )
{   // building just like constructor above
    Double_node *tail = new Double_node;
    Double_node *head = new Double_node;
    list_head = head;
    list_tail = tail;
    list_head->previous_node = nullptr;
    list_tail->next_node = nullptr;
    list_head->next_node = list_tail;
    list_tail->previous_node = list_head;
    // swap takes care of moving everything from one list to the other
    swap(list);
}

template <typename Type>
Double_sentinel_list<Type>::~Double_sentinel_list() {
    Double_node *cur = list_head->next_node; // setting the current node as the head sentinel
    Double_node *tmp;
    while (list_size != 0){ // looping until that the next node after the head sentinel is the tail sentinel
        tmp = cur; //setting a tmp so that it can be deleted while incrementing cur
        cur = cur->next_node; // moving cur to next node
        delete tmp; // deleting tmp
        list_size--; // decrementing list size since there is one less item
    }
    //list_size = 0;
    delete list_head; //deleting the head sentinel
    //std::cout << list_tail->node_value << std::endl;
    delete list_tail; //deleting the tail sentinel
}

template <typename Type>
int Double_sentinel_list<Type>::size() const {
    return list_size; //list head is always incremented and decremented hence returning this is enough
}

template <typename Type>
bool Double_sentinel_list<Type>::empty() const {
    Double_node *cur = list_head; //setting the curent node to list head 
    if (cur->next_node == list_tail) { // if head is pointing to tail and vice versa, then list is empty
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
    Double_node *firstNode = list_head->next_node; //select first node after head sentinel
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
         return list_head->next_node; // returning address of first element OR tail
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
         return list_head; // returning address of head
     } catch (...) { // catching if list has nothing inside of it
         return nullptr; //returning nullptr by default
     }
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::find( Type const &obj ) const {
    Double_node *cur = list_head->next_node;
    while (cur->node_value != obj) {
        if (cur->next_node == list_tail){
            //return cur->node_value;
            return cur;
        }
        cur = cur->next_node;
    }
    //return cur->node_value;
    return cur;
}

template <typename Type>
int Double_sentinel_list<Type>::count( Type const &obj ) const {
    //std::cout << std::endl << std::endl ;
    int numItem = 0; // this way won't overcount sentinel
    Double_node *cur = list_head;
    while (cur->next_node != nullptr) {
        //std::cout << "value in linked list: " << cur->node_value << std::endl;
        if (cur->node_value == obj) {
            numItem++;
            //std::cout << cur->node_value << " is in the list! " << std::endl;
        }
        cur = cur->next_node;
    }
    //std::cout << std::endl << "count return value: " << numItem << std::endl;
    return numItem;
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
    // creating new node
    Double_node *newNode = new Double_node;
    newNode->node_value = obj; //setting value of node to obj
    newNode->previous_node = list_head; // pointing new node to list head
    newNode->next_node = list_head->next_node; //pointin new node to the old first node
    Double_node *curFirstNode = list_head->next_node;
    curFirstNode->previous_node = newNode; // pointing old first node to new node
    list_head->next_node = newNode; // pointing head to new node
    list_size++; //incrementing list
}

template <typename Type>
void Double_sentinel_list<Type>::push_back( Type const &obj ) {
    // same as push_front except head is replace by tail, previous is replace by next and vice versa and oldfirst node is replaced by old last node
    Double_node *newNode = new Double_node;
    newNode->node_value = obj;
    newNode->previous_node = list_tail->previous_node;
    newNode->next_node = list_tail;
    Double_node *curLastNode = list_tail->previous_node;
    curLastNode->next_node = newNode;
    list_tail->previous_node = newNode;
    list_size++;
}

template <typename Type>
void Double_sentinel_list<Type>::pop_front() {
    // if list is empty, there is nothing to pop
    if (empty()) {
        throw underflow();
    } else {
        Double_node *tmp = list_head->next_node; //selecting the first node other than head
        list_head->next_node = tmp->next_node; //pointing new first node to next of old first node
        Double_node *newFirst = tmp->next_node; 
        newFirst->previous_node = list_head; // pointing new first node to head
        list_size--; // decrementing
        delete tmp; //deleting old first node
    }
}

template <typename Type>
void Double_sentinel_list<Type>::pop_back() {
    // just like pop_front except for the back
    if (empty()) {
        throw underflow();
    } else {
        Double_node *tmp = list_tail->previous_node;
        list_tail->previous_node = tmp->previous_node;
        Double_node *newLast = tmp->previous_node;
        newLast->next_node = list_tail;
        list_size--;
        delete tmp;
    }
}

template <typename Type>
int Double_sentinel_list<Type>::erase( Type const &obj ) {
    // selecting current node as the first node
    Double_node *cur = list_head->next_node;
    Double_node *tmp;
    // int to increment on number of deletes
    int numDelet = 0;
    //std::cout << "entering erase function " << std::endl;
    // incrementing while not arriving to tail
    while (cur->next_node != nullptr){
        // if the value of the current node is one that we have to delete, enter statement
        if (cur->node_value == obj){
            tmp = cur;
            // connecting previous node of current to next node of current
            tmp->previous_node->next_node = tmp->next_node;
            // connecting next node of current to previous node of current
            tmp->next_node->previous_node = tmp->previous_node;
            // incrementing number of deleted one
            numDelet++;
            // decrementing node
            list_size--;
            // moving up of list
            cur = cur->next_node;
            // deleting node
            delete tmp;
        } else {
            // moving up in list
            cur = cur->next_node;
        }
    }
    //std::cout << "leaving erase function " << std::endl;
	return numDelet;
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
	// Enter your implementation here
}

template <typename Type>
Type Double_sentinel_list<Type>::Double_node::value() const {
	return node_value; // This returns a default value of Type
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::Double_node::previous() const {
	return previous_node;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::Double_node::next() const {
	return next_node;
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
