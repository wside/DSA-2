#ifndef _GRAPH_H
#define _GRAPH_H

class Graph{

    public:
        Graph();
        void dijkstra(node s);
        void load();
        void output();  

    private:
        class Node; //edge needs t recognize node
        class Edge{
        	//next node
        	//weight
        };
        class Node{
            public: 
            list<Edge> adj; //adjacency list
            bool known;
            DistType dist; //DIstType is probably int
            Vertex path; //Probably vertext *, as mentioned above 
            //other datat member functions as needed
        };

};r

//heap delete min (shortest path)

#endif //_GRAPH_H