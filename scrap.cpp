short counter = 1;
    while (getline(G_File, line)){
        if (counter!=0){
            std::cout << word << std::endl;
            //test = myHashTab.insert(word);
        }
    
        counter = (counter+1)%3;
       // std::cout << "count: " << counter << std::endl;
    }



std::cout << "-----------------------------" << std::endl;
  //  std::list<Node>::iterator it = Node_List.begin();
    void *ptr;
   
    std::cout <<   &Node_List.front()  << std::endl;
    bool b;
    Node *t =  static_cast<Node*> (Node_HT.getPointer("v1", &b));
    std::cout << "pos: " <<  &Node_List.front() - t << std::endl;
    Node *t2 =  static_cast<Node*> (Node_HT.getPointer("v2", &b));
    std::cout << "pos: " <<  &Node_List.front() - t2 << std::endl;
    Node *t3 =  static_cast<Node*> (Node_HT.getPointer("v4", &b));
    std::cout << "pos: " <<  &Node_List.front() - t3 << std::endl;
    Node *t4 =  static_cast<Node*> (Node_HT.getPointer("v5", &b));
    std::cout << "pos: " <<  &Node_List.front() - t4 << std::endl;
    Node *s =  static_cast<Node*> (Node_HT.getPointer("v3", &b));
    std::cout << "pos: " <<  &Node_List.front() - s << std::endl;
    Node *t5 =  static_cast<Node*> (Node_HT.getPointer("v6", &b));
    std::cout << "pos: " <<  &Node_List.front() - t5 << std::endl;
    Node *t6 =  static_cast<Node*> (Node_HT.getPointer("v7", &b));
    std::cout << "pos: " <<  &Node_List.front() - t6 << std::endl;

  //  int pos = t - &Node_List.front();
 // std::cout << "pos: " <<  &(*t)  << std::endl;
  //  std::cout << "pos: " <<  &Node_List.front() - t << std::endl;
    
    // std::cout << (*t).name << std::endl;
    // Advance the iterator by 2 positions,
//std::advance(it, 5);
 // std::advance(it, pos);
//std::cout << it->name <<  " " << it->dist << " " << it->known << std::endl;


    /*
    while (getline(inputFile, line)){   
        std::istringstream ss(line);
        ss >> first_vertex >> second_vertex >> weight;
        std::cout << first_vertex << " " << second_vertex << " " << weight << std::endl;
        
        //initilizes nodes here so Dijkstra method doesn't have to
        insertCheck = Node_HT.insert(first_vertex); 
        if (insertCheck == 0){
        	Node node;
        	node.name = first_vertex;
            node.known = false;
        	node.dist = INFINITY;
        	Node_List.push_back(node);
        	Node_HT.setPointer(first_vertex, &Node_List.back());
        }
        insertCheck = Node_HT.insert(second_vertex); 
        if (insertCheck == 0){
        	Node node;
        	node.name = second_vertex;
            node.known = false;
        	node.dist = INFINITY;
        	Node_List.push_back(node);
        	Node_HT.setPointer(second_vertex, &Node_List.back());
        }
       

    }
        

    for (auto const& i : Node_List) {
        std::cout << i.name <<  " " << i.dist << " " << i.known << std::endl;
    }

    bool b;
    Node *t =  static_cast<Node*> (Node_HT.getPointer("v3", &b));
    std::cout << "pos: " <<  t->name << " " << t->dist << " " << t->known <<std::endl;

   */
	 std::string stringTmp;
  int key, id;
      gHeap.setKey("v4", 2);
    gHeap.deleteMin(&stringTmp, &key);
    std::cout << "\nDeleted item with string id \"" << stringTmp
	     << "\" and key " << key << std::endl;