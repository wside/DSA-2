//Wendy Ide
//Programming Assignment #3 -Dijkstra
//DSA II Prof. Sable
//11/15/2018

#include "graph.h"

#include <iostream>
#include <fstream>
#include <ctime>

std::string graphFile_name;
std::ifstream G_File;
std::string startVertex_name;
std::string outFile_name; 


void getUserInput(std::string message, std::string &ref){
    std::cout << message;
    std::cin >> ref;
}


void loadGraph(){
    getUserInput("Enter name of graph file: ", graphFile_name);
    G_File.open(graphFile_name, std::ifstream::in); 
    while (!G_File){
        G_File.clear();
        std::cout << "File cannot be opened, please try agian with valid file name." << std::endl;
        loadGraph();
    }
}


int main(){

    loadGraph(); //load input file into main

    Graph myGraph; //declare Graph class object
    
    myGraph.load(G_File); //load input file into Graph 
    
    //set starting vertex
    getUserInput("Enter a valid vertex id for the starting vertex: ", startVertex_name);
    while (!myGraph.startCheck(startVertex_name))
        getUserInput("Enter a valid vertex id for the starting vertex: ", startVertex_name);


    clock_t begin = clock();
    myGraph.dijkstra(startVertex_name); //the actual dijkstra algorithm function
    clock_t end = clock();
    double elapsed_secs_load = double(end - begin) / CLOCKS_PER_SEC;
    std::cout << "Total time (in seconds) to apply Dijkstra's algorithm: " << elapsed_secs_load << std::endl;

    getUserInput("Enter name of output file: ", outFile_name);  //load output file into main

    myGraph.output(outFile_name); //write dijkstra solution to text file

    return 0;

} //end of main    
