#include "hash.h"

int main(){
    

    hashTable myHashTab(10);
    std::string mystring = "abcdefghijklmnopqrsAtuvwxyz@@@@!!!!";
    for (int i=0; i<mystring.length(); i++){
        std::string s(1, mystring[i]);
        if (s=="A")
                  myHashTab.insert("mytest");
        else
            myHashTab.insert(s);
        if (s=="p"){
                myHashTab.remove("p");
            std::cout << "contains " << "p" << " ?: " << myHashTab.contains("p")  << std::endl;}
    }


    // 

    for (int i=0; i<mystring.length(); i++){
        std::string r(1, mystring[i]);
        std::cout << "contains " << r << " ?: " << myHashTab.contains(r)  << std::endl;
    }
    std::cout << "contains " << "mytest" << " ?: " << myHashTab.contains("mytest")  << std::endl;

}





 /*//testing
    std::cout << "-------------------------------------------------------------------------------------------------------------------- "<< std::endl;
    D_File.clear();
    D_File.seekg(0, std::ios::beg);

    while (getline(D_File, line))
        std::cout << myHashTab.contains(line)  << std::endl;
    */




//in constructor
 
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

/*
//testing rehash
    hashTable myHashTab(10);
    std::string mystring = "abcdefghijklmnopqrstuvwxyz@@@@!!!!";
    for (int i=0; i<mystring.length(); i++){
        std::string s(1, mystring[i]);
        myHashTab.insert(s);
    }

    
    // 
    myHashTab.remove("p");
    for (int i=0; i<mystring.length(); i++){
        std::string r(1, mystring[i]);
        std::cout << "contains " << r << " ?: " << myHashTab.contains(r)  << std::endl;
    }

*/







/*

if (hashIdx==hashIdxOrig-1){
        	 	if (data.at(hashIdxOrig-1).isOccupied == false){
        	 		std::cout << "hash table full!, key not found" << std::endl;
        	 		return -1; 
        	 	}
        	 	else if ((data.at(hashIdxOrig-1).key==key) && (data.at(hashIdxOrig-1).isDeleted==false)){
        	 	    std::cout << "hash table full!, key found" << std::endl;
        	 	    return hashIdx;
        	 	}
        	 	else
        	 	return -1; */

                         /*while ((data.at(hashIdx).isOccupied == true) && (data.at(hashIdx).isDeleted == false)){
            hashIdx++;
            std::cout << "delted?: " << data.at(hashIdx).isDeleted << std::endl;
        }*/
        //if hashIdx exceed capacity check back at beginning

                   //hashItem item; 
   // item.key = key;
    //item.isOccupied = true;
  /*  int hashIdx = hash(key);
    std::cout << "occ?: " << data.at(hashIdx).isOccupied << std::endl;
    if (data.at(hashIdx).isOccupied==false){
        std::cout << "spot open" << std::endl;
        data.at(hashIdx).key = key; //put the key in
        //do rest of stuff
        data.at(hashIdx).isOccupied = true; 
        filled++;
        std::cout << "stored: " <<  data.at(hashIdx).key  << std::endl;
        std::cout << "  filled: " <<  filled  << std::endl;
        return 0;
    }*/

                  //while (data.at(hashIdx).isOccupied = true)
         //   hashIdx++;
        //data.at(hashIdx).key = key;
/*
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
    myHashTab.remove("supppercallfffrgilistic");
    std::cout << "contains supppercallfffrgilistic?: " <<  myHashTab.contains("supppercallfffrgilistic")  << std::endl;
    std::cout << "contains laaaa?: " <<  myHashTab.contains("laaaa")  << std::endl;
    std::cout << "contains randomword1?: " <<  myHashTab.contains("randomword1")  << std::endl;
*/

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