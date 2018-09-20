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

    char ch;
    std::string currentWord;
    int lineNum=1;
	
    //open output file for writing
    std::ofstream ofs;
    ofs.open("output.txt", std::ofstream::out);
	
    //open input file for reading
    std::ifstream ifs;
    ifs.open("sample.txt", std::ifstream::in);
	
    while (ifs >> std::noskipws >> ch) {
        if (std::isalnum(ch) || ch=='-' || ch=='\''){
            currentWord.push_back(ch);
            if (ifs.peek(), ifs.eof())
                std::cout << currentWord << std::endl;  //lookup function here
        }
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