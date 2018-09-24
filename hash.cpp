#include "hash.h"
#include <iostream>     // ////std::cout
#include <algorithm>    // std::lower_bound, std::upper_bound, std::sort


//constructor
hashTable::hashTable(int size){
    this->filled = 0;
    this->capacity = getPrime(size);
    ////std::cout << "capacity" << capacity << std::endl;
    data.resize(capacity);
    ////std::cout << "data capacity" << data.capacity() << std::endl;
   
    for (int t=0; t<capacity; t++){
    	data.at(t).isOccupied = false;
    	data.at(t).isDeleted = false; 
    }
}

std::vector<uint> hashTable::primeList{53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157, 98317, 196613, 393241, 786433, 1572869, 3145739};

uint hashTable::getPrime(int size){
    std::vector<uint>::iterator upIdx;
    upIdx = std::upper_bound (primeList.begin(), primeList.end(), (size*2)); 
    
    return *upIdx;
}

int hashTable::hash(const std::string &key){
    uint hashVal=0;
    for (char ch : key)
        hashVal = 37 * hashVal + ch; 
    
    if (key=="mytest")
        return 2;

    //std::cout << "hashval: " << (hashVal%capacity) << std::endl;
    return (hashVal%capacity); 
    
    /*
    //for testing
    
    */
    /*
    ////std::cout << "hashval: " << int(key[0]) << std::endl;
    return int(key[0]);
    */
}


int hashTable::insert(const std::string &key, void *pv){
    if ( (filled/(1.00*capacity))>=0.50 ) //dynamically resize hash table if it is more than half full 
    	rehash();

    //std::cout << "--trying to store: " << key << std::endl;
    int hashIdx;
  
    int found;
    int info;

    std::tie(found,info) = findPos(key);
    ////std::cout << "found: " <<found<< std::endl;
    ////std::cout << "info: " << info<< std::endl;
    if (found==-1){                         //key not in hash table, availbe spot open
        hashIdx = info;
        data.at(hashIdx).key = key;
        ////std::cout << "stored at pos: " <<  hashIdx << std::endl;
       	//stuff
   	   
   	    data.at(hashIdx).isOccupied = true; 
        if (data.at(hashIdx).isDeleted == true)
            data.at(hashIdx).isDeleted = false;  //if replacing a deleted entry don't increase filled
        else
            filled++;
        //std::cout << "stored: " <<  data.at(hashIdx).key  << " at pos: " << hashIdx << std::endl;
        //std::cout << "filled: " <<  filled  << std::endl;
        return 0;
      
    }
    else if (found!=-2 && found!=-1){ 
    	////std::cout << "key already in hash table!" << std::endl; 
    	return 1;
    }
    //redundancy
    else if(found==-2){   //rare case should not happen ever //hash table full, key not found
    	if (info!=-1){    //a deleted spot is availible 
            hashIdx = info;
            data.at(hashIdx).key = key;
    	    data.at(hashIdx).isDeleted = false;
            filled++;
            return 0;
        }
        else{ //a deleted spot is not availible 
            rehash(); 
            insert(key);
    	}
    }

    	   
}


bool hashTable::contains(const std::string &key){
    if ((findPos(key)).first == -1 || (findPos(key)).first==-2)
       return false;
    else
        return true; 
}


std::pair<int, int> hashTable::findPos(const std::string &key){
    int IdxOrig = hash(key); //save start val 
    int Idx = IdxOrig;
    int availIdx = -1;

    if (data.at(IdxOrig).isOccupied == false){
    	////std::cout << "availble spot open" << std::endl; 
        return std::make_pair(-1, IdxOrig); //return -1;
    }
  
    while (data.at(Idx).isOccupied == true){
        if ((data.at(Idx).key==key) && (data.at(Idx).isDeleted==false)){
            //////std::cout << "contains at pos: " <<  Idx << std::endl;
            return std::make_pair(Idx, -1); //return Idx;
        }
        if (data.at(Idx).isDeleted==true)  //if is deleted=true then send potential index back
        	availIdx = Idx; 
        if (Idx==(IdxOrig-1)){
           ////std::cout << "Not found, also hash table completely full!" << std::endl;
           return std::make_pair(-2, availIdx);
        }
        Idx++; 
        if (Idx==capacity) //if reach end wrap around to beggining 
        	Idx=0;  
        
    }
    
    if (availIdx==-1)
    	availIdx = Idx;
    return  std::make_pair(-1, availIdx); 
}


bool hashTable::remove(const std::string &key){
    if (contains(key)==false){
        ////std::cout << "could not remove, not in table" << std::endl;
        return false;
    }
    else{ 
    	int delIdx = (findPos(key)).first;
    	////std::cout << "delIdxl: " << delIdx << std::endl;
        data.at(delIdx).isDeleted = true;
        ////std::cout << "deletion succeful: " << std::endl;
        return true; //deletion successful
    }
}

bool hashTable::rehash(){
    try{
    	//save entries of old in a temporary hashtable
    	std::vector<hashItem> dataTemp;
        dataTemp.reserve(capacity);
        dataTemp = data;

        int capacityOrig = capacity;
        capacity = getPrime((capacity/2)+1); //set new capactiy
	    data.resize(capacity);
	    
	    dataTemp.resize(capacity);
	    for (int t=0; t<capacity; t++){  //clear original table
    	    data.at(t).isOccupied = false;
     	    data.at(t).isDeleted = false; 
        }
	    ////std::cout << "new capacity: " << dataTemp.capacity() << std::endl;
	    //std::cout << "new capacity varible saved: " <<  capacity << std::endl;
        //move all entries into new spots
        filled=0;
        for (int i=0; i<capacityOrig; i++){
            if ((dataTemp.at(i).isOccupied == true)&& (dataTemp.at(i).isDeleted==false)){ //no need to move deleted entries 
                //std::cout << "---trying to rehash item: " << dataTemp.at(i).key << std::endl;
                insert(dataTemp.at(i).key);
            }            
        }   

        return true;
    }
    catch(std::bad_alloc&){
        ////std::cout << "memoery allocation failed! " << std::endl;
        return false;
    }
}
