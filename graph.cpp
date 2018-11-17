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

            //testnemch
            //std::cout << "first_vertex: " << first_vertex << std::endl;
            //std::cout << "second_vertex: " << second_vertex << std::endl;
            //std::cout << "edge.cost: " << edge.cost << std::endl;
            //std::cout << edge.nextNode->name << std::endl;
            //end of testbecnh
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
    
    short delMinCheck =0;
	while(delMinCheck!=1){
		std::string stringTmp;
        int key;
        Node *v;  //Node v = smallest unknown distance vertex;
		delMinCheck = gHeap.deleteMin(&stringTmp, &key, &v); //v is ppData  
        (v->known) = true;
        std::cout << "v name " << v->name << std::endl; //test del later
        std::cout << "v->dist " << v->dist << std::endl; //test del later
        for ( auto const& w : (v->adjlist) ){
        	std::cout << "w next node name " << w.nextNode->name << std::endl; //test del later
            //bool b3;
            //Node *g = static_cast<Node*> (Node_HT.getPointer((w.nextNode->name), &b3));     
             std::cout << "w.nextNode->known " << w.nextNode->known << std::endl; //test del later
            if ((w.nextNode->known)==false){  	 
                int cvw =  w.cost; //cost of edge from v to w
                 std::cout << "w.nextNode->dist orig " << w.nextNode->dist << std::endl; //test del later
                 std::cout << "cvw " << cvw << std::endl; //test del later
                  
                if ( v->dist + cvw < (w.nextNode->dist)){
                	//update w
                	w.nextNode->dist = v->dist + cvw;
                     std::cout << "w.nextNode->dist after " << w.nextNode->dist << std::endl; //test del later
                	gHeap.setKey(w.nextNode->name, w.nextNode->dist);
                	w.nextNode->path  = new Node;
                	w.nextNode->path = v;
                     std::cout << "w.nextNode->path->name " << w.nextNode->path->name << std::endl; //test del later
                }
            }     
        }
          std::cout << "---------------------" << std::endl; //test del later
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
            printPath(i.path, ofs);    
            ofs << ", " << i.name << "]" << std::endl; 
        }
        /*
        std::string printPath;
            	 
        Node *path = i.path;
     	while(path !=NULL){
     	    printPath = (path->name) + ", " + printPath;  
            if ( path->name==startNode)
                break;
     	     path = path->path;
     	}
         
        if (path==NULL && i.name!=startNode)
            ofs <<  i.name << ": " << "NO PATH" << std::endl; 
        else
           ofs <<   i.name << ": " << i.dist << " [" << printPath << i.name << "]"  << std::endl; 
   
        */     
    }

    ofs.close(); //close the output file
}


void Graph::printPath(Node *v, std::ofstream& outputFile){
    //std::cout<< "here2";
    if (v->path != NULL){
        //std::cout << v->path << std::endl;
        printPath(v->path, outputFile);
        outputFile << ", ";
    }
    outputFile << v->name;
}