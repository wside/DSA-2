#ifndef _HASH_H
#define _HASH_H

#include <vector>
#include <string>
typedef unsigned int uint;

class hashTable {

    public:
        hashTable(int size=0);  
        int  insert(const std::string &key, void *pv = NULL);
        bool contains(const std::string &key);
        void *getPointer(const std::string &key, bool *b = NULL);
        int  setPointer(const std::string &key, void *pv);
        bool remove(const std::string &key);

    private:
        class hashItem {
            public:
                std::string key;
                bool isOccupied;
                bool isDeleted;
                void *pv;
        };

        int capacity; // The current capacity of the hash table.
        int filled;   // Number of occupied items in the table.

        std::vector<hashItem> data; // The actual entries are here.

        int  hash(const std::string &key);   // The hash function.
        std::pair<int, int> findPos(const std::string &key);
        bool rehash();

        static uint getPrime(int size);
};


#endif //_HASH_H