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
   
    arr[0][0] = 1; //never gets overwritten 
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
               
        for (int j=0; j<lenB+1; j++){ //fill in matrix
            for (int i=0; i<lenA+1; i++){
                if (stringC[i+j-1]==stringA[i-1]){ 
                    if (arr[j][i-1])
                        arr[j][i] = arr[j][i-1]; //same as left
                }
                if (stringC[i+j-1]==stringB[j-1]){
                    if (arr[j-1][i])
                        arr[j][i] = arr[j-1][i]; //same as above
                }
                else if (stringC[i+j-1]!=stringA[i-1]){
                    arr[j][i] = 0;
                }  
            }
        }
        
        //backtrack to get CAPs placement for stringA
        j = lenB;
        i = lenA;   
        if(arr[j][i]){  //last matrix entry indicates if merge is valid (1 if valid)
            while(j>=0 && i>=0){
                if (j==0 && i==0)
                    break;
                if (arr[j-1][i])   //try going up first
                    j--;      
                else if (arr[j][i-1]){  //then try going left
                    stringC[i+j-1] = toupper(stringC[i+j-1]); //changes stringC in place
                    i--;
                }
            }
            ofs << stringC << std::endl; //testing, del later
        }
        else if (arr[j][i]==0)
            ofs << "*** NOT A MERGE ***" << std::endl; 
    
    } //end of big while loop


    ofs.close(); //close the output file
    return 0;

} //end of main    

