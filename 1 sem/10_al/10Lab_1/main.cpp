#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    int m, n;
    ifstream cin("input.txt");
    ofstream cout("output.txt");
    cin >> n >> m;
    int arr[n];
    for(int i = 0; i < n; i++){
        arr[i] = 0;
    }
    int a, b;
    for(int i = 0; i < m; i++){
        cin >> a >> b;
        arr[a-1]++;
        arr[b-1]++;
    }
    for(int i = 0; i < n; i++){
        cout << arr[i] << ' ';
    }
    return 0;
}
