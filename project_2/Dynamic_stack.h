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

#ifndef DYNAMIC_STACK_H
#define DYNAMIC_STACK_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Exception.h"
#include <iostream>
using namespace std;


class Dynamic_stack {

	private:
		int *array;
		int count;		
		int array_size;
		int initial_size;
	
	public:
		Dynamic_stack(int = 10);
		~Dynamic_stack();

		int top() const;
		int size() const;
		bool empty() const;
		int capacity() const;
			
		void push( int const & );
		int pop();
		void clear();		
};

Dynamic_stack::Dynamic_stack( int n ):
count( 0 ),
array_size( n ),
initial_size(n) {
    // checking if size requested is less than 1. If it is, then create an array or size 1
    if (n < 1) {
        // creating array of size 1
        array = new int[1];
    } else {
        // creating array of size n
        array = new int[array_size];
    }
}


Dynamic_stack::~Dynamic_stack() {
    delete[] array;
}


int Dynamic_stack::top() const {
    // if function empty, throw underflow
    if (empty()) {
        throw underflow();
    } else {
        //returning last element entered in array
        return array[count-1];
    }
}


int Dynamic_stack::size() const {
    // returning int count which is updated whenever a new int is pushed or popped from array
    return  count;
}


bool Dynamic_stack::empty() const {
    // if szie is 0 ie if there are no elements in array
    if (size() == 0) {
        return true;
    }
    return false;  
}


int Dynamic_stack::capacity() const {
    // returning array_size which is a variable that's automatically updated whenever size of array changes
    return array_size;
}


void Dynamic_stack::push( int const &obj ) {
    // if array still has enough space in it
    if (count < array_size){
        // put new object in it
        array[count] = obj;
    } else {
        // new size of array twice the old size
        int newSize = 2*array_size;
        // creating array1 which has double size of old array
        int *array1 = new int [newSize];
        // copying all items of old array  to new one
        for (int  i = 0; i < array_size; i++) {
            array1[i] = array[i];
        }
        // pushing new value in obj
        array1[array_size] = obj;
        // updating arra_size
        array_size = newSize;
        //deleting items in old array
        delete[] array;
        // assigning array to array1
        array = array1;
    }
    // updating count
    count++;
}


int Dynamic_stack::pop() {
     // getting value of top element
     int removedInt = array[count-1];
     // if array empty throw underflow
     if (empty()) {
        throw underflow();
    } else {
        // updating top element which will ignore the old top until it is overwritten
        count--;
    }
    // returning value that was "deleted"
    return removedInt;
}

void Dynamic_stack::clear() {
    // setting count as 0 so when putting new values, it will overwrite current values
    count = 0;
    // setting the array size to its initial value
    array_size = initial_size;
}
#endif
