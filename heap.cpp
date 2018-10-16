#include "heap.h"   


//constructor
heap::heap(int capacity){
    this->filled = 0;
    this->capacity = capacity;
    data.resize(capacity+1);
    this->mapping = new hashTable(capacity); //hash class automatically multiplies input capacity by 2 to avoid collisions
}


//public functions:
int heap::insert(const std::string &id, int key, void *pv){
    int posCur = filled+1;
    if (filled==capacity) //heap is full //implement dynamic resize later
    	return 1;
    if (mapping->contains(id)==true) //node with the given id already exists 
    	return 2;
    else{
        data.at(posCur).id = id;
        data.at(posCur).key = key;
        data.at(posCur).pData = pv;
        mapping->insert(id, &data[posCur]);
        percolateUp(posCur);
        filled++; //increase filled counter after item was successfully inserted
        return 0;
    }
}


int heap::setKey(const std::string &id, int key){
    if (mapping->contains(id)==false) //node with the given id does not exist
    	return 1;
    else{
    	bool b;
    	node *pn = static_cast<node *> (mapping->getPointer(id, &b));
	    int setPos = getPos(pn);
	    data.at(setPos).key = key;
	    //if replacement node < parent node, filter replacement node up the tree
	    if (data.at(setPos).key < data.at(setPos/2).key) 
     	    percolateUp(setPos);          
        else 
     	    percolateDown(setPos); //else percolate down //will break from function immediately if current is less than both children
     	return 0;        
    }
}


int heap::deleteMin(std::string *pId, int *pKey, void *ppData){
    if (filled == 0)
    	return 1;
    else{
    	//poiter stuff
        if (pId!=NULL)
       	    *pId = data[1].id; 
        if (pKey!=NULL)
        	*pKey = data[1].key; 
        if (ppData!=NULL)
        	*(static_cast<void **> (ppData)) = data[1].pData;
        //"delete" the root by switching the root and the last node
        //then deleteing the contents of the last node
        mapping->setPointer(data[filled].id, &data[1]);
        mapping->remove(data[1].id);
        std::swap(data.at(filled),data.at(1)); 
       
        data.at(filled).id = "";
        data.at(filled).key = 0;
        data.at(filled).pData = NULL;
   
        filled--;
        percolateDown(1);  
        return 0;
    }
} 


int heap::remove(const std::string &id, int *pKey, void *ppData){ 
	if (mapping->contains(id)==false) //node with the given id does not exist
    	return 1;
    else{ 
    	//get position of node that you want to delete
    	bool b;
	    node *pn = static_cast<node *> (mapping->getPointer(id, &b));
	    int delPos = getPos(pn);
	    //pointer stuff
	    if (pKey!=NULL)
        	*pKey = data[delPos].key; 
        if (ppData!=NULL)
        	*(static_cast<void **> (ppData)) = data[delPos].pData;
	    //"delete delPos" by switching delPos with farthest right node 
	    //then delete the farthest right node
	    mapping->setPointer(data[filled].id, &data[delPos]);
        mapping->remove(data[delPos].id);
        std::swap(data.at(filled),data.at(delPos)); 
        data.at(filled).id = "";
        data.at(filled).key = 0;
        data.at(filled).pData = NULL;
        filled--;
        //if replacement node < parent node, filter replacement node up the tree
         if (data.at(delPos).key < data.at(delPos/2).key) 
     	    percolateUp(delPos);          
        else 
     	    percolateDown(delPos); //else percolate down //will break from function immediately if current node is less than both children
     	return 0;   
     } 
}    


//private functions:
void heap::percolateUp(int posCur){
    if (posCur!=1){
        if (data.at(posCur).key < data.at(posCur/2).key){          //integer division always truncates  
    	    mapping->setPointer(data[posCur].id, &data[posCur/2]); //swap the hash table pointers 
    	    mapping->setPointer(data[posCur/2].id, &data[posCur]); //swap the hash table pointers  
    	    std::swap(data.at(posCur),data.at(posCur/2));          //swap the heap contents      
    	    percolateUp(posCur/2);                                 //percolate up again if necessary using updated position 
        }
    }
                                                              
}


void heap::percolateDown(int posCur){
	if ((2*posCur)>filled) //returns if reaches a leaf node
		return;
	if ((2*posCur)==filled){ //layer before bottom//no right_child
        if (data.at(posCur*2).key < data.at(posCur).key){ 
	    	mapping->setPointer(data[posCur].id, &data[posCur*2]);   //swap the hash table pointers 
    	    mapping->setPointer(data[posCur*2].id, &data[posCur]);   //swap the hash table pointers 
            std::swap(data.at(posCur),data.at(posCur*2));            //swap parent and left_child
            return;
	    }
	    else
	    	return;
    }
    if ((2*posCur)<filled){ //both children valid
        int j;
        //determine which child node is smaller
        if (data.at(posCur*2).key < data.at(posCur*2+1).key)     //if left_child < right_child
    	    j = posCur*2;
		else                                                     //if left_child > right_child
    	    j = posCur*2+1;
    	//if obtained node is smaller than parent node, switch with parent node  
		if (data.at(j).key < data.at(posCur).key){
            mapping->setPointer(data[posCur].id, &data[j]); //swap the hash table pointers 
    	    mapping->setPointer(data[j].id, &data[posCur]); //swap the hash table pointers 
            std::swap(data.at(posCur),data.at(j));          //swap parent and right_child
            posCur = j;                                     //posCur = right_child 
            percolateDown(j);                               //recursive call
        }
        else
            return;
    }  
}    


int heap::getPos(node *pn){
    int pos = pn - &data[0];
    return pos;
}
