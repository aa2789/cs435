#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

unsigned long  compCount = 0;

void printArray(int* arr, int length){
    for(int i=0;i<length;i++){
        cout<<arr[i];
        if(i<length-1)cout<<", ";
    }
    cout<<endl;
}

void resetCompCount(){
    compCount=0;
}

bool smaller(int* arr, int i, int j){
    compCount+=1;
    if(arr[i]<arr[j])return true;
    return false;
}

void insertionSort(int * arr, int length){
    for(int i=1;i<length;i++){
        int j=i;
        while(j>0 && smaller(arr,j,j-1)){
            swap(arr[j],arr[j-1]);
            j--;
        }
    }
    }
    
void printTopBorder(const string& caseType, bool experimentBorder=false){
    if(experimentBorder==true){
            cout<<setw(50);
            cout<<"------------------------"<<caseType<<"------------------------"<<endl;
            return;
    }
    cout<<setw(50);
    cout<<"------------"<<caseType<<"------------"<<endl;
}

void runExperimentOne(int* arr){
    cout<<"Initial Array (n=32)"<<endl;
    printArray(arr,32);       
    insertionSort(arr,32);
    cout<<"Sorted Array"<<endl;
    printArray(arr,32); 
    cout<<"The number of comparisons is "<<compCount<<endl;    
    resetCompCount();   
}

void runExperimentOne(){
    int* arr = new int[32];
    //worst case data input
    for(int i=31;i>=0;i--){
        arr[i]= (31-i);
    }
    printTopBorder("Worst Case");
    runExperimentOne(arr);

    // best case data input
    for(int i=0;i<32;i++){
        arr[i]=i;
    }
    printTopBorder("Best Case");
    runExperimentOne(arr);

    //average case data input
    for(int i=0;i<32;i++){
        arr[i]= rand()%32;
    }
    printTopBorder("Average Case");
    runExperimentOne(arr);

    delete[] arr;
}

void runExperimentTwo(int* arr, int length){
    insertionSort(arr,length);
    cout<<"The number of comparisons for n = "<<length<<" is "<<compCount<<endl;
    resetCompCount();
}

void runExperimentTwo(){
    for(int length=100;length<=10000;length*=10){
        int* arr = new int[length];
        for(int i=0;i<length;i++){
            arr[i] = rand()%1000000;
        }
        runExperimentTwo(arr,length);
        delete[] arr;
    }
}



int main(){

    srand((unsigned)time(NULL));
    printTopBorder("EXPERIMENT ONE",true);
    runExperimentOne();
    printTopBorder("EXPERIMENT TWO",true);
    runExperimentTwo();
    return 0;


}