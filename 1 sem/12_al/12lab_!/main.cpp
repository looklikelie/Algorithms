#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int bfs_and_relax(int n,int m,const vector<vector<int>>& main_n, vector<vector<int>>& res_n){
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
    ifstream cin("maxflow.in");
    ofstream cout("maxflow.out");
    int n,m,s,e,b;
    long long max_flow = 0;
    cin >> n >> m;
    vector<vector<int>> main_network(n,vector<int>(n,0));
    vector<vector<int>> residual_network(n,vector<int>(n,0));
    for (int i = 0; i < m; ++i) {
        cin >> s >> e >> b;
        s--;
        e--;
        main_network[s][e] = max(b,main_network[s][e]);
        residual_network[s][e] = max(b,residual_network[s][e]);
    }
    while (true){
       int buffer = bfs_and_relax(n,m,main_network,residual_network);
       if (buffer == 0){
           break;
       }else{
           max_flow += buffer;
       }
    }
    cout << max_flow;
    cin.close();
    cout.close();
    return 0;
}
