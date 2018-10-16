#ifndef _HEAP_H
#define _HEAP_H

#include "hash.h" 
#include <vector>
#include <string>

class heap{

    public:
        //The constructor
        //Allocates space for the nodes of the heap
        //and the mapping (hash table) based on the specified capacity
        heap(int capactiy); 

        //public functions //return 0 if sucess, 1 if did not work:
        //   
        //inserts a new item into the heap
        int insert(const std::string &id, int key, void *pv = NULL);    
        
        //provides increaseKey and decreaseKey functionaility
        int setKey(const std::string &id, int key);   
        
        //removes the item with the lowest key from the heap
        int deleteMin(std::string *pId = NULL, int *pKey = NULL, void *ppData = NULL); 
        
        //delete an item with a specified key from the heap
        int remove(const std::string &id, int *pKey = NULL, void *ppData = NULL);    
        
    private:
        //the "structure" of each heap entry //An inner class within heap class
        class node {            
            public:
                std::string id; // The id of this node
                int key;        // The key of this node
                void *pData;    // A pointer to the actual data
        };
        
        int capacity; //total capacity of the heap, initialized in constructor
        int filled; //Number of occupied items in the heap 


        //The declarations of my data vector and hash table pointer:
        std::vector<node> data;   //The actual binary heap
        hashTable *mapping;       //maps ids to node pointers
        
        //private member functions 
        void percolateUp(int posCur);
        void percolateDown(int posCur);
        int getPos(node *pn);      

};







#endif //_HEAP_H
