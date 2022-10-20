#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <chrono>

using namespace std;

unsigned long compCount = 0;

bool compare(const int& i, const int& j, const string& cmpOperator){
    compCount+=1;
    if(cmpOperator=="<="){
        if(i<=j)return true;
        else return false;
    }
    else if(cmpOperator=="<"){
        if(i<j)return true;
        else return false;
    }
    else if(cmpOperator==">="){
        if(i>=j)return true;
        else return false;
    }
    else if(cmpOperator==">"){
        if(i>j)return true;
        else return false;
    }
    else if(cmpOperator=="=="){
        if(i==j)return true;
        else return false;
    }
   
    return false;

}
void inline resetCompCount(){
    compCount=0;
}
bool sorted(int* arr, int n ){
    for(int i=0;i<n-1;i++){
        if(arr[i]>arr[i+1]){
            cout<<"THE ARRAY IS NOT SORTED"<<endl;
            return false;
            }
    }
    cout<<"THE ARRAY IS SORTED"<<endl;
    return true;
}

void printArray(int* arr, int n){
    for(int i=0;i<n;i++){
        cout<<arr[i]<<", ";
    }
    cout<<endl;

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
        if(compare(leftArray[lPointer],rightArray[rPointer],"<=")){
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
    cout<<"The total number of comparisons for merge sort was "<<compCount<<",and the total time taken was "<<duration.count()<<" microseconds"<<endl;


}
void pushDown(int* arr, int n, int currNode){
    while(true){
        if(2*currNode+1>=n)break;
        int s;
        if(2*currNode+1==(n-1)||compare(arr[2*currNode+1],arr[2*currNode+2],">=")){
        s=2*currNode+1;
         }
         else{
            s=2*currNode+2;
         }
         if(compare(arr[currNode],arr[s],"<")){
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
    cout<<"The total number of comparisons for heap sort was "<<compCount<<" ,and the total time taken was "<<duration.count()<<" microseconds"<<endl;

}
void quickSort(int* arr, int left, int right){
    if(left>=right)return;
   // int pivot = left+rand()%(right-left+1);
    int pivot = left+(right-left)/2;
    int v= arr[pivot];
    swap(arr[left], arr[pivot]);
    int l=left+1;
    int r=right;
    while(l<=r){
        while(l<=r&&compare(arr[l],v,"<="))l++;
        while(l<=r&&compare(arr[r],v,">"))r--;
        if(l<r){
            swap(arr[l],arr[r]);
            l++;
            r--;
        }   
    }
    swap(arr[r],arr[left]);
    quickSort(arr,left,r-1);
    quickSort(arr,r+1,right);
}

void quickSortDriver(int* arr, int n){
    auto start = chrono::steady_clock::now();
    quickSort(arr,0,n-1);
    auto end = chrono::steady_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end-start);
    cout<<"The total number of comparisons for quick sort was "<<compCount<<" ,and the total time taken was "<<duration.count()<<" microseconds"<<endl;   
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
    cout<<"EXPERIMENT ON SORTED ARRAY"<<endl;
    mergeSortDriver(mArr, 32);
    printArray(mArr,32);
    resetCompCount();
    heapSort(hArr,32);
    printArray(hArr,32);
    resetCompCount();
    quickSortDriver(qArr,32);
    printArray(qArr,32);
    resetCompCount();
    for(int i=31;i>=0;i--){
        mArr[i]=(31-i);
        hArr[i]=(31-i);
        qArr[i]=(31-i);
    }
    cout<<"EXPERIMENT ON REVERSELY SORTED ARRAY"<<endl;
    mergeSortDriver(mArr,32);
    printArray(mArr,32);
    resetCompCount();
    heapSort(hArr,32);
    printArray(hArr,32);
    resetCompCount();
    quickSortDriver(qArr,32);
    printArray(qArr,32);
    resetCompCount();
    for(int i=0;i<32;i++){
        int j= rand()%32;
        mArr[i]=j;
        hArr[i]=j;
        qArr[i]=j;
    }
    cout<<"EXPERIMENT ON RANDOMLY GENERATED ARRAY"<<endl;
    mergeSortDriver(mArr,32);
    printArray(mArr,32);
    resetCompCount();
    heapSort(hArr,32);
    printArray(hArr,32);
    resetCompCount();
    quickSortDriver(qArr,32);
    printArray(qArr,32);
    resetCompCount();
    delete[] mArr;
    delete[] hArr;
    delete[] qArr;


}



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

/*
        HOW TO RUN PROGRAM (just in case)
If you wish to perform experiment 1, simply generate the executable doing 'g++ main.cpp -o prog' and run './prog'
If you wish to perform experiment 2, you must use a command line argument corresponding to the algorithm you wish to run.
Command Line Parameter Values: 1 = mergesort 2=Heapsort 3=Quicksort
So if you want to test mergesort you would do './prog 1' 
Also, when running experiment 2, please make sure inputFile.txt is in the same directory as the executable, as the program reads from a file to populate the array to ensure 
the different sorting algorithms get the same arrays to sort.


*/

int main(int argc, char** argv){
    srand((unsigned)time(NULL));
    //Command Line Parameter Values
    //1 = mergesort 2=Heapsort 3=Quicksort
    if(argc>1){
        int paramValue = stoi(argv[1]);
        
        for(int i=1024;i<=1048576;i*=32){
            int * arr = new int[i];
            populateArray(arr,i);
            if(paramValue==1)mergeSortDriver(arr,i);
            if(paramValue==2)heapSort(arr,i);
            if(paramValue==3)quickSortDriver(arr,i);
            delete[] arr;
            resetCompCount();
        }
    }
    else{
        runExperimentOne();
    }
    

}

