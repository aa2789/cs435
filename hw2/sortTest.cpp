#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <chrono>
#include <bits/stdc++.h>

using namespace std; 

void populateArray(int* arr, int n){
    ifstream infile;
    infile.open("inputFile.txt");
    int index=0;
    if(infile.is_open()){
        int num;
        while( (index<n) && (infile>>num) ){
            arr[index++]=num;
        }
    }
    infile.close();

}

int main(){
    int * arr = new int[1048576];
    populateArray(arr,1048576);
    cout<<arr[0]<<"  "<<arr[1048575]<<endl;
    auto start = chrono::steady_clock::now();
    sort(arr,arr+1048576);
    auto end = chrono::steady_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end-start);
    cout<<duration.count()<<endl;
    cout<<arr[0]<<"  "<<arr[1048575];



}