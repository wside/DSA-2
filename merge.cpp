//Wendy Ide
//Programming Assignment #4
//DSA II Prof. Sable
//12/3/18

#include <iostream>
#include <fstream>
#include <ctime>


int main(){
    std::ifstream ifs;
    std::string inFile_name;
    std::ofstream ofs;
    std::string outFile_name; 
   
    std::string line;
    short type = 1;

    std::cout << "Enter name of input file: ";
    std::cin >> inFile_name;
    ifs.open(inFile_name, std::ifstream::in);
   
    while (getline(ifs, line)){
        if (type==1) //the first string
            std::cout << type << std::endl;
        else if (type==2)  //the second string
            std::cout << type << std::endl;
        else //type=0, the merged string
            std::cout << type << std::endl;

        std::cout << line << std::endl;
        type = (type+1)%3;
    }

   //2d matrix
   //do stuff


////////////////////////////////////////////////////
    std::cout << "Enter name of output file: ";
    std::cin >> outFile_name;
    ofs.open(outFile_name, std::ofstream::out);
    //process the output file
    std::cout << "------------------" << std::endl; //for testing, delete later
    std::cout << "outputfile processed" << std::endl; //for testing, delete later
    
    ofs.close(); //close the output file

    return 0;

} //end of main    