#include <iostream>
#include <fstream>
#include <unordered_map>
using namespace std;

void radixSort(int r, int c, char** P, char** S){
    
    for(int j=c-1;j>=0;j--){
        int counts[27]={0};
        unordered_map<int,char*> map;
        for(int i=0;i<r;i++){
            char c = P[i][j];
            if(isspace(c)){
                counts[0]++;
            }
            else{
                counts[(c-'A')+1]++;
            }
        }
        for(int i=1;i<27;i++){
          counts[i]+=counts[i-1];
         }
         for(int i=r-1;i>=0;i--){
            char c = P[i][j];
            int index;
            if(isspace(c)){
                index=counts[0]-1;
                counts[0]-=1;
            }
            else{
            index = counts[(c-'A')+1]-1;
            counts[(c-'A')+1]-=1;
            }
          
            map[index]=P[i];
         }
         for(int i=0;i<r;i++){
            P[i]=map[i];
         }

    }
}
int populateSArray(char** S){
    ifstream infile;
    infile.open("f.txt");
    int index=0;
    if(infile.is_open()){
        string str;
        while( (index<1000) && (infile>>str) ){
            char* arr = S[index];
            for(int i=0;i<21;i++){
                if(i>=str.length()){
                    arr[i]=' ';
                }
                else{
                    arr[i]=toupper(str[i]);
                }
            }
            index++;
        }
    }
    infile.close();
    return index;
}

void initializePArray(char** P, char** S, int r){
    for(int i=0;i<r;i++){
        P[i] = S[i];
    }
}

int main(){

    char** S = new char*[1000];
    for(int i=0;i<1000;i++){
        S[i]=new char[21];
    }
    int numWords=populateSArray(S);


    char* P[numWords];
    initializePArray(P,S,numWords);

    radixSort(numWords,21,P,S);
    for(int i=0;i<numWords;i++){
        for(int j=0;j<21;j++){
            if(isspace(P[i][j]))break;
            cout<<P[i][j];
        }
        cout<<endl;
    }

    for(int i=0;i<1000;i++){
        delete[] S[i];
    }
    delete[] S;


    return 0;
                                                                
        }
