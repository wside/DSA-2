#include "hash.h"    
#include <algorithm>  //std::upper_bound in getPrime  


//constructor
hashTable::hashTable(int size){
    this->filled = 0;
    this->capacity = getPrime(size);
    data.resize(capacity);
   
    for (int t=0; t<capacity; t++){
    	data.at(t).isOccupied = false;
    	data.at(t).isDeleted = false; 
    }
}


//getPrime stuff (private)
std::vector<uint> hashTable::primeList{53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157, 98317, 196613, 393241, 786433, 1572869, 3145739};

uint hashTable::getPrime(int size){
    std::vector<uint>::iterator upIdx;
    upIdx = std::upper_bound (primeList.begin(), primeList.end(), (size*2)); 
    
    return *upIdx;
}


//actual hash function (private)
int hashTable::hash(const std::string &key){
    uint hashVal=0;
    for (char ch : key)
        hashVal = 37 * hashVal + ch; 
   
    return (hashVal%capacity); 
}


//public functions
int hashTable::insert(const std::string &key, void *pv){
    //dynamically resize hash table if it is more than 75% full 
    if ( (filled/(1.00*capacity))>=0.75 ){ 
    	if (rehash()==false)
            return 2; //return 2 if rehash fails
    }
    
    //inserting the item
    int hashIdx;
    int found;
    int info;
    std::pair<int, int> findPosPair =  findPos(key);
    found = findPosPair.first;
    info  = findPosPair.second;
    
    if (found==-1){                         //key not in hash table, availbe spot open
        hashIdx = info;
        data.at(hashIdx).key = key;         //insert in new key
   	    data.at(hashIdx).isOccupied = true; 
        filled++;  //increment filled counter by 1
        return 0;
    }
    else if (found!=-2 && found!=-1)  //key already in hash table
    	return 1;
    //redundancy
    else if(found==-2){   //rare case should not happen ever because of rehash //hash table full, key not found
        rehash(); 
        insert(key);
    }
}


bool hashTable::remove(const std::string &key){
    if (contains(key)==false)
        return false;   //could not remove, not in table
    else{ 
        int delIdx = (findPos(key)).first;
        data.at(delIdx).isDeleted = true;
        return true; //deletion successful
    }
}


bool hashTable::contains(const std::string &key){
    if ((findPos(key)).first == -1 || (findPos(key)).first==-2)
       return false;
    else
        return true; 
}


//privte functions
std::pair<int, int> hashTable::findPos(const std::string &key){
    int IdxOrig = hash(key); //save start val 
    int Idx = IdxOrig;

    if (data.at(IdxOrig).isOccupied == false) //availble spot open at expected spot //most likely case 
        return std::make_pair(-1, IdxOrig);   //return -1;

    while (data.at(Idx).isOccupied == true){
        if ((data.at(Idx).key==key) && (data.at(Idx).isDeleted==false)) //check if key already there
            return std::make_pair(Idx, -1); //returns position index if found
        if (Idx==(IdxOrig-1))               //redundancy, should never happen  //stops while loop if wraps all the way around  
           return std::make_pair(-2, -1);   //hash table completely full! // //ignores if a deleted spot is availible because should rehash anyway
        Idx++;                              //continue searching
        if (Idx==capacity)                  //if reach end wrap around to beggining //recall vectors are zero indexed 
        	Idx=0;  
    }
     
    return  std::make_pair(-1, Idx); //availble spot open //send back first available spot
}


bool hashTable::rehash(){
    try{
    	std::vector<hashItem> dataTemp;
        dataTemp.reserve(capacity);
        dataTemp = data;                     //save entries of old in a temporary hashtable

        int capacityOrig = capacity;         //save original capacity
        capacity = getPrime((capacity/2)+1); //set new capactiy
	    data.resize(capacity);               //new table has new capacity
	    
        for (int t=0; t<capacity; t++){      //clear new table
            data.at(t).isOccupied = false;
            data.at(t).isDeleted = false; 
        }
	  
        //move all entries into new spots
        filled=0;
        for (int i=0; i<capacityOrig; i++){
            if ((dataTemp.at(i).isOccupied == true)&& (dataTemp.at(i).isDeleted==false)){ //no need to move deleted entries 
                insert(dataTemp.at(i).key);  //insert old value into new table with new hash val
            }            
        }   
        return true;
    }
    catch(std::bad_alloc&){
        return false;  //memory allocation failed!
    }

}
