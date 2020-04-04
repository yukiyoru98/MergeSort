#include <iostream>
#include <fstream>
#include <vector>
#include <limits>

using namespace std;

void Merge(vector<int> &vec, int start, int mid, int end){
    
    //create vector for in-place
    vector<int> v1; //first half
    vector<int> v2; //second half
    for(int i=start; i<=mid; i++){
        v1.push_back(vec[i]);
    }
    for(int j=mid+1; j<=end; j++){
        v2.push_back(vec[j]);
    }

    //add infinity to the end of v1, v2(get rid of range checking)
    v1.push_back(numeric_limits<int>::max());
    v2.push_back(numeric_limits<int>::max());
    
    //compare elements
    int i = 0; //index for iterating v1
    int j = 0; //index for iterating v2
    for(int k = start; k <= end; k++){
        if(v1[i] < v2[j]){
            vec[k] = v1[i];
            i++;
        }
        else{
            vec[k] = v2[j];
            j++;
        }
    }
    
}

void MergeSort(vector<int> &vec, int start, int end){
    if(start < end){ //more than one elements in vec
        //divide
        int mid = (end + start) / 2;
        MergeSort(vec, start, mid);
        MergeSort(vec, mid + 1, end);
        //conquer
        Merge(vec, start, mid, end);
    }
}

int main(){
    vector<int> vec;
    const string inputFile = "input.txt";
    const string outputFile = "output.txt";

    //=====Read Input Sequence=====
    ifstream ReadFile(inputFile, ios::in);//declare input file
    //check if file exists
    if(!ReadFile.is_open()){
        cerr << "Input File not found.";
        exit(1);
    }
    
    int n = 0; //save how many numbers to sort
    ReadFile >> n; //read first line(numbers to sort)
    for(int i=0; i<n; i++){ //read the numbers and save them into vec
        int x;
        ReadFile >> x;
        vec.push_back(x);
    }
    
    //=====Do Merge Sort=====
    MergeSort(vec, 0, n-1);
    
    //=====Output Sorted Sequence=====
    ofstream WriteFile(outputFile, ios::out | ios::trunc);//declare output file
    //check if file exists
    if(!WriteFile.is_open()){
        cerr << "Output File not found.";
        exit(1);
    }
    
    for(int i=0; i<n; i++){ //read the sorted numbers in vector and write into file
        WriteFile << vec[i] << '\n';
    }
    
    return 0;
}
