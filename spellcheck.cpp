//Wendy Ide
//Programming Assignment #1 - Dictionary
//DSA II Prof. Sable
//09/23/2018

#include "hash.h"
#include <iostream>
#include <fstream>
#include <ctime>

bool contains_num(std::string Word){ //function to check if a word has a number 
    for(auto &ch: Word){
        if (std::isdigit(ch)==true)
            return true;
    }
    return false;
}

int main(){
    
    //get filenames from user command line
    std::string Dictionary_name;
    std::string inFile_name;
    std::string outFile_name;
    
    //construct hash table object
    hashTable myHashTab(50000); //will dynamically grow if needed
    
    //load dictionary
    std::cout << "Enter name of dictionary:  ";
    std::cin >> Dictionary_name;

    std::string line;
    std::ifstream D_File;
    D_File.open(Dictionary_name, std::ifstream::in);
    clock_t begin1 = clock();
    while (getline(D_File, line))
        myHashTab.insert(line);
    clock_t end1 = clock();
    double elapsed_secs_load = double(end1 - begin1) / CLOCKS_PER_SEC;
    std::cout << "Total time (in seconds) to load dictionary: " << elapsed_secs_load << std::endl;

    //check document
    char ch;
    std::string currentWord;
    int lineNum=1;
	
    //from command line
    std::cout << "Enter name of input file:  ";
    std::cin >> inFile_name;
    std::cout << "Enter name of output file:  ";
    std::cin >> outFile_name;

    //open output file for writing
    std::ofstream ofs;
    ofs.open(outFile_name, std::ofstream::out);
	
    //open input file for reading
    //assumes input file is valid text file (it ends in a newline char)
    std::ifstream ifs;
    ifs.open(inFile_name, std::ifstream::in);
	
    clock_t begin2 = clock();
    while (ifs >> std::noskipws >> ch) {
        if (std::isalnum(ch) || ch=='-' || ch=='\'')
            currentWord.push_back(tolower(ch));
        else{
            if (!currentWord.empty()){
                //std::cout << currentWord << std::endl;  //lookup function here
                //Lookup word or check if its long
                if (currentWord.length()>20)
                    ofs << "Long word at line " << lineNum << ", starts: " << currentWord.substr(0,20) << std::endl;
                else{
                    if (contains_num(currentWord)==false){
                        if ( myHashTab.contains(currentWord)==false)
                            ofs << "Unknown word at line " << lineNum << ": " << currentWord << std::endl;
                    }
                }               
                currentWord.erase(); //erase current word to prepare for next
            }
            if (ch =='\n'){
                lineNum++;
                //std::cout << "line: " << lineNum << std::endl; 
            }
        }
    } 
    clock_t end2 = clock();
    double elapsed_secs_check = double(end2 - begin2) / CLOCKS_PER_SEC;
    std::cout << "Total time (in seconds) to check document: " << elapsed_secs_check << std::endl;


    ofs.close(); //close the output file
    return 0;
}
