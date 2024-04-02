#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

int partition(int arr[], int l, int r)
{
    int v = arr[l + (rand() % (r - l))];
    int i = l;
    int j = r;
    while (i <= j){
        while (arr[i] < v){
            i++;
        }
        while (arr[j] > v){
            j--;
        }
        if (i >= j){
            break;
        }
        swap(arr[i++], arr[j--]);
    }
     return j;
}

void qsort(int arr[], int l, int r)

{
    if(l < r){
        int q;
        q = partition(arr, l, r);
        qsort(arr, l, q);
        qsort(arr,q+1,r);
    }
}

int main()
{
    int n;
    ifstream file;
    file.open("sort.in");
    cin >> n;
    int arr[n];
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }
    qsort(arr, 0, n-1);
    ofstream out("sort.out");
    for(int i = 0; i < n; i++){
        cout << arr[i] << ' ';
    }
    return 0;
}
