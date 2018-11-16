//Wendy Ide
//Programming Assignment #3 -Dijkstra
//DSA II Prof. Sable
//11/15/2018

#include "graph.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>


int main(){

    
    //load input Graph file
    //std::cout << "Enter name of graph file: ";
    //std::cin >> graphFile_name;
   
    std::string filename = "graph.txt";
    std::ifstream G_File;
    //G_File.open(graphFile_name, std::ifstream::in); //uncomment when take userinput
    G_File.open(filename, std::ifstream::in);
    if (!G_File){
          std::cout << "File not succesfully open" << std::endl;
          //reprompt user for file name
    }

    Graph myGraph;
    myGraph.load(G_File);
    myGraph.dijkstra("v5");
    myGraph.output();
    /*
    while (getline(G_File, line)){   
    	std::istringstream ss(line);
    	ss >> first_vertex >> second_vertex >> weight;
        std::cout << first_vertex << std::endl;
        std::cout << second_vertex << std::endl;
        std::cout << weight << std::endl;
        
        //test = myHashTab.insert(word);
    }
*/
   return 0;

} //end of main    
