
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

#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#ifndef nullptr
#define nullptr 0
#endif

#include <iostream>
#include <limits>
#include "Exception.h"
#include "Disjoint_sets.h"
#include "ece250.h"

using namespace std;

class Weighted_graph {
	private:
		static const double INF;
		double** graph;
		int num_nodes;
		int num_edges;
		

		// Do not implement these functions!
		// By making these private and not implementing them, any attempt
		// to make copies or assignments will result in errors
		Weighted_graph( Weighted_graph const & );
		Weighted_graph &operator=( Weighted_graph );

		// your choice

	public:
		Weighted_graph( int = 10 );
		~Weighted_graph();

		int degree( int ) const;
		int edge_count() const;
		std::pair<double, int> minimum_spanning_tree() const;
		void bubbleSortPairs(std::pair<int,int> []) const;
		bool insert_edge( int, int, double );
		bool erase_edge( int, int );
		void clear_edges();

	// Friends

	friend std::ostream &operator<<( std::ostream &, Weighted_graph const & );
};

const double Weighted_graph::INF = std::numeric_limits<double>::infinity();

Weighted_graph::Weighted_graph(int n ) {
    //ece250::allocation_table.summary();
    if (n < 0) {
	throw illegal_argument();
    }
    num_edges = 0;
    num_nodes = n;
    graph = new double*[n];
    for (int i = 0; i < n; i++){
	graph[i] = new double[n];
	for (int j = 0; j < n; j++){
	    graph[i][j] = INF;
	}
    }
    //ece250::allocation_table.summary();

}

Weighted_graph::~Weighted_graph() {
    //ece250::allocation_table.summary();
    for (int i = 0; i < num_nodes; i++){
	delete[] graph[i];
	graph[i] = nullptr;
    }
    delete[] graph;
    graph = nullptr;
    num_nodes = 0;
    num_edges = 0;
    //ece250::allocation_table.summary();
}

int Weighted_graph::degree(int u) const {
    if (u >= num_nodes || u < 0){//illegal arguments
	throw illegal_argument();
    }
    int deg = 0;
    //iterating through every node and seeing if connected to node u
    //if connected then update degree
    for (int i = 0; i < num_nodes; i++){
	deg = (graph[u][i] != INF) ? deg + 1 : deg;
    }
    return deg;
}

int Weighted_graph::edge_count() const {
	return num_edges;
}

bool Weighted_graph::erase_edge(int i, int j) {
    if (i >= num_nodes | j >= num_nodes | i < 0 | j < 0){
        //std::cout << "i or j less than 0" << std::endl;
	throw illegal_argument();
    }
    if (i == j){ //condition i and j equal return true
	return true;
    }
    if(graph[i][j] == INF){ //means edge between them doesn't exist 
	return false;
    }
    num_edges--;
    graph[i][j] = INF;
    graph[j][i] = INF;
    return true;
}

void Weighted_graph::clear_edges() {
    //go through each edge and set distance INF aka not connected
    for (int i = 0; i < num_nodes; i++){
	for (int j = 0; j < num_nodes; j++){
	    graph[i][j] = INF;
	}
    }
    //set num edges to 0 since there are none left
    num_edges = 0;
    return;
}

bool Weighted_graph::insert_edge( int i, int j, double d ) {
    //ece250::allocation_table.summary();
    if (i >= num_nodes | j >= num_nodes | d <= 0 | i < 0 | j < 0){//illegal test cases
        throw illegal_argument();
    }
    if (i == j) {
	return false;
    }
    if (graph[i][j] == INF){
	num_edges++;
    }
    graph[i][j] = d;
    graph[j][i] = d;
    return true;
}

std::pair<double, int> Weighted_graph::minimum_spanning_tree() const {
    int k = 0;
    std::pair <int,int> pairs[((this->num_nodes)*(this->num_nodes - 1))/2];
    //loop to enter al of the pairs in the piars array.
    for (int i = 0; i < this->num_nodes; i++){ 
	for (int j = i+1; j < num_nodes; j++){
	    //cout << "I: " << i << " | J: " << j << endl;
	    pairs[k].first = i;
	    pairs[k].second = j;
	    k++;
	}
    }
    //sorting pairs by non decreasing weights
    bubbleSortPairs(pairs);
    // initialiazing locally insatnce of Disjoint_set which would call destructor automatically after end of fucntion
    Disjoint_set ds(this->num_nodes);
    int edgesTested = 0;
    int  i = 0;
    double totalWeight = 0;
    // while we still have more than 1 set, continue to unionize
    while (ds.num_sets() > 1){
        edgesTested++;
	if (ds.find_set(pairs[i].first) != ds.find_set(pairs[i].second)){//if two sets not same head then union
	    totalWeight += graph[pairs[i].first][pairs[i].second]; //adding up the weights for each pair that unioned
	    ds.union_sets(pairs[i].first, pairs[i].second);//unioning the pairs
	}
	i++;//count up to go to next pair
    }
    // totalWeight is sum of all the weights of the minimumm spanning tree
    // edgesTested is the number of edges we went through to find the minimum spanning tree
    return std::pair<double, int>( totalWeight, edgesTested );
}

void Weighted_graph::bubbleSortPairs(std::pair<int,int> a[]) const {
    //bubble sort
    //cout << ((this->num_nodes)*(this->num_nodes - 1))/2 <<endl;
    bool swapped = true;
    for (int i = 0; i < ((this->num_nodes)*(this->num_nodes - 1))/2 - 1; i++){
	for (int  j = 0; j < ((this->num_nodes)*(this->num_nodes - 1))/2-i-1; j++){
	    if (this->graph[a[j].first][a[j].second] > this->graph[a[j+1].first][a[j+1].second] | this->graph[a[j].first][a[j].second] == INF){ // verifying if the weight is less
		std::pair <int,int> tempPair;
		tempPair.first = a[j].first;
		tempPair.second = a[j].second;
		//swapping
		a[j].first = a[j+1].first;
		a[j].second = a[j+1].second;

		a[j+1].first = tempPair.first;
		a[j+1].second = tempPair.second;
		//swapping happened is true
		swapped = true;
	    }
	}
	// break if no swap happened
	if (!swapped){
	    break;
	}
    }

}

std::ostream &operator<<( std::ostream &out, Weighted_graph const &graph ) {
	

	return out;
}


#endif
