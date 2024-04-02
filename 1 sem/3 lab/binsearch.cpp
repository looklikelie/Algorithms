#include <iostream>
#include <fstream>

using namespace std;

int binsearchlow(int arr[], int element, int first, int last){
    int mid = (first + last) / 2;
    while(first <= last){
        mid = (first + last) / 2;
        if(arr[mid] < element){
            first = mid + 1;
        }else{
            last = mid - 1;
        }
    }
    if(arr[first] == element){
        return first + 1;
    }else{
        return -1;
    }
    cout<<'p';
}

int binsearchhigh(int arr[], int element, int first, int last){
    int mid = (first + last) / 2;
    while(first <= last){
        mid = (first + last) / 2;
        if(arr[mid] > element){
            last = mid - 1;
        }else{
            first = mid + 1;
        }
    }
    if(arr[first-1] == element){
        return first;
    }else{
        return -1;
    }
}

int main()
{
    //ifstream cin("binsearch.in");
    int n, m, element;
    cin >> n;
    int arr[n];
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }
    cin >> m;
    //ofstream cout("binsearch.out");
    for(int i = 0; i < m; i++){
        cin >> element;
        cout << binsearchlow(arr, element, 0, n-1) << ' ' << binsearchhigh(arr, element, 0, n-1) << '\n';
    }

    return 0;
}
