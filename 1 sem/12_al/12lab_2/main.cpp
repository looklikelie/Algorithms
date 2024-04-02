#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int bfs_and_relax(int n, vector<vector<int>>& res_n){
    vector<int> parents(n,-1);
    vector<int> dynamic = {0};
    int start = 0;
    bool flag = false;
    while (start < dynamic.size()){
        for(int i = 0;i < n;i++) {
            if (res_n[dynamic[start]][i] != 0 and parents[i] == -1 and i != 0){
                parents[i] = dynamic[start];
                dynamic.push_back(i);
                if (i == n-1){
                    flag = true;
                }
            }
        }
        start++;
        if (flag){
            break;
        }
    }
    if (parents[n-1] == -1){
        return 0;
    } else{
        int min_v = INT_MAX;
        vector<int> way;
        int pointer = n-1;
        while (parents[pointer] != -1){
            way.push_back(pointer);
            pointer = parents[pointer];
        }
        way.push_back(0);
        reverse(way.begin(),way.end());
        for (auto it = way.begin();it != way.end() - 1;it++){
            min_v = min(min_v,res_n[*it][*(it+1)]);
        }
        for (auto it = way.begin();it != way.end() - 1;it++){
            res_n[*it][*(it+1)] -= min_v;
            res_n[*(it+1)][*it] += min_v;
        }
        return min_v;
    }

}

int main(){
    ifstream cin("matching.in");
    ofstream cout("matching.out");
    int n,m,k,s,e;
    cin >> n >> m >> k;
    vector<vector<int>> network(n+m+2,vector<int>(n + m + 2,0));
    for (int i = 1; i < n + 1; ++i) {
        network[0][i] = 1;
    }
    for (int i = n + 1;i < n + m + 1;++i){
        network[i][n + m + 1] = 1;
    }
    for (int j = 0; j < k; ++j) {
        cin >> s >> e;
        network[s][e+n] = 1;
    }
    int cnt = 0;
    while (true){
        int buffer = bfs_and_relax(n+m+2,network);
        if (buffer == 0){
            break;
        }else{
            cnt += buffer;
        }
    }
    cout << cnt;
    cin.close();
    cout.close();
    return 0;
}
