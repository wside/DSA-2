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

    int insertCheck;
  //  std::list<Node>::iterator it = Node_List.begin();

    while (inputFile >> word){
        if (type==1)
        	first_vertex=word;
        if (type==2)
        	second_vertex=word;
        if (type!=0){
            std::cout << word << std::endl;
            //initilizes nodes here so Dijkstra method doesn't have to
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


/*
void Graph::dijkstra(Node s){

    
    //for each Node v{
        //v.dist = INFINITY;
      //  v.known = false;
	//}
	

	for (auto const& i : NodeList) {
        i.NodeList.dist = INFINITY;
        i.NodeList.known = false;
    }

	s.dist = 0;

	while(there is an unknown distance vertex){
		Node v = smallest unknown distance vertex;
		v. known = true;

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
	}

}
*/

