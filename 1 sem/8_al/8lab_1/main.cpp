#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream cin("input.txt");
    ofstream cout("output.txt");
    int n, m, first, second;
    cin >> n >> m;
    int matrix[n][n];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            matrix[i][j] = 0;
        }
    }
    for(int i = 0; i < m; i++){
        cin >> first >> second;
        matrix[first - 1][second - 1] = 1;
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << matrix[i][j] << ' ';
        }
        cout << endl;
    }
    return 0;
}
