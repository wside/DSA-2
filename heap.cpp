#include "heap.h"   
#include <iostream>

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
    std::cout << "filled: " << filled << std::endl;
    std::cout << "posCur: " << posCur << std::endl;
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
        //test block delete later
        std::cout << "filled after insert: " << filled << std::endl;
        for(int i=1;i<filled+1;i++){
        	std::cout << "position: " << i << "  contains key: " << data.at(i).key << "  stringID: " << data.at(i).id << std::endl;
        }

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
        //del later
         std::cout << std::endl;
        for(int i=1;i<filled+1;i++){
            std::cout << "position: " << i << "  contains key: " << data.at(i).key << "  stringID: " << data.at(i).id << std::endl;
        }

     	return 0;        
    }
}


int heap::deleteMin(std::string *pId, int *pKey, void *ppData){
    if (filled == 0)
    	return 1;
    else{
        if (pId!=NULL)
       	    *pId = data[1].id; 
        if (pKey!=NULL)
        	*pKey = data[1].key; 
        if (ppData!=NULL)
        	*(static_cast<void **> (ppData)) = data[1].pData;
        //"delete" the root by switching the root and the last node
        //then deleteing the contents of the last node
        std::cout << "filleddelmininit: " << filled << std::endl;
         std::cout << "idinitfirstswitch: " << data.at(1).id << std::endl;
         std::cout << "keyinitfirstswitch: " << data.at(1).key << std::endl;
        mapping->setPointer(data[filled].id, &data[1]);
        mapping->remove(data[1].id);
        std::swap(data.at(filled),data.at(1)); 
        //for testing delete later 
         std::cout << "idafterfirstswitch: " << data.at(1).id << std::endl;
         std::cout << "keyafterfirstswitch: " << data.at(1).key << std::endl;

        data.at(filled).id = "";
        data.at(filled).key = 0;
        data.at(filled).pData = NULL;
        //test block delete later
        for(int i=1;i<filled+1;i++){
            std::cout << "position: " << i << "  contains key: " << data.at(i).key << "  stringID: " << data.at(i).id << std::endl;
        }


        filled--;
        std::cout << "filled after deleteMin: " << filled << std::endl;
        //test block delete later
        percolateDown(1);  
        return 0;
    }
} 


int heap::remove(const std::string &id, int *pKey, void *ppData){ //finish later
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
        std::cout << "filled after remove: " << filled << std::endl;
        //if replacement node < parent node, filter replacement node up the tree
         if (data.at(delPos).key < data.at(delPos/2).key) 
     	    percolateUp(delPos);          
        else 
     	    percolateDown(delPos); //else percolate down //will break from function immediately if current is less than both children
     	return 0;   
     } 
}    


//private functions:
 void heap::percolateUp(int posCur){
     
    if (posCur!=1){
        if (data.at(posCur).key < data.at(posCur/2).key){          //integer division always truncates  
    	    mapping->setPointer(data[posCur].id, &data[posCur/2]); //swap the hash table pointers 
    	    mapping->setPointer(data[posCur/2].id, &data[posCur]); //swap the hash table pointers  
    	    std::swap(data.at(posCur),data.at(posCur/2));               //swap the heap contents      
    	//posCur = (posCur/2);                                   //update current position 
    	    percolateUp(posCur/2);
        }
    }
                                                              //percolate up again if necessary 
 }


