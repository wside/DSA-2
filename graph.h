#ifndef _GRAPH_H
#define _GRAPH_H

#include "hash.h"  
#include "heap.h"  
#include <limits>
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>


const int INFINITY= std::numeric_limits<int>::max();

class Graph{

    public:
       	Graph();
       // Graph(int capactiy);
        void load(std::ifstream& inputFile);
        void dijkstra(std::string Node_x_name);
        void output();  

    private:
        class Node; //edge needs t recognize node
        class Edge{
        	public:
        	    Node *nextNode;
        	    int cost;
        };
        class Node{
            public: 
                std::string name;
                bool known;
                int dist; 
                std::list<Edge> adjlist; //adjacency list
                Node *path; //Probably vertex*, as mentioned above 
            //other datat member functions as needed
        };

        std::list<Node> Node_List;
        hashTable Node_HT;
        int totalNodeCount;
        //heap gHeap; 

};

//heap delete min (shortest path)

#endif //_GRAPH_H