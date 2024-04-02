#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

void dfs(int first,const vector<vector<int> >& matrix,vector<short>& used,vector<int>& ans,bool& cycle){
    for(const int& i: matrix[first]){
        if (used[i] == 1){
            cycle = true;
        }
        if (used[i] == 0){
            used[i] = 1;
            dfs(i,matrix,used,ans,cycle);
        }
    }
    used[first] = 2;
    ans.push_back(first);
}

int main() {
    int n,m, first, second;
    bool cycle = false;
    ifstream cin("hamiltonian.in");
    ofstream cout("hamiltonian.out");
    cin >> n >> m;
    vector<vector<int> > matrix(n,(vector<int>()));
    vector<short> used(n,0);
    vector<int> ans(0);
    for (int i = 0; i < m; ++i) {
        cin >> first >> second;
        matrix[first - 1].push_back(second - 1);
    }
    for (int j = 0; j < n; ++j) {
        used[j] = 1;
        dfs(j,matrix,used,ans,cycle);
        while (j + 1 < n) {
            if (used[j + 1] == 0) {
                break;
            } else {
                j++;
            }
        }
    }
    bool trouble = true;
    bool error = false;
    for (int i = n - 1; i > 0; --i) {
        trouble = true;
        for (const int& j:matrix[ans[i]]){
            if (j == ans[i - 1]){
                trouble = false;
            }
        }
        if (trouble){
            error = true;
            break;
        }
    }
    if (error){
        cout << "NO";
    } else{
        cout << "YES";
    }
    cin.close();
    cout.close();
    return 0;
}
