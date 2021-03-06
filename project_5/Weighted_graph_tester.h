/*************************************************
 * Weighted_graph_tester
 * A class for testing singly-linked lists.
 *
 * Author:  Douglas Wilhelm Harder
 * Copyright (c) 2006-9 by Douglas Wilhelm Harder.  All rights reserved.
 *
 * DO NOT EDIT THIS FILE
 *************************************************/

#ifndef WEIGHTED_GRAPH_TESTER_H
#define WEIGHTED_GRAPH_TESTER_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Exception.h"
#include "Tester.h"
#include "Weighted_graph.h"

#include <iostream>
#include <limits>
#include <cmath>


class Weighted_graph_tester:public Tester<Weighted_graph> {
	using Tester< Weighted_graph >::object;
	using Tester< Weighted_graph >::command;

	public:
		Weighted_graph_tester( Weighted_graph *obj = 0 ):Tester<Weighted_graph>( obj ) {
			// empty
		}

		void process();
};

/****************************************************
 * void process()
 *
 * Process the current command.  For singly-linked lists, these include:
 *
 *  Accessors
 *   edge_count n      edge_count    the edge count is n
 *   degree m n        degree        the degree of vertex m is n
 *   degree! m         degree        the call to degree of m returns an exception
 *   mst m d c         minimum_spanning_tree
 *                                   checks if the minimum spanning tree
 *                                   starting with vertex m is d with c edges checked
 *  Mutators
 *   insert m n d b    insert_edge   insert an edge of weight d between m and n, with insert return b
 *   insert! m n d     insert_edge   insert throws an exception when inserting
 *                                   an edge of weight d between m and n
 *   erase m n b       erase_edge    erase the edge connecting vertices m and n
 *   erase! m n        erase_edge    erase throws an exception when attempting to erase
 *                                   the edge between m and n
 *   clear             clear_edges   call the clear_edges member function
 *
 *  Others
 *   cout            cout << graph   print the graph (for testing only)
 *   summary                         prints the amount of memory allocated
 *                                   minus the memory deallocated
 *   details                         prints a detailed description of which
 *                                   memory was allocated with details
 *   !!                              use the previous command, e.g.  5 push_front 3
 *                                                                   6 !! 7         // same as push_front 7
 *   !n                              use the command used in line n  7 front 7
 *                                                                   8 !7 9         // same as push_front 9
 *
 ****************************************************/

void Weighted_graph_tester::process() {
	if ( command == "new" ) {
		object = new Weighted_graph();
		std::cout << "Okay" << std::endl;
	} else if ( command == "new:" ) {
		int n;
		std::cin >> n;

		object = new Weighted_graph( n );
		std::cout << "Okay" << std::endl;
	} else if ( command == "edge_count" ) {
		// check if the edge count equals the next integer read

		int expected_count;

		std::cin >> expected_count;

		int actual_count = object->edge_count();

		if ( actual_count == expected_count ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << "Failure in edge_count(): expecting the value '" << expected_count << "' but got '" << actual_count << "'" << std::endl;
		}
	} else if ( command == "degree" ) {
		int vertex;
		std::cin >> vertex;

		int expected_degree;
		std::cin >> expected_degree;

		int actual_degree = object->degree( vertex );

		if ( actual_degree == expected_degree ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << "Failure in degree(" << vertex << "): expecting the value '" << expected_degree << "' but got '" << actual_degree << "'" << std::endl;
		}
	} else if ( command == "degree!" ) {
		int v;
		std::cin >> v;

		try {
			object->degree( v );
			std::cout << "Failure in degree(" << v << "): expecting to catch an exception" << std::endl;
		} catch( illegal_argument ) {
			std::cout << "Okay" << std::endl;
		} catch (...) {
			std::cout << "Failure in degree(" << v << "): expecting an illegal argument exception but caught a different exception" << std::endl;
		}
	} else if ( command == "mst" ) {
		double expected_distance;
		std::cin >> expected_distance;

		int expected_count;
		std::cin >> expected_count;

		std::pair<double, int> actual_value = object->minimum_spanning_tree();

		if ( (fabs( actual_value.first - expected_distance ) < 1e-10) && (actual_value.second == expected_count) ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << "Failure in minimum_spanning_tree(): expecting the pair '" << expected_distance << "," << expected_count << "' but got '" << actual_value.first << "," << actual_value.second << "'" << std::endl;
		}
	} else if ( command == "insert" ) {
		int v1, v2;
		std::cin >> v1;
		std::cin >> v2;

		double weight;
		std::cin >> weight;

		bool expected_insert_edge;
		std::cin >> expected_insert_edge;


		bool actual_insert_edge = object->insert_edge( v1, v2, weight );

		if ( actual_insert_edge == expected_insert_edge ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << "Failure in insert_edge(" << v1 << "," << v2 << "," << weight << "): expecting the value '" << expected_insert_edge << "' but got '" << actual_insert_edge << "'" << std::endl;
		}
	} else if ( command == "insert!" ) {
		int v1, v2;
		std::cin >> v1;
		std::cin >> v2;

		double weight;
		std::cin >> weight;

		try {
			object->insert_edge( v1, v2, weight );
			std::cout << "Failure in insert_edge(" << v1 << ", " << v2 << ", " <<  weight << "): expecting to catch an exception" << std::endl;
		} catch( illegal_argument ) {
			std::cout << "Okay" << std::endl;
		} catch (...) {
			std::cout << "Failure in insert_edge(" << v1 << ", " << v2 << ", " <<  weight << "): expecting an illegal argument exception but caught a different exception" << std::endl;
		}
	} else if ( command == "erase" ) {
		int v1, v2;
		std::cin >> v1;
		std::cin >> v2;

		bool expected_erase_edge;
		std::cin >> expected_erase_edge;

		bool actual_erase_edge = object->erase_edge( v1, v2 );

		if ( actual_erase_edge == expected_erase_edge ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << "Failure in erase_edge(" << v1 << "," << v2 << "): expecting the value '" << expected_erase_edge << "' but got '" << actual_erase_edge << "'" << std::endl;
		}
	} else if ( command == "erase!" ) {
		int v1, v2;
		std::cin >> v1;
		std::cin >> v2;

		try {
			object->erase_edge( v1, v2 );
			std::cout << "Failure in insert_edge(" << v1 << ", " << v2 << "): expecting to catch an exception" << std::endl;
		} catch( illegal_argument ) {
			std::cout << "Okay" << std::endl;
		} catch (...) {
			std::cout << "Failure in insert_edge(" << v1 << ", " << v2 << "): expecting an illegal argument exception but caught a different exception" << std::endl;
		}
	} else if ( command == "clear" ) {
		object->clear_edges();
		std::cout << "Okay" << std::endl;
	} else if ( command == "cout" ) {
		std::cout << *object << std::endl;
	} else {
		std::cout << command << "Command not found." << std::endl;
	}
}

#endif
