#include "graph.h"   

Graph::Graph(){
    this-> Node_HT = hashTable(50000); //can grow if needed
}

void Graph::load(std::ifstream& inputFile){
    std::string word;
    short type = 1;
    totalNodeCount = 0;        //declared in header 
    std::string first_vertex;  //source vertex of an edge
    std::string second_vertex; //destination vertex of an edge

    short insertCheck;

    while (inputFile >> word){
        if (type==1)
        	first_vertex=word;
        if (type==2)
        	second_vertex=word;
        if (type!=0){
            //initilizes nodes here so Dijkstra funct doesn't have to
            insertCheck = Node_HT.insert(word); 
            if (insertCheck == 0){
        	    Node node;
        	    node.name = word;
                node.known = false;
        	    node.dist = INFINITY;
        	    Node_List.push_back(node);
        	    Node_HT.setPointer(word, &Node_List.back());
        	    totalNodeCount++;
            }
        }
        else{   //the third word of each line, means type == 0
            Edge edge ;
            edge.cost = std::stoi(word);
            edge.nextNode = new Node;
            bool b1;
            edge.nextNode = static_cast<Node*> (Node_HT.getPointer(second_vertex, &b1));     
            //edge.nextNode->name = second_vertex;
            bool b2;
            Node *t =  static_cast<Node*> (Node_HT.getPointer(first_vertex, &b2));     
            (t->adjlist).push_back(edge);
        }
    
        type = (type+1)%3;
    }   
}


bool Graph::startCheck(std::string startingNode){
    if (Node_HT.contains(startingNode))
    	return true;
    else
    	return false;
}


void Graph::dijkstra(std::string Node_x_name){
    startNode = Node_x_name; //so whole class can have access
   
    //set the starting vertex cost to 0
    bool b2;
    Node *x = static_cast<Node*> (Node_HT.getPointer(Node_x_name, &b2));     
    (x->dist) = 0;

    //put all unknown verticies in a heap (local to dijkstra funct)
    heap gHeap(totalNodeCount);
    for (auto const& i : Node_List) {
    	bool b1;
    	Node *pv =  static_cast<Node*> (Node_HT.getPointer(i.name, &b1));  
        gHeap.insert (i.name, i.dist, pv); //pv is ppData
    }
    
    //determine shortest paths
    short delMinCheck =0;
	while(delMinCheck!=1){
		std::string stringTmp;
        int key;
        Node *v;  //Node v = smallest unknown distance vertex;
		delMinCheck = gHeap.deleteMin(&stringTmp, &key, &v); //v is ppData  
        (v->known) = true;
        for ( auto const& w : (v->adjlist) ){           
            if ((w.nextNode->known)==false){  	 
                int cvw =  w.cost; //cost of edge from v to w
                if ( v->dist + cvw < (w.nextNode->dist)){  //key decision
                	//update w
                	w.nextNode->dist = v->dist + cvw;
                	gHeap.setKey(w.nextNode->name, w.nextNode->dist);
                	w.nextNode->path  = new Node;
                	w.nextNode->path = v;
                }
            }     
        }
	}	
}


void Graph::output(std::string outFile_name){
    std::ofstream ofs;
    ofs.open(outFile_name, std::ofstream::out);
    
    for (auto const& i : Node_List) {       
        ofs <<  i.name << ": ";       
        if (i.path==NULL && i.name == startNode) 
            ofs << i.dist << " [" << i.name << "]" << std::endl; 
        else if (i.path==NULL)
            ofs << "NO PATH" << std::endl;
        else if (i.path != NULL){
            ofs << i.dist << " [";
            printPath(i.path, ofs);  //calls the path finding function here  
            ofs << ", " << i.name << "]" << std::endl; 
        } 
    }

    ofs.close(); //close the output file
}


void Graph::printPath(Node *v, std::ofstream& outputFile){
    if (v->path != NULL){
        printPath(v->path, outputFile); //goes back through the nodes and prints in reverse (from start to finish) since recursive 
        outputFile << ", ";
    }
    outputFile << v->name;
}