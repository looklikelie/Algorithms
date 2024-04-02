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

int qsort(int arr[], int r, int k)

{
    int l = 0;
    while (true) {
        int mid = partition(arr, l, r);
        if (mid == k) {
            return arr[mid];
        }else if(k < mid) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
}

int main()
{
    int n, k, A, B, C;
    //fstream in("kth.in");
    cin >> n >> k >> A >> B >> C;
    int arr[n];
    for(int i = 0; i < n; i++){
        if(i < 2){
            cin >> arr[i];
        }
        else{
            arr[i] = A * arr[i - 2] + B * arr[i - 1] + C;
        }
    }
    //ofstream out("kth.out");
    cout << qsort(arr, n - 1, k - 1);
    return 0;
}