void heap::percolateDown(int posCur){
	//breaks if reaches a leaf node
	std::cout << "posCur " << posCur << std::endl;
	std::cout << "bool " << ((posCur*2)>filled) << std::endl;
	if ((2*posCur)>filled) //at bottom
		return;
	if ((2*posCur)==filled){
        if (data.at(posCur*2).key < data.at(posCur).key){ 
	    	mapping->setPointer(data[posCur].id, &data[posCur*2]);   //swap the hash table pointers 
    	    mapping->setPointer(data[posCur*2].id, &data[posCur]);   //swap the hash table pointers 
            std::swap(data.at(posCur),data.at(posCur*2));                 //swap parent and left child
              
            for(int i=1;i<filled+1;i++){
                std::cout << "position: " << i << "  contains key: " << data.at(i).key << "  stringID: " << data.at(i).id << std::endl;
            }
            return;
	    }
	    else
	    	return;
    }
    if ((2*posCur)<filled){
        int j;
        //determine which child node is smaller
        if (data.at(posCur*2).key < data.at(posCur*2+1).key)     //if left child < right child
    	    j = posCur*2;
		else                                                      //if left child > right child
    	    j = posCur*2+1;
    	//if obtained node smaller than parent node, switch with parent node  
		if (data.at(j).key < data.at(posCur).key){
            mapping->setPointer(data[posCur].id, &data[j]); //swap the hash table pointers 
    	    mapping->setPointer(data[j].id, &data[posCur]); //swap the hash table pointers 
            std::swap(data.at(posCur),data.at(j));               //swap parent and right child
            posCur = j;                                     //posCur = rightchild 
            //test block delete later
            for(int i=1;i<filled+1;i++){ std::cout << "position: " << i << "  contains key: " << data.at(i).key << "  stringID: " << data.at(i).id << std::endl;}

            percolateDown(j);
        }
        else
            return;
    }  
}    




 






/*
	if ((posCur*2)<filled) {
	//breaks from inner while loop if BOTH children are greater than the parent 
	    while ( (data.at(posCur).key > data.at(posCur*2).key) || (data.at(posCur).key > data.at(posCur*2+1).key) ){ 
	    	if ((posCur*2+1)>filled){
	    		std::cout << "here " << std::endl;
 
	    		if (data.at(posCur*2).key < data.at(posCur).key){ 
	    			mapping->setPointer(data[posCur].id, &data[posCur*2]);   //swap the hash table pointers 
    	            mapping->setPointer(data[posCur*2].id, &data[posCur]);   //swap the hash table pointers 
                    std::swap(data.at(posCur),data.at(posCur*2));                 //swap parent and left child
                    
                    for(int i=1;i<filled+1;i++){
                     std::cout << "position: " << i << "  contains key: " << data.at(i).key << std::endl;
                     }

                     posCur = posCur*2; 
                     percolateDown(posCur);

                    }
                else{
                    std::cout << "here2 " << std::endl;
                	return;
                }
	    	}
		    if (data.at(posCur*2).key > data.at(posCur*2+1).key){        //if left child > right child
    	        mapping->setPointer(data[posCur].id, &data[posCur*2+1]); //swap the hash table pointers 
    	        mapping->setPointer(data[posCur*2+1].id, &data[posCur]); //swap the hash table pointers 
                std::swap(data.at(posCur),data.at(posCur*2+1));               //swap parent and right child
                posCur = posCur*2+1;                                     //posCur = rightchild 
                percolateDown(posCur);

                 //test block delete later
               for(int i=1;i<filled+1;i++){
                std::cout << "position: " << i << "  contains key: " << data.at(i).key << std::endl;
                }
		    } 
		    else{                                                        //if left child < right child
    	        mapping->setPointer(data[posCur].id, &data[posCur*2]);   //swap the hash table pointers 
    	        mapping->setPointer(data[posCur*2].id, &data[posCur]);   //swap the hash table pointers 
                std::swap(data.at(posCur),data.at(posCur*2));                 //swap parent and left child
                posCur = posCur*2;                                       //posCur = leftchild         
                percolateDown(posCur);

                 //test block delete later
               for(int i=1;i<filled+1;i++){
               std::cout << "position: " << i << "  contains key: " << data.at(i).key << std::endl;
                }
		    }
	    }  
      
           

	}//percolate down again if necessary                                                              
}
*/

int heap::getPos(node *pn){
    int pos = pn - &data[0];
    return pos;
}
