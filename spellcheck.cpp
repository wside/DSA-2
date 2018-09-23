#include "hash.h"
#include <iostream>
#include <fstream>

void Lookup(std::ofstream &ofs, std::string Word, int lineNum){
    if (Word.length()>20)
        //std::cout 
        ofs << "Long word at line " << lineNum << ", starts: " << Word.substr(0,20) << std::endl;
    //if (unknown word)
        //std::cout << "Unknown word at line " << lineNum << ": " << Word << std::endl;
}



int main(){

    //construct hash table object
    hashTable myHashTab(10); //will dynamically grow if needed
    
    //load dictionary
    int count = 0;
    std::string line;
 
    std::ifstream D_File;
    D_File.open("wordlist_small.txt", std::ifstream::in);
    while (getline(D_File, line))
        myHashTab.insert(line);
        //std::cout << line << std::endl;
   
    //testing
    std::cout << "---------------------------------------------------- "<< std::endl;
    D_File.clear();
    D_File.seekg(0, std::ios::beg);

    while (getline(D_File, line))
        std::cout << "contains " << line << " ?: " << myHashTab.contains(line)  << std::endl;

   
    



    //check document
    char ch;
    std::string currentWord;
    int lineNum=1;
	
    //open output file for writing
    std::ofstream ofs;
    ofs.open("output.txt", std::ofstream::out);
	
    //open input file for reading
    //assumes input file is valid text file (it ends in a newline char)
    std::ifstream ifs;
    ifs.open("sample.txt", std::ifstream::in);
	
    while (ifs >> std::noskipws >> ch) {
        if (std::isalnum(ch) || ch=='-' || ch=='\'')
            currentWord.push_back(tolower(ch));
        else{
            if (!currentWord.empty()){
                std::cout << currentWord << std::endl;  //lookup function here
                Lookup(ofs, currentWord, lineNum);
                currentWord.erase();
            }
            if (ch =='\n'){
                lineNum++;
                std::cout << "line: " << lineNum << std::endl; 
            }
        }
    } 

    ofs.close(); //close the output file
    return 0;
}
