#ifndef DOUBLE_HASH_TABLE_H
#define DOUBLE_HASH_TABLE_H


/****************************************
 * UW User ID:  uwuserid
 * Submitted for ECE 250
 * Semester of Submission:  (Winter|Spring|Fall) 20NN
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 ****************************************/

#include "Exception.h"
#include "ece250.h"

enum state { EMPTY, OCCUPIED, DELETED };

template<typename T>
class DoubleHashTable {
	private:
		int count;
		int power;
		int array_size;
		T *array;
		state *array_state;

		int h1( T const & ) const; // first hash function
		int h2( T const & ) const; // second hash function

	public:
		DoubleHashTable( int = 5 );
		~DoubleHashTable();
		int size() const;
		int capacity() const;		
		bool empty() const;
		bool member( T const & ) const;
		T bin( int ) const;

		void print() const;

		void insert( T const & );
		bool remove( T const & );
		void clear();
};

template<typename T >
DoubleHashTable<T >::DoubleHashTable( int m ):
count( 0 ), power( m ),
array_size( 1 << power ),
array( new T [array_size] ),
array_state( new state[array_size] ) {

	for ( int i = 0; i < array_size; ++i ) {
		array_state[i] = EMPTY;
	}
}

template<typename T >
DoubleHashTable<T >::~DoubleHashTable() {
    // enter your implementation here 
    delete[] array;
    delete[] array_state;
}

template<typename T >
int DoubleHashTable<T >::size() const {
    // enter your implementation here 
    return this->count; //count is the variable with the number of elements currently in the hash
}

template<typename T >
int DoubleHashTable<T >::capacity() const {
    // enter your implementation here 
    return this->array_size; // returning the array size
}



template<typename T >
bool DoubleHashTable<T >::empty() const {
    // enter your implementation here 
    return (size() == 0); // if size is zero then 0 == 0 is true so it will return true. Else it returns false
}

template<typename T >
int DoubleHashTable<T >::h1( T const &obj ) const {
    // enter your implementation here 
    int num = static_cast<int> (obj);
    num = num % this->array_size; //getting mod value
    num = (num >= 0) ? num : num + this->array_size; // adding value of size of array if % value is negative
    //std::cout << "h1 value: " << num << std::endl;
    return num;
}

template<typename T >
int DoubleHashTable<T >::h2( T const &obj ) const {
    // enter your implementation here 
    int num = static_cast<int> (obj);
    num = (num / this->array_size) % this->array_size;//dividing obj value by num of array
    num = (num >= 0) ? num : num + this->array_size;//adding size of arraya to value if value is negative
    num = (num%2 == 0) ? num + 1 : num;//if value is dividible by 2, then add 1 to make it odd
    return num;
}
//Logic to jump from one index to the other is the same for member, remove and insert
//only detailing for member the logic behind it
template<typename T >
bool DoubleHashTable<T >::member( T const &obj ) const {
    int num  = h1(obj);//gatting value for initial try to insert
    int nextJump = h2(obj);//getting jump size
    int numCapacity = capacity();
    int i = 0;
    while (numCapacity != i){
	//std::cout << i << std::endl;
	if (array_state[num] == EMPTY) {
	    return false; // if at tinitial try to insert, state is empty, then no value tried to be inserted in this slot so definitely not in there
	}
	//std::cout << "BANANAS" <<std::endl;
	//std::cout << num <<"Array number: " << array[num] << std::endl;
	if ((array[num] == obj && array_state[num] == OCCUPIED)){ // value in array and state is occupied which means it was inserted in array
	    return true;
	}
	num = (num + nextJump) % capacity(); //doing jump to next index
	i++;
    }
    return false;
}

template<typename T >
T DoubleHashTable<T >::bin( int n ) const {
    // enter your implementation here 	      
                    
	return array[n]; //returning value in array at inndex n
}

template<typename T >
void DoubleHashTable<T >::insert( T const &obj ) {
    // enter your implementation here 	
    if (size() == capacity()){ //array filled
	throw overflow();
    }
    int num  = h1(obj);
    //std::cout << "mod value: " << num << std::endl;
    int nextJump = h2(obj);
    //std::cout << "jump value: " << nextJump << std::endl;
    while (1){ //continue until free index found and the break from loop
	if (array_state[num] == EMPTY | array_state[num] == DELETED){ //can insert in deleted slot as well
	    array[num] = obj;
	    array_state[num] = OCCUPIED; //set state to occupied as new num was inserted
	    break;
	} else {
	    num = (num + nextJump) % capacity(); // calculating new index to go to
	}
    }
    this->count++;//update count
    //print();
    return; 
}

template<typename T >
bool DoubleHashTable<T >::remove( T const &obj ) {
	 // enter your implementation here 	
    int num  = h1(obj);
    //std::cout << "mod value: " << num << std::endl;
    int nextJump = h2(obj);
    //std::cout << "jump value: " << nextJump << std::endl;
    int numCapacity = capacity();
    int i = 0;
    while (numCapacity != i){
	if (array[num] == obj && array_state[num] == OCCUPIED){
	    array_state[num] = DELETED;//update slot state to deleted
            this->count--;//update count
            return true;
        }
        num = (num + nextJump) % capacity();
        i++;
    }
    return false;
}

template<typename T >
void DoubleHashTable<T >::clear() {
    // enter your implementation here
    int i = 0;
    // setting state as empty for every slot in array
    while (i != this->array_size){
	array_state[i] = EMPTY;
    	i++;
    }
    this->count = 0;
}

template<typename T >
void DoubleHashTable<T >::print() const {
    // enter your implementation here 	
    // printing number in order of the array
    for (int i = 0; i < capacity(); i++){
	std::cout << i << "->" << array[i]  << std::endl;
    }
    std::cout << "-------------------------------------" << std::endl;
    std::cout << "-------------------------------------" << std::endl;
    // printing in order the states of each slot
    for (int i = 0; i < capacity(); i++){
        if (array_state[i] == EMPTY){
	    std::cout << i << " -> EMPTY" << std::endl;
	} else if (array_state[i] == OCCUPIED){
	    std::cout << i << " -> OCCUPIED" << std::endl;
	} else if (array_state[i] == DELETED) {
	    std::cout << i << " -> DELETED" << std::endl;
	}
    }
    return;
}

#endif
