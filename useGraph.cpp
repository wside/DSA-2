//Wendy Ide
//Programming Assignment #3 -Dijkstra
//DSA II Prof. Sable
//11/15/2018

#include "graph.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>

std::string graphFile_name;
std::string startVertex_name;
std::string outFile_name; 
/*
void prompt(){
    std::cout << "Enter a valid vertex id for the starting vertex: ";
    std::cin >> startVertex_name;
}
*/


int main(){


    //load input Graph file
    std::cout << "Enter name of graph file: ";
    std::cin >> graphFile_name;
   
    //std::string filename = "graph.txt";
    std::ifstream G_File;
    G_File.open(graphFile_name, std::ifstream::in); 
    if (!G_File){
          std::cout << "File cannot be opened, please try agian with valid file name." << std::endl;
          //reprompt user for file name
    }
        
    Graph myGraph;
    myGraph.load(G_File);
    std::cout << "Enter a valid vertex id for the starting vertex: ";
    std::cin >> startVertex_name;
    while (!myGraph.startCheck(startVertex_name)){ //won't enter if input valid vertex the first time
          std::cout << "Enter a valid vertex id for the starting vertex: ";
          std::cin >> startVertex_name;
    }

    clock_t begin = clock();
    myGraph.dijkstra(startVertex_name);
    clock_t end = clock();
    double elapsed_secs_load = double(end - begin) / CLOCKS_PER_SEC;
    std::cout << "Total time (in seconds) to apply Dijkstra's algorithm: " << elapsed_secs_load << std::endl;

    //load output file
    std::cout << "Enter name of output file: ";
    std::cin >> outFile_name;

    myGraph.output(outFile_name);

   return 0;

} //end of main    
