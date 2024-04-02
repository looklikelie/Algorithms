#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream cin("components.in");
    ofstream cout("components.out");
    int n, m, a, b, sum = 1 ;
    cin >> n >> m;
    int arr[n];
    for(int i = 0; i < n; i++){
        arr[i] = 0;
    }
    for(int i = 0; i < m; i++){
        cin >> a >> b;
        a--; b--;
        if(arr[a] == 0 && arr[b] == 0){
            arr[a] = sum;
            arr[b] = sum;
            sum++;
        }
        else if(arr[a] != arr[b]){
            if(arr[a] == 0){
                arr[a] = arr[b];
            }
            else if(arr[b] == 0){
                arr[b] = arr[a];
            }
            else {
                int fir = arr[a], sec = arr[b], num = min(arr[a], arr[b]);
                for(int j = 0; j < n; j++){
                    if(arr[j] == fir || arr[j] == sec){
                        arr[j] = num;
                    }
                }
                sum--;
            }
        }
    }
    for(int i = 0; i < n; i++){
        if(arr[i] == 0){
            arr[i] = sum;
            sum++;
        }
    }
    sum--;
    cout << sum <<'\n';
    for(int i = 0; i < n; i++){
        cout << arr[i] << ' ';
    }
    return 0;
}
