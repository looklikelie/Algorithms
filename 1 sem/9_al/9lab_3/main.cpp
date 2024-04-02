#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

void dfs(int first,const vector<vector<int> >& matrix,vector<short>& used,vector<int>& ans,bool& trouble){
    for (const int &i: matrix[first]) {
        if (used[i] == 1 and ans[i] == ans[first]) {
            trouble = true;
        }
        if (used[i] == 0) {
            used[i] = 1;
            ans[i] = - ans[first];
            dfs(i, matrix, used, ans, trouble);
        }
    }
    used[first] = 2;
}

int main() {
    int n,m, first, second;
    int parent = -1;
    bool trouble = false;
    ifstream cin("bipartite.in");
    ofstream cout("bipartite.out");
    cin >> n >> m;
    vector<vector<int> > matrix(n,(vector<int>()));
    vector<short> used(n,0);
    vector<int> ans(n,0);
    for (int i = 0; i < m; ++i) {
        cin >> first >> second;
        if (first == second){
            trouble = true;
        }
        matrix[first - 1].push_back(second - 1);
        matrix[second - 1].push_back(first - 1);
    }
    for (int j = 0; j < n; ++j) {
        used[j] = 1;
        ans[j] = 1;
        dfs(j,matrix,used,ans,trouble);
        while (j + 1 < n) {
            if (used[j + 1] == 0) {
                break;
            } else {
                j++;
            }
        }
    }
    if (!trouble){
        cout << "YES";
    }else{
        cout << "NO";
    }
    return 0;
}
