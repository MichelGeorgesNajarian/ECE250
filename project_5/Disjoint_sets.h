
#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

#ifndef nullptr
#define nullptr 0
#endif


#include <limits>
#include "Exception.h"

using namespace std;

struct ll_entry; // represents each element of the linked list
struct set_info; // keeps track of the information (pointers to head and tail and the size of the set) of each set
//could we delete the above two lines?


struct ll_entry{ 
	int content;
	set_info* ptr_to_info; // ptr to the info entry of the corresponding set
	ll_entry* next;
	
};

struct set_info { 
	ll_entry* head;
	ll_entry* tail;
	int size;
};

class Disjoint_set {

private:
	ll_entry** nodes;
	set_info** sets;
	int set_counter;
	int initial_num_sets;
public:
	Disjoint_set(int);
	~Disjoint_set();
	int find_set(int) const;
	int num_sets() const;
	void union_sets(int, int);
};

Disjoint_set::Disjoint_set(int n) : nodes(new ll_entry*[n]), 
sets (new set_info*[n]), 
set_counter(n),
initial_num_sets(n) {
    for (int i = 0; i < n; i++){
	this->nodes[i] = new ll_entry; // creating nodes
	this->sets[i] = new set_info; // creating sets

	// making the set point to node
	this->sets[i]->head = this->nodes[i];
	this->sets[i]->tail = this->nodes[i];
	this->sets[i]->size = 1;

	// content go from 1 to n-1, at each loop, new cintent is value of i
	this->nodes[i]->content = i;
	//new itemp points nowhere
	this->nodes[i]->next = nullptr;
	this->nodes[i]->ptr_to_info = this->sets[i];
    }
}

Disjoint_set::~Disjoint_set() {
    int num = this->initial_num_sets;
    for (int i = 0; i < num; i++){
	delete this->sets[i]; //deleting every part of array
	this->sets[i] = nullptr; //extra security to make sure there is nothing left assigned
    }
    for (int i = 0; i < num; i++){
	delete this->nodes[i]; // delete every part of array
	this->nodes[i] = nullptr; //extra security to make sure there is nothing left assigned
    }
    delete[] this->sets; //deleting the entire set
    delete[] this->nodes; // deleting the entire node
    this->sets = nullptr; // safeguard, assigning set to nullptr
    this->nodes = nullptr; // same thing with node
    set_counter = 0; //not really necessary but just in case
    initial_num_sets = 0; // not really necessary but just in case
}
int Disjoint_set::find_set(int item) const{
    return nodes[item]->ptr_to_info->head->content;//returning the content of the head of the set containing the number item
}

int Disjoint_set::num_sets() const {
	return set_counter;//returning the number of sets
}

void Disjoint_set::union_sets(int node_index1, int node_index2) {
    int totalNum = this->initial_num_sets;
    // all illegal inputs
    if (node_index1 < 0 || node_index2 < 0 || node_index1 >= totalNum || node_index2 >= totalNum) {
	throw illegal_argument();
    }
    //if indexes are the same then nothing to do;
    if (node_index1 == node_index2){
	return;
    }
	
    set_info* si1 = nodes[node_index1]->ptr_to_info; //set of first node to unionize
    set_info* si2 = nodes[node_index2]->ptr_to_info;//set of second node to unionize

    int sizeSet1 = si1->size;//getting size of set 1
    int sizeSet2 = si2->size;//getting size of set 2
    //std::cout << "size of set 1: " << si1->size << " | size of set 2: " << si2->size << std::endl;
    set_info *tempSet = nullptr;//creating new temp set_info without allocating any momery, to be used when swapping
    // program will work assuming size of si1 is bigger than si2 to make it more efficient. So need to swap si1 and si2 if it's actually the inverse
    if (sizeSet1 < sizeSet2){
	tempSet = si2;
	si2 = si1;
	si1 = tempSet;
    }

    // summing up the sums
    si1->size += si2->size;
    //connecting tail of set one to head of set 2
    si1->tail->next = si2->head;
    //setting tail of set 2 as the tail of the unined set
    si1->tail = si2->tail;
    tempSet = si2; // setting tempSet as si2
    ll_entry *tempNode = tempSet->head; // tempnode is head of si2
    for (int i = 0; i < si2->size; i++){
	tempNode->ptr_to_info = si1; // setting ptr_to_info of each node of set 2 to the one of set 1
	tempNode = tempNode->next;// going to next node
    }
    this->set_counter -= 1; // decrementing set counter since going to delete set2
}


#endif
