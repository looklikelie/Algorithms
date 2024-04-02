#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream cin("input.txt");
    ofstream cout("output.txt");
    int n;
    cin >> n;
    int arr[n][n];
    bool flag = true;
    for (int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> arr[i][j];
        }
    }
    for (int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(arr[i][j] != arr[j][i] && i != j){
                flag = false;
            }
            else if(arr[i][j] == 1 && i == j){
                flag = false;
            }
        }
    }
    if(flag == false){
        cout << "NO";
    }else{
        cout << "YES";
    }

    return 0;
}



    for (int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << arr[i][j] << ' ';
        }
        cout << '\n';
    }
