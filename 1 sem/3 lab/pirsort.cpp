#include <iostream>
#include <fstream>

using namespace std;

void shift_up(long long arr[], int i){
    if((i % 2 == 0) && (arr[i] > arr[(i / 2) - 1]) && (i > 0)){
        swap(arr[i], arr[(i / 2) - 1]);
        i = (i / 2) - 1;
        shift_up(arr, i);
    }else if((i % 2 == 1) && (arr[i] > arr[i / 2]) && (i > 0)){
        swap(arr[i], arr[i / 2]);
        i = i / 2;
        shift_up(arr, i);
    }
    return;
}

void shift_down(long long arr[], int n, int i){
    if((2 * i + 2 <= n) && (arr[2 * i + 1] < arr[2 * i + 2]) && (arr[i] < arr[2 * i + 2])){
        swap(arr[i], arr[2 * i + 2]);
        i = 2 * i + 2;
        shift_down(arr, n , i);
    }else if((2 * i + 2 <= n) && (arr[2 * i + 1] >= arr[2 * i + 2]) && (arr[i] < arr[2 * i + 1])){
        swap(arr[i], arr[2 * i + 1]);
        i = i * 2 + 1;
        shift_down(arr, n, i);
    }else if((2 * i + 1 <= n) && (arr[i] < arr[2 * i + 1])){
        swap(arr[i], arr[2 * i + 1]);
        i = i * 2 + 1;
        shift_down(arr, n, i);
    }
    return;
}

void sortpir(long long arr[], int size){
    while(size > 0){
        shift_down(arr, size, 0);
        swap(arr[0], arr[size]);
        size--;
    }
    return;
}

int main()
{
    ifstream cin("sort.in");
    ofstream cout("sort.out");
    int n;
    cin >> n;
    long long arr[n];
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }
    for(int i = 0; i < n; i++){
        shift_up(arr, i);
    }
    sortpir(arr, n - 1);
    for(int i = 0; i < n; i++){
        cout << arr[i] << ' ';
    }
    return 0;
}
