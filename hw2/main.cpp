#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <chrono>

using namespace std;

unsigned long compCount = 0;

bool compare(int*arr, int i, int j){
    compCount+=1;
    if(arr[i]<arr[j])return true;
    return false;

}
bool sorted(int* arr, int n ){
    for(int i=0;i<n-1;i++){
        if(arr[i]>arr[i+1])return false;
    }
    return true;
}

void merge(int*arr, int l, int mid, int r){
    int* leftArray = new int[mid-l+1];
    int* rightArray = new int[r-mid];
    for(int i=l;i<=mid;i++) leftArray[i-l]=arr[i];
    for(int i=mid+1;i<=r;i++)rightArray[i-(mid+1)]=arr[i];
    int lPointer=0;
    int rPointer =0;
    int mPointer =l;
    while(lPointer<(mid-l+1)&& rPointer<(r-mid)){
        if(leftArray[lPointer]<=rightArray[rPointer]){
            arr[mPointer++]=leftArray[lPointer++];
        }
        else{
            arr[mPointer++]=rightArray[rPointer++];
        }
    }
    while(lPointer<(mid-l+1)){
        arr[mPointer++]=leftArray[lPointer++];
    }
    while(rPointer<(r-mid)){
        arr[mPointer++]=rightArray[rPointer++];
    }
    delete[] leftArray;
    delete[] rightArray;

    
}


void mergeSort(int* arr, int l, int r){
    if(l==r)return;
    int mid = l+(r-l)/2;
    mergeSort(arr,l,mid);
    mergeSort(arr,mid+1,r);
    merge(arr,l,mid,r);  
}

void mergeSortDriver(int* arr, int n){
    auto start = chrono::steady_clock::now();
    mergeSort(arr,0,n-1);
    auto end = chrono::steady_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end-start);
    cout<<duration.count()<<endl;


}
void pushDown(int* arr, int n, int currNode){
    while(true){
        if(2*currNode+1>=n)break;
        int s;
        if(2*currNode+1==(n-1)||arr[2*currNode+1]>=arr[2*currNode+2]){
        s=2*currNode+1;
         }
         else{
            s=2*currNode+2;
         }
         if(arr[currNode]<arr[s]){
            swap(arr[currNode],arr[s]);
            currNode = s;
         }
         else{
            break;
         }

    }

}


void buildHeap(int* arr, int n){
    int start = (n/2)-1;
    for(int i=start;i>=0;i--){
        pushDown(arr,n,i);
    }

}
void heapSort(int* arr, int n){
    auto start = chrono::steady_clock::now();
    buildHeap(arr, n);
    swap(arr[0],arr[n-1]);
    for(int arrayLen=n-1;arrayLen>1;arrayLen--){
        pushDown(arr,arrayLen,0);
        swap(arr[0],arr[arrayLen-1]);
    }

    auto end = chrono::steady_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end-start);
    cout<<duration.count()<<endl;

}
void quickSort(int* arr, int n){
    auto start = chrono::steady_clock::now();
    auto end = chrono::steady_clock::now();
    auto duration = chrono::duration_cast<chrono::seconds>(end-start);
    cout<<duration.count()<<endl;    

}

void runExperimentOne(){
    int *mArr = new int[32];
    int* hArr = new int[32];
    int *qArr = new int[32];
    for(int i=0;i<32;i++){
        mArr[i]=i;
        hArr[i]=i;
        qArr[i]=i;
    }
    mergeSortDriver(mArr, 32);
    heapSort(hArr,32);
    quickSort(qArr,32);
    for(int i=31;i>=0;i--){
        mArr[i]=(31-i);
        hArr[i]=(31-i);
        qArr[i]=(31-i);
    }
    mergeSortDriver(mArr,32);
    heapSort(hArr,32);
    quickSort(qArr,32);
    for(int i=0;i<32;i++){
        int j= rand()%32;
        mArr[i]=j;
        hArr[i]=j;
        qArr[i]=j;
    }
    mergeSortDriver(mArr,32);
    heapSort(hArr,32);
    quickSort(qArr,32);
    delete[] mArr;
    delete[] hArr;
    delete[] qArr;


}
void printArray(int* arr, int n){
    for(int i=0;i<n;i++){
        cout<<arr[i]<<", ";
    }
    cout<<endl;

}
void heapTest(){
    int* arr =new int[33];
    for(int i=0;i<33;i++){
        int j=rand()%1000000;
        arr[i]=j;
    }
    printArray(arr,33);
    heapSort(arr,33);
    printArray(arr,33);
    if(sorted(arr,33)==1){
        cout<<"Sorted"<<endl;
    }
    else cout<<"Not Sorted"<<endl;

}

void mergeTest(){
    int* arr= new int[33];
    for(int i=0;i<33;i++){
        arr[i]=rand()%32;
    }
    printArray(arr,33);
    mergeSortDriver(arr,33);
    printArray(arr,33);
    if(sorted(arr,33)==1){
        cout<<"Sorted"<<endl;
    }
    else cout<<"Not Sorted"<<endl;

}


int main(int argc, char** argv){
    srand((unsigned)time(NULL));
    //Command Line Parameter Values
    //1 = mergesort 2=Heapsort 3=Quicksort
   // heapTest();
   mergeTest();





}

