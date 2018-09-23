#include "hash.h"
#include <iostream>
#include <fstream>

bool contains_num(std::string Word){
    for(auto &ch: Word){
        if (std::isdigit(ch)==true)
            return true;
    }
    return false;
}


int main(){

    //construct hash table object
    hashTable myHashTab(50000); //will dynamically grow if needed
    
    //load dictionary
    int count = 0;
    std::string line;
 
    std::ifstream D_File;
    D_File.open("wordlist_small.txt", std::ifstream::in);
    while (getline(D_File, line))
        myHashTab.insert(line);
        //std::cout << line << std::endl;
   
    /*//testing
    std::cout << "-------------------------------------------------------------------------------------------------------------------- "<< std::endl;
    D_File.clear();
    D_File.seekg(0, std::ios::beg);

    while (getline(D_File, line))
        std::cout << myHashTab.contains(line)  << std::endl;
    */


   
    



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
    ifs.open("lyrics.txt", std::ifstream::in);
	
    while (ifs >> std::noskipws >> ch) {
        if (std::isalnum(ch) || ch=='-' || ch=='\'')
            currentWord.push_back(tolower(ch));
        else{
            if (!currentWord.empty()){
                std::cout << currentWord << std::endl;  //lookup function here
                //Lookup word or check if its long
                if (currentWord.length()>20){
                   // std::cout << "here1" << std::endl;
                    ofs << "Long word at line " << lineNum << ", starts: " << currentWord.substr(0,20) << std::endl;
                }
                else{
                    //std::cout << "here2" << std::endl;
                    if (contains_num(currentWord)==false){
                       // std::cout << "here3" << std::endl;
                        if ( myHashTab.contains(currentWord)==false)
                            ofs << "Unknown word at line " << lineNum << ": " << currentWord << std::endl;
                    }
                }               
                currentWord.erase(); //erase current word to prepare for next
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
