#ifndef _HASH_H
#define _HASH_H

#include <vector>
#include <string>
typedef unsigned int uint;

class hashTable {

    public:
        //The constructor insilizates the hash table
        //Uses getPrime to choose a prime number at least twice as large as
        //The specified size for the initial size of the hash table.
        hashTable(int size=0);   
        
        //Insert the specified key into the hash table.
        //Returns 0 on success, 1 if key already exists in hash table, 2 if rehash fails.
        int  insert(const std::string &key, void *pv = NULL);
        
        //If specified key is in hash table, return true; otherwise, return false.
        bool contains(const std::string &key);
        
        //Delete the item with the specified key.
        //Returns true on success, false if the specified key is not in the hash table.
        bool remove(const std::string &key);

        //To be implemented later 
        void *getPointer(const std::string &key, bool *b = NULL);
        int  setPointer(const std::string &key, void *pv);
        
    private:
        //the "structure" of each hash table entry
        class hashItem {
            public:
                std::string key;
                bool isOccupied;
                bool isDeleted;
                void *pv;
        };

        int capacity;  //The current capacity of the hash table.
        int filled;    //Number of occupied items in the table.

        std::vector<hashItem> data; //The actual entries are here.

        int  hash(const std::string &key);   //The hash function. 
        
        //Search for an item with the specified key.
        //First of pair returns item's index if found, or -1 if not found, 
        //or -2 if table is full (should never happen, but implemented as a safety)
        //Second of pair returns next availbe postion, or -1(no-op) if item's index was found
        std::pair<int, int> findPos(const std::string &key); 
        
        //The rehash function; makes the hash table bigger.
        //Returns true on success, false if memory allocation fails.
        bool rehash();
         
        static uint getPrime(int size);      //Return a prime number at least twice as large as size. 
        static  std::vector<uint> primeList; //precomputed list found from internet

};


#endif //_HASH_H
