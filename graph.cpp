#include "graph.h"   

Graph::Graph(){
    this-> Node_HT = hashTable(50000); //can grow if needed
    //this-> gHeap = new  gHeap(capactiy);
}

void Graph::load(std::ifstream& inputFile){
    std::string line;
    std::string first_vertex;
    std::string second_vertex;
    int weight;
    int insertCheck;
  //  std::list<Node>::iterator it = Node_List.begin();

    while (getline(inputFile, line)){   
        std::istringstream ss(line);
        ss >> first_vertex >> second_vertex >> weight;
        std::cout << first_vertex << " " << second_vertex << " " << weight << std::endl;

        insertCheck = Node_HT.insert(first_vertex); ///initilizes nodes here so Dijkstra method doesn't have to
        if (insertCheck == 0){
        	Node node;
        	node.name = first_vertex;
            node.known = false;
        	node.dist = INFINITY;
        	Node_List.push_back(node);
        	Node_HT.setPointer(first_vertex, &node);

        }
        insertCheck = Node_HT.insert(second_vertex); ///initilizes nodes here so Dijkstra method doesn't have to
        if (insertCheck == 0){
        	Node node;
        	node.name = second_vertex;
            node.known = false;
        	node.dist = INFINITY;
        	Node_List.push_back(node);
        }
       

    }
        

   // NodeHashTab.insert(Node_name);
   // gHeap.insert(Node_name, INFINITY);
   // NodeList.push_back(Node_name);

    for (auto const& i : Node_List) {
        std::cout << i.name <<  " " << i.dist << " " << i.known << std::endl;
    }
    bool b;
    Node *t =  static_cast<Node*> (Node_HT.getPointer("v1", &b));
    // std::cout << (*t).name << std::endl;
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

