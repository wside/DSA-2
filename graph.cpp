#include "graph.h"   

void dijkstra(Node s){

    for each Node v{
        v.dist = INFINITY;
        v.known = false;
	}

	s.dist = 0;

	while(there is an unknown distance vertex){
		Node v = smallest unknown distance vertex;
		v. known = true;

		for each Node w adjacent to v{
            if (!w.known){
                DistType cvw = cost of edge from v to w;
                if ((v.dist + cvw) < w.dist){
                	//Update w
                    decrease( w.dist to (v.dist + cvw) );
                    w.path = v;
                }
		    }
        }
	}

}