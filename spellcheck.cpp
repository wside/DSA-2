#include <iostream>
#include <fstream>

int main(){

	std::string currentWord;
	int lineNum=1;
	char ch;
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
    			currentWord.erase();
    		}
    		if (ch =='\n'){
            	lineNum++;
            	std::cout << "line: " << lineNum << std::endl; 
            }
    	}
	} 


}