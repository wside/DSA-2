#include "graph.h"   

Graph::Graph(){
    this-> Node_HT = hashTable(50000); //can grow if needed
    //this-> gHeap = new  gHeap(capactiy);
}

void Graph::load(std::ifstream& inputFile){
    std::string word;
    short type = 1;
    totalNodeCount = 0; // declared in header 
    std::string first_vertex; //source vertex of an edge
    std::string second_vertex; //dest vertex of an edge

    short insertCheck;
  //  std::list<Node>::iterator it = Node_List.begin();

    while (inputFile >> word){
        if (type==1)
        	first_vertex=word;
        if (type==2)
        	second_vertex=word;
        if (type!=0){
            std::cout << word << std::endl;
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
        	std::cout << std::stoi(word)  << std::endl;
            Edge edge ;//= new Edge;
            edge.cost = std::stoi(word);
            edge.nextNode = new Node;
            edge.nextNode->name = second_vertex;
            bool b;
            Node *t =  static_cast<Node*> (Node_HT.getPointer(first_vertex, &b));     
            (t->adjlist).push_back(edge);
            std::cout << "here: " << std::endl;
        }
    
        type = (type+1)%3;
        std::cout << "type: " << type << std::endl;
    }

     std::cout << "totalNodeCount: " << totalNodeCount << std::endl;
     for (auto const& i : Node_List) {
        std::cout << i.name <<  " " << i.dist << " " << i.known << std::endl;
        for (auto const& j : i.adjlist)
             std::cout << j.nextNode->name <<  " " << j.cost << std::endl;
    }



}


bool Graph::startCheck(std::string startingNode){
    if (Node_HT.contains(startingNode)){
    	startNode = startingNode; //so whole class can have access
    	return true;
    }
    else
    	return false;
}


void Graph::dijkstra(std::string Node_x_name){
 std::cout << "here: " << std::endl;
    //done already
    //for each Node v{
        //v.dist = INFINITY;
      //  v.known = false;
	//}

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
    
    
	
    //debug
	for(auto const& i : Node_List) 
            std::cout << i.name <<  " " << i.dist << " " << i.known << std::endl;
    //debug

    short delMinCheck =0;
	while(delMinCheck!=1){
		std::cout << "here: " << std::endl;
		//Node v = smallest unknown distance vertex;
		//v. known = true;
		std::string stringTmp;
        int key;
        Node *v;
		delMinCheck = gHeap.deleteMin(&stringTmp, &key, &v); //v is ppData
        std::cout << "delMinCheck: " << delMinCheck << std::endl;
        // std::cout << "v: " << v<<  std::endl;
        (v->known) = true;
   
        //debug
        for (auto const& i : Node_List) 
            std::cout << i.name <<  " " << i.dist << " " << i.known << std::endl;
        //debug
       /*
		for each Node w adjacent to v{
            if (!w.known){
                int cvw = cost of edge from v to w;
                if ((v.dist + cvw) < w.dist){
                	//Update w
                    decrease( w.dist to (v.dist + cvw) );
                    w.path = v;
                }
		    }
        }
        */
        std::cout << "v->name: " << v->name <<  std::endl;
        for ( auto const& w : (v->adjlist) ){
        	//std::cout << "v->name: " << v->name <<  std::endl;
        	std::cout << "w.nextNode->name: " << w.nextNode->name <<  std::endl;
            std::cout << "v->dist: " << v->dist <<  std::endl;
            
        	bool b3;
            Node *g = static_cast<Node*> (Node_HT.getPointer((w.nextNode->name), &b3));     
            
            if ((g->known)==false){
            	 std::cout << "g->known: " << g->known <<  std::endl;
                int cvw =  w.cost; //cost of edge from v to w
                  std::cout << "cvw: " << cvw <<  std::endl;
                     std::cout << "g->dist: " << g->dist <<  std::endl;
                if ( v->dist + cvw < (g->dist)){
                	//update w
                	g->dist = v->dist + cvw;
                	std::cout << "g->dist: " << g->dist <<  std::endl;
                	gHeap.setKey(w.nextNode->name, g->dist);
                	g->path  = new Node;
                	g->path = v;
                	 //std::cout << "g->path: " << g->path <<  std::endl;
                }
            }      
        }
	//testbench
     for (auto const& i : Node_List) {
        std::cout << i.name <<  " " << i.dist << " " << i.known << std::endl;
    }
     



	}
	
}


void Graph::output(std::string outFile_name){
    //std::string startNode = "v5";
	
	std::ofstream ofs;
    ofs.open(outFile_name, std::ofstream::out);
    
     for (auto const& i : Node_List) {
     	 //bool b;
     	// Node *prev = static_cast<Node*> (Node_HT.getPointer((i.path), &b));
     	 //Node *(i.path);
         std::string printPath;
            	 


     	 Node *path = i.path;
     	 while(path !=NULL){
     	   
     	    
     	 	    printPath = (path->name) + ", " + printPath;  
                if ( path->name==startNode)
                	break;
     	     	path = path->path;
     	   

     	 }
         
         if (path==NULL && i.name!=startNode){
           ofs <<  i.name << ": " << "NO PATH" << std::endl; 
         }
         else

     	 ofs <<   i.name << ": " << i.dist << " [" << printPath << i.name << "]"  << std::endl; 
       // if (i.path->name != i.name){e
         //  if(i.path->path !=NULL)
     	 //  ofs << (i.path->path) << std::endl;
        // }
        
     
    }

     ofs.close(); //close the output file
}