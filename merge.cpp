//Wendy Ide
//Programming Assignment #4
//DSA II Prof. Sable
//12/3/18

#include <iostream>
#include <fstream>
#include <algorithm> //std::max
#include <ctime> //del later if not used

bool arr[1001][2001] = {0};


int main(){
    std::ifstream ifs;
    std::ofstream ofs;
    std::string inFile_name, outFile_name; 
    std::string stringA, stringB,stringC;
    int lenA, lenB, lenC;
    int j, i; 

    std::cout << "Enter name of input file: ";
    std::cin >> inFile_name;
    ifs.open(inFile_name, std::ifstream::in);
   
    arr[0][0] = 1; //never gets overwritten 
    while(!ifs.eof()){
        ifs >> stringA >> stringB >> stringC;
        if (ifs.eof()) //makes sure last line doesn't duplicate
            break;
        std::cout << stringA << " " <<  stringB << " " << stringC << std::endl; //testing, del later
        lenA = stringA.length();
        lenB = stringB.length();
        lenC = stringC.length();
        std::cout << lenA << " " <<  lenB << " " << lenC << std::endl; //testing, del later
        
        if (lenC != lenA+lenB){ //quick length check
            std::cout << "*** NOT A MERGE ***" << std::endl;
             continue;
        }
        
        /*
        for (int i=1; i<lenA+1; i++){ //fill first row (go down width of array)
            if (stringC[i-1] == stringA[i-1])
                arr[0][i] = arr[0][i-1];
            else 
                arr[0][i] = 0;
        }

        for (int j=1; j<lenB+1; j++){ //fill first column (go down height of array)
            if (stringC[j-1] == stringB[j-1])
                arr[j][0] = arr[j-1][0];
            else
                arr[j][0] = 0;
        }
        */
        for (int j=0; j<lenB+1; j++){ //fill rest of matrix
            for (int i=0; i<lenA+1; i++){
                //  std::cout << "j,i: " << j << ", " << i << std::endl;
                if (stringC[i+j-1]==stringA[i-1]){ 
                   // std::cout << "hit stringA" << std::endl;
                   // std::cout << i+j-1 << " " << stringC[i+j-1] << ", " << i-1 << " " << stringA[i-1] << std::endl;
                   //std::cout << "arr[j][i-1] " << arr[j][i-1] << std::endl;
                    if (arr[j][i-1]==1)
                        arr[j][i] = arr[j][i-1]; //same as left
                    //std::cout << "set a[j][i] " << arr[j][i]<< std::endl;
                }
                if (stringC[i+j-1]==stringB[j-1]){
                   // std::cout << "hit stringB" << std::endl;
                   // std::cout << i+j-1 << " " << stringC[i+j-1] << ", " << j-1 << " " << stringB[j-1] << std::endl;
                   // std::cout << "arr[j-1][i] " << arr[j-1][i]<< std::endl;
                    if (arr[j-1][i]==1)
                        arr[j][i] = arr[j-1][i]; //same as above
                    //std::cout << "set a[j][i] " << arr[j][i]<< std::endl;
                }
                else if (stringC[i+j-1]!=stringA[i-1]){
                    arr[j][i] = 0;
                }  
            }
        }



   //testbench, del later
    for (int i = 0; i < lenB+1; ++i)
    {
        for (int j = 0; j < lenA+1; ++j)
        {
            std::cout << arr[i][j] << ' ';
        }
        std::cout << std::endl;
    }

// 
        j = lenB;
        i = lenA;   
        if(arr[j][i]==1){  //last entry indicates if merge is valid
            std::cout << "merge is correct" << std::endl;
            while(j!=0 || i!=0){
                if (arr[j-1][i]==1){   //try going up first
                    //std::cout << "goingup" << std::endl;
                    j--;
                }       
                else if (arr[j][i-1]==1){  //then try left
                    //std::cout << "goingleft" << std::endl;
                    stringC[i+j-1] = toupper(stringC[i+j-1]);
                    i--;
                }
            }
                
            
         std::cout << "stringC fixed: " << stringC << std::endl; //testing, del later
        }
        else
            std::cout << "*** NOT A MERGE ***" << std::endl;
        
        
        std::cout << "------------------------- " << std::endl;

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