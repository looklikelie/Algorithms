#include <iostream>
#include <fstream>
#include <vector>

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
    ifstream cin("topsort.in");
    ofstream cout("topsort.out");
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
    if (!cycle){
        for (int i = n-1; i >= 0; --i) {
            cout << ans[i] + 1 << " ";
        }
    }else{
        cout << "-1";
    }

    return 0;
}
