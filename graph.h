#ifndef _GRAPH_H
#define _GRAPH_H

#define INFINITY 2000000000 //2 billion

#include "hash.h"  
#include "heap.h"  
#include <fstream>
#include <list>


class Graph{

    public:
       	Graph();
        void load(std::ifstream& inputFile);
        bool startCheck(std::string startingNode);
        void dijkstra(std::string Node_x_name);
        void output(std::string outFile_name);  

    private:
        class Node; //Edge class needs to recognize Node class
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
                Node *path; 
        };
        
        void printPath(Node *v, std::ofstream& outputFile);

        std::list<Node> Node_List;
    
        //heap local to dijstras function so not declared in header 
        hashTable Node_HT;

        int totalNodeCount;
        std::string startNode;

};


#endif //_GRAPH_H