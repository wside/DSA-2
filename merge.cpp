//Wendy Ide
//Programming Assignment #4
//DSA II Prof. Sable
//12/3/18

#include <iostream>
#include <fstream>

bool arr[1001][2001] = {0}; //global 2D matrix for dynamic programming implementation


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

    std::cout << "Enter name of output file: ";
    std::cin >> outFile_name;
    ofs.open(outFile_name, std::ofstream::out);
    
    while(!ifs.eof()){
        ifs >> stringA >> stringB >> stringC;
        if (ifs.eof()) //makes sure last line doesn't duplicate
            break;    
         std::cout << stringA << " " <<  stringB << " " << stringC << std::endl; //testing, del later
        lenA = stringA.length();
        lenB = stringB.length();
        lenC = stringC.length();
     
        if (lenC != lenA+lenB){ //quick length check
             ofs << "*** NOT A MERGE ***" << std::endl; 
             continue;
         }
        
        //matrix is i,j indexed    
        for (int i=0; i<lenA+1; i++){ //fill in matrix
            for (int j=0; j<lenB+1; j++){
                arr[i][j] = false; 
                if (i==0 && j==0) 
                    arr[i][j] = true; 
                //A is empty 
                else if (i==0 && stringB[j-1]==stringC[j-1]) 
                    arr[i][j] = arr[i][j-1]; 
                //B is empty 
                else if (j==0 && stringA[i-1]==stringC[i-1]) 
                    arr[i][j] = arr[i-1][j]; 
                //Current character of C matches with current character of A, 
                //but doesn't match with current character of B 
                else if(stringA[i-1]==stringC[i+j-1] && stringB[j-1]!=stringC[i+j-1]) 
                    arr[i][j] = arr[i-1][j]; 
                //Current character of C matches with current character of B, 
                //but doesn't match with current character of A 
                else if (stringA[i-1]!=stringC[i+j-1] && stringB[j-1]==stringC[i+j-1]) 
                    arr[i][j] = arr[i][j-1]; 
                //Current character of C matches with that of both A and B 
                else if (stringA[i-1]==stringC[i+j-1] && stringB[j-1]==stringC[i+j-1]) 
                    arr[i][j]=(arr[i-1][j] || arr[i][j-1]) ; 
                    
            }
        }
        
        
   //testbench, del later
      for (int i = 0; i < lenA+1; ++i){
        for (int j = 0; j < lenB+1; ++j){
            std::cout << arr[i][j] << ' ';
        }
        std::cout << std::endl;
    }

        //backtrack to get CAPs placement for stringA
        i = lenA;  
        j = lenB;
          std::cout << "orig: " << (arr[i][j])<< std::endl; 
           std::cout << "orig i,j: " << i << ", " << j<< std::endl;
        if(arr[i][j]){  //last matrix entry indicates if merge is valid (1 if valid)
            while(i>=0 && j>=0){
                if (i==0 && j==0)
                    break;
                if (arr[i][j-1]){  //try going left first
                    std::cout << "(arr[i][j-1]: " << (arr[i][j-1])<< std::endl;
                    std::cout << "goingleft" << std::endl;
                    j--;
                }
                else if (arr[i-1][j]){   //then try going left (makes sure CAPs takes farthest left (first) availble spot for StringA)
                    std::cout << "(arr[i-1][j]: " << (arr[i-1][j])<< std::endl;
                    std::cout << "goingup" << std::endl;
                    stringC[i+j-1] = toupper(stringC[i+j-1]); //changes stringC in place
                    i--;      
                }
                
            }
             std::cout << "stgC fixed: " << stringC << std::endl; //testing, del later
            ofs << stringC << std::endl; 
        }
        else if (!arr[i][j]){
           std::cout<< "*** NOT A MERGE ***" << std::endl; //testing, del late
            ofs << "*** NOT A MERGE ***" << std::endl; 
        }
    
    } //end of big while loop


    ofs.close(); //close the output file
    return 0;

} //end of main    
