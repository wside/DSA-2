#include "hash.h"
#include <iostream>     // std::cout
#include <algorithm>    // std::lower_bound, std::upper_bound, std::sort
#include <vector>       // std::vector

hashTable::hashTable(int size){
    this->filled = 0;
    this->capacity = getPrime(size);
    std::cout << "capacity" << capacity << std::endl;
    data.resize(capacity);
   // int test = hash("atest");
    //std::cout << test << std::endl;

    /*for (auto t : data) 
    {
    	t.isOccupied = false;
    	t.isDeleted = false; 
    	//std::cout << "occ: " << t.isOccupied << std::endl;
    }*/
    //for real
    
    for (int t=0; t<capacity; t++) 
    {
    	data.at(t).isOccupied = false;
    	data.at(t).isDeleted = false; 
    }
    

    /*
    //for testing
    for (int t=0; t<capacity; t++) 
    {
    	data.at(t).key = "a";
    	data.at(t).isOccupied = true;
    	data.at(t).isDeleted = false; 
    	//std::cout << "occ: " << t.isOccupied << std::endl;
    }
    data.at(5).isDeleted = true; 
    data.at(10).isOccupied  = false; 
    data.at(113).isOccupied  = false; 
    //end of testing
    */
   
}

uint hashTable::getPrime(int size){
    std::vector<uint> primeList{53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157, 98317, 196613, 393241, 786433, 1572869, 3145739, 786433};
    std::vector<uint>::iterator upIdx;
    upIdx = std::upper_bound (primeList.begin(), primeList.end(), (size*2)); 
    
    return *upIdx;
}

int hashTable::hash(const std::string &key){
    uint hashVal=0;
    for (char ch : key)
        hashVal = 37 * hashVal + ch; 

    return (hashVal%capacity); 
    
    //for testing
    /*
    if (key=="mytest")
    	return 108;

    std::cout << "hashval: " << int(key[0]) << std::endl;
    return int(key[0]);
    */
}


int hashTable::insert(const std::string &key, void *pv){
    std::cout << "--trying to store: " << key << std::endl;
    int hashIdx;
  
    int found;
    int info;

    std::tie(found,info) = findPos(key);
    std::cout << "found: " <<found<< std::endl;
    std::cout << "info: " << info<< std::endl;
    if (found==-1){                         //key not in hash table, availbe spot open
        hashIdx = info;
        data.at(hashIdx).key = key;
        std::cout << "stored at pos: " <<  hashIdx << std::endl;
       	//stuff
   	    data.at(hashIdx).isDeleted = false; //redundancy
   	    data.at(hashIdx).isOccupied = true; 
        filled++;
        std::cout << "stored: " <<  data.at(hashIdx).key  << std::endl;
        std::cout << "filled: " <<  filled  << std::endl;
        return 0;
      
    }
    else if (found!=-2 && found!=-1){ 
    	std::cout << "key already in hash table!" << std::endl; 
    	return 1;
    }
    //redundancy
    else if(found==-2){   //rare case should not happen ever //hash table full, key not found
    	if (info!=-1){    //a deleted spot is availible 
            hashIdx = info;
            data.at(hashIdx).key = key;
            std::cout << "stored at pos: " <<  hashIdx << std::endl;
    	    //stuff
    	    data.at(hashIdx).isDeleted = false;
            filled++;
            std::cout << "stored: " <<  data.at(hashIdx).key  << std::endl;
            std::cout << "filled: " <<  filled  << std::endl;
            return 0;
        }
        else //a deleted spot is not availible 
    	    std::cout << "rehash and try agian" << std::endl; 
            //if everything occupied- rehash 
    	   //return 2 if rehash fails
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
    	std::cout << "availble spot open" << std::endl; 
        return std::make_pair(-1, IdxOrig); //return -1;
    }
  
    while (data.at(Idx).isOccupied == true){
    	//std::cout << "probing for an open spot" << std::endl;
        if ((data.at(Idx).key==key) && (data.at(Idx).isDeleted==false)){
            std::cout << "contains at pos: " <<  Idx << std::endl;
            return std::make_pair(Idx, -1); //return Idx;
        }
        if (data.at(Idx).isDeleted==true)  //if is deleted=true then send potential index back
        	availIdx = Idx;
        if (Idx==(IdxOrig-1)){
           std::cout << "Not found, also hash table completely full!" << std::endl;
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
        std::cout << "could not remove, not in table" << std::endl;
        return false;
    }
    else{ 
    	int delIdx = (findPos(key)).first;
    	std::cout << "delIdxl: " << delIdx << std::endl;
        data.at(delIdx).isDeleted = true;
        std::cout << "deletion succeful: " << std::endl;
        return true; //deletion successful
    }
}


int main(){
    

    hashTable myHashTab(90);
    myHashTab.insert("supppercallfffrgilistic");
    myHashTab.insert("thisisastringsss");
    myHashTab.insert("abd9901");
    myHashTab.insert("weee");
    myHashTab.insert("laaaa");
    myHashTab.insert("myyyy");
    myHashTab.remove("msdfdvs");
    myHashTab.insert("dssfsdfree");
    myHashTab.insert("!dffffff!");
    std::cout << "contains h?: " <<  myHashTab.contains("h")  << std::endl;
    myHashTab.insert("h");
    std::cout << "contains h?: " <<  myHashTab.contains("h")  << std::endl;
    myHashTab.insert("mytest");
    std::cout << "contains supppercallfffrgilistic?: " <<  myHashTab.contains("supppercallfffrgilistic")  << std::endl;
    std::cout << "contains laaaa?: " <<  myHashTab.contains("laaaa")  << std::endl;
    std::cout << "contains randomword1?: " <<  myHashTab.contains("randomword1")  << std::endl;

    /*hashTable myHashTab(90);
    myHashTab.insert("d");
    myHashTab.insert("e");
    myHashTab.insert("f");
    myHashTab.insert("j");
    myHashTab.insert("l");
    myHashTab.insert("m");
    myHashTab.remove("m");
    myHashTab.insert("d");
    myHashTab.insert("!");
    std::cout << "contains h?: " <<  myHashTab.contains("h")  << std::endl;
    myHashTab.insert("h");
    std::cout << "contains h?: " <<  myHashTab.contains("h")  << std::endl;
    myHashTab.insert("mytest");
    */
}

//TODO: circle back to beginning and check 