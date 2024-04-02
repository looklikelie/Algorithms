#include <iostream>
#include <fstream>

using namespace std;

int check(int arr[], int size){
    for(int i = 0; (2 * i) + 1 <= size; i++){
        if(arr[i] >= arr[(2 * i) + 2]){
            return 0;
        }
        if(arr[i] >= arr[(2 * i) + 1]){
            return 0;
        }
    }
    return 1;
}

int main()
{
    int size;
    ifstream cin("isheap.in");
    cin >> size;
    int arr[size];
    for(int i = 0; i < size; i++){
        cin >> arr[i];
    }
    ofstream cout("isheap.out");
    if(check(arr, size - 1)){
        cout << "YES";
    }else{
        cout << "NO";
    }
    return 0;
}
