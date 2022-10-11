#include <fstream>
#include <iostream>
using namespace std;

int main(){
    srand((unsigned)time(NULL));
    ofstream fout;
    fout.open("inputFile.txt");
    for(int i=100;i<200;i++){
        int j= rand()%1000000;
        fout<<j<<endl;
    }
    fout.close();
    return 0;

}