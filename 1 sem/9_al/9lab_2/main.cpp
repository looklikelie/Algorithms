#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

void dfs(int first,const vector<vector<int> >& matrix,vector<short>& arr,vector<int>& ans,bool& cycle,int& stop){
    if (!cycle) {
        for (const int &i: matrix[first]) {
            if (arr[i] == 1) {
                cycle = true;
                stop = i;
                break;
            }
            if (arr[i] == 0) {
                arr[i] = 1;
                dfs(i, matrix, arr, ans, cycle,stop);
                if (cycle){
                    break;
                }
            }
        }
        arr[first] = 2;
        if (cycle and stop != -322) {
            if (stop == first){
                stop = -322;
            }
            ans.push_back(first);
        }
    }
}

int main() {
    int n,m, first, second;
    int stop = -1;
    bool cycle = false;
    ifstream cin("cycle.in");
    ofstream cout("cycle.out");
    cin >> n >> m;
    vector<vector<int> > matrix(n,(vector<int>()));
    vector<short> arr(n,0);
    vector<int> ans(0);
    for (int i = 0; i < m; ++i) {
        cin >> first >> second;
        matrix[first - 1].push_back(second - 1);
    }
    for (int j = 0; j < n; ++j) {
        arr[j] = 1;
        dfs(j,matrix,arr,ans,cycle,stop);
        while (j + 1 < n) {
            if (arr[j + 1] == 0) {
                break;
            } else {
                j++;
            }
        }
    }
    if (cycle){
        reverse(ans.begin(),ans.end());
        cout << "YES" << "\n";
        for (const int& i:ans) {
            cout << i + 1 << " ";
        }
    }else{
        cout << "NO";
    }
    cin.close();
    cout.close();
    return 0;
}
