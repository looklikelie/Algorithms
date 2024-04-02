#include <iostream>
#include <fstream>

using namespace std;

void anti_qs(int a[], int n){
    for(int i = 0; i < n; i++){
        swap(a[i], a[i/2]);
    }
}

int main()
{
    //ifstream ifile("antiqs.in");
    int n;
    cin >> n;
    int arr[n];
    for(int i = 0; i < n; i++){
        arr[i] = i+1;
    }
    anti_qs(arr, n);
    ofstream ofile("antiqs.out");
    for(int i = 0; i < n; i++){
        cout << arr[i] << ' ';
    }
    return 0;
}
