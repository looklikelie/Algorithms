#include <iostream>
#include <fstream>

using namespace std;

void mergee(long long a[], int left, int mid, int right, long long* p){
    int it1 = 0;
    int it2 = 0;
    int result[right - left];
    while(left + it1 < mid && mid + it2 < right){
        if (a[left + it1] <= a[mid + it2]){
            result[it1 + it2] = a[left + it1];
            it1++;
        }else{
            result[it1 + it2] = a[mid + it2];
            it2++;
            *p += mid - (left + it1);
        }
    }
    while(left + it1 < mid){
        result[it1 + it2] = a[left + it1];
        it1++;
    }
    while(mid + it2 < right){
        result[it1 + it2] = a[mid + it2];
        it2++;
    }
    for(int i = 0; i < it1 + it2; i++){
        a[left + i] = result[i];
    }
}

void mergesort(long long a[], int left, int right, long long* p){
    if(left + 1 >= right){
        return;
    }
    int mid = (left + right) / 2;
    mergesort(a, left, mid, p);
    mergesort(a, mid, right, p);
    mergee(a, left, mid, right, p);
}
int main()
{
    ifstream ifile("inversions.in");
    int n;
    long long kol_vo = 0;
    long long* p =  &kol_vo;
    ifile >> n;
    long long arr[n];
    for(int i = 0; i < n; i++){
        ifile >> arr[i];
    }
    mergesort(arr, 0, n, p);
    ofstream ofile("inversions.out");
    ofile << kol_vo << endl;
    return 0;
}
