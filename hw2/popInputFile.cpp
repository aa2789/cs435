#include <fstream>
#include <iostream>
using namespace std;

int main(){
    srand((unsigned)time(NULL));
    ofstream fout;
    fout.open("inputFile.txt");
    for(int i=0;i<1048576;i++){
        int j= rand()%10000000;
        fout<<j<<endl;
    }
    fout.close();
    return 0;

}