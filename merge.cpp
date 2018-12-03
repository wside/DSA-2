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
    int i, j;  //for backtracking later

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
        lenA = stringA.length();
        lenB = stringB.length();
        lenC = stringC.length();
     
        if (lenC != lenA+lenB){ //quick length check
             ofs << "*** NOT A MERGE ***" << std::endl; 
             continue;
         }
        
        //matrix is i,j indexed    
        for (int i=0; i<lenA+1; i++){ //fill in boolean matrix
            for (int j=0; j<lenB+1; j++){
                arr[i][j] = false;   //preset to false
                if (i==0 && j==0) 
                    arr[i][j] = true; 
                else if (i==0 && stringB[j-1]==stringC[j-1]) //A is empty 
                    arr[i][j] = arr[i][j-1]; 
                else if (j==0 && stringA[i-1]==stringC[i-1]) //B is empty 
                    arr[i][j] = arr[i-1][j]; 
                else if(stringA[i-1]==stringC[i+j-1] && stringB[j-1]!=stringC[i+j-1]) //current C char matches current A char, but not current B char
                    arr[i][j] = arr[i-1][j]; 
                else if (stringA[i-1]!=stringC[i+j-1] && stringB[j-1]==stringC[i+j-1]) //C matches B, but not A
                    arr[i][j] = arr[i][j-1]; 
                else if (stringA[i-1]==stringC[i+j-1] && stringB[j-1]==stringC[i+j-1]) //C matches both A and B
                    arr[i][j]=(arr[i-1][j] || arr[i][j-1]) ; 
            }
        }
        
        //backtrack to get CAPs placement for stringA
        i = lenA;  
        j = lenB;
        if(arr[i][j]){  //last matrix entry indicates if merge is valid (1 if valid)
            while(i>=0 && j>=0){
                if (i==0 && j==0)
                    break;
                if (arr[i][j-1])  //try going left first
                    j--;
                else if (arr[i-1][j]){   //then try going left (makes sure CAPs takes farthest left (first) availble spot for StringA)
                    stringC[i+j-1] = toupper(stringC[i+j-1]); //changes stringC in place
                    i--;      
                }
                
            }
            ofs << stringC << std::endl; 
        }
        else if (!arr[i][j])
            ofs << "*** NOT A MERGE ***" << std::endl; 
    
    } //end of big while loop

    ofs.close(); //close the output file
    return 0;

} //end of main    
