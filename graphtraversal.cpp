#include <bits/stdc++.h>
using namespace std;

/* ========================
   🔹 INTERPOLATION SEARCH
   ======================== */
// Works well if array elements are uniformly distributed
int interpolationSearch(vector<int>& arr, int target) {
    int l=0, r=arr.size()-1;
    while(l<=r && target>=arr[l] && target<=arr[r]) {
        if(l==r) return (arr[l]==target)? l : -1;
        // estimate position
        int pos = l + (double)(r-l) * (target-arr[l]) / (arr[r]-arr[l]);
        if(arr[pos]==target) return pos;
        if(arr[pos]<target) l=pos+1;
        else r=pos-1;
    }
    return -1;
}

/* ========================
   🔹 FIBONACCI SEARCH
   ======================== */
int fibonacciSearch(vector<int>& arr, int target) {
    int n = arr.size();
    // Initialize Fibonacci numbers
    int fib2=0, fib1=1, fibM=fib2+fib1; 
    while(fibM<n){ fib2=fib1; fib1=fibM; fibM=fib2+fib1; }
    int offset=-1;

    while(fibM>1){
        int i=min(offset+fib2,n-1);
        if(arr[i]<target){ fibM=fib1; fib1=fib2; fib2=fibM-fib1; offset=i; }
        else if(arr[i]>target){ fibM=fib2; fib1=fib1-fib2; fib2=fibM-fib1; }
        else return i;
    }
    if(fib1 && offset+1<n && arr[offset+1]==target) return offset+1;
    return -1;
}

int main(){
    vector<int> arr={1,3,5,7,9,11,13,15,17,19};

    cout<<"Interpolation Search(13): "<<interpolationSearch(arr,13)<<"\n";
    cout<<"Fibonacci Search(7): "<<fibonacciSearch(arr,7)<<"\n";
    cout<<"Fibonacci Search(20): "<<fibonacciSearch(arr,20)<<"\n";

    return 0;
}
