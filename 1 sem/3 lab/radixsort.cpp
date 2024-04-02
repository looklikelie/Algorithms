#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void radixsort(string arr[], int n, int m, int k){
    char d;
    int elements = 256, tmp;
    int C[elements];
    string B[n];
    int key = 1;
        for(int i = m-1; i > -1; i--){
            if(key > k){
                return;
            }
            key++;
            for(int j = 0; j < elements; j++){
                C[j] = 0;
            }
            for(int j = 0; j < n; j++){
                d = arr[j][i];
                C[d]++;
            }
            int count = 0;
            for(int j = 0; j < elements; j++){
                tmp = C[j];
                C[j] = count;
                count += tmp;
            }
            for(int j = 0; j < n; j++){
                d = arr[j][i];
                B[C[d]] = arr[j];
                C[d]++;
            }
            for(int j = 0; j < n; j++){
                arr[j] = B[j];
            }
        }
    return;
}

int main()
{
    //ifstream cin("radixsort.in");
    //ofstream cout("radixsort.out");
    int n, m, k;
    cin >> n >> m >> k;
    string arr[n];
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }
    radixsort(arr, n, m, k);
    for(int i = 0; i < n; i++){
        cout << arr[i] << '\n';
    }
    cout<<'\n';
    return 0;
}
