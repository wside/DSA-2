//Wendy Ide
//Programming Assignment #4
//DSA II Prof. Sable
//12/3/18

#include <iostream>
#include <fstream>
#include <ctime> //del later if not used

int arr[1001][2001] = {0};

int main(){
    std::ifstream ifs;
    std::ofstream ofs;
    std::string inFile_name;
    std::string outFile_name; 
    std::string stringA;
    std::string stringB;
    std::string stringC;
    int lenA;
    int lenB;
    int lenC;

    std::cout << "Enter name of input file: ";
    std::cin >> inFile_name;
    ifs.open(inFile_name, std::ifstream::in);
   
    while(!ifs.eof()){
        ifs >> stringA >> stringB >> stringC;
        if (ifs.eof()) //makes sure last line doesn't duplicate
            break;
        std::cout << stringA << " " <<  stringB << " " << stringC << std::endl; //testing, del later
        lenA = stringA.length();
        lenB = stringB.length();
        lenC = stringC.length();
        std::cout << lenA << " " <<  lenB << " " << lenC << std::endl; //testing, del later
        
        if (lenC != lenA+lenB){ //quick check
             std::cout << "*** NOT A MERGE ***" << std::endl;
             continue;
         }
        
          std::cout << "testst" << std::endl; 
        //for (inti=0; i < lenA; i++){
        //}
           
        

          



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