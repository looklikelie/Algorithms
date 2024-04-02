#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

struct edge {
    int a, b, cap, flow;
};

vector<edge> edge_arr{};
vector<int> cur(500,0);

void add_edge (int a, int b, int cap,vector<vector<int>>& residual_network) {
    edge e1 = { a, b, cap, 0 };
    edge e2 = { b, a, 0, 0 };
    residual_network[a].push_back ((int) edge_arr.size());
    edge_arr.push_back (e1);
    residual_network[b].push_back ((int) edge_arr.size());
    edge_arr.push_back (e2);
}

bool bfs(int n,vector<vector<int>>& residual_network, vector<int>& d){
    d.assign(n,INT_MAX);
    d[0] = 0;
    queue<int> que;
    que.push(0);
    while (!que.empty()){
        int u = que.front();
        que.pop();
        for (const int& i:residual_network[u]){
            if (edge_arr[i].cap - edge_arr[i].flow > 0 and d[edge_arr[i].b] == INT_MAX){
                d[edge_arr[i].b] = d[u] + 1;
                que.push(edge_arr[i].b);
            }
        }
    }
    return d[n-1] != INT_MAX;

}

int dfs(int vertex,int flow,int n,vector<vector<int>>& residual_network,vector<int>& d){
    if (vertex == n - 1 or flow == 0){
        return flow;
    }
    for (; cur[vertex] < residual_network[vertex].size(); cur[vertex]++){
        int i = residual_network[vertex][cur[vertex]];
        if (d[edge_arr[i].b] != d[vertex] + 1)continue;
        int pushed = dfs(edge_arr[i].b,min(flow,edge_arr[i].cap - edge_arr[i].flow),n,residual_network,d);
        if (pushed){
            edge_arr[i].flow += pushed;
            if (edge_arr[i].cap == 0){
                edge_arr[i-1].flow -= pushed;
            }else{
                edge_arr[i+1].flow -= pushed;
            }
            return pushed;
        }
    }
    return 0;

}

int dinic(int n,vector<vector<int>>& residual_network){
    vector<int> dist(n);
    int flow = 0;
    for (;;){
        if (!bfs(n,residual_network,dist)) break;
        while (int buffer = dfs(0,INT_MAX,n,residual_network,dist)){
            flow += buffer;
        }
        cur.assign(n,0);
    }
    return flow;
}

int dfs_and_way(int vertex,int flow,int n,vector<vector<int>>& ans_arr,vector<vector<int>>& residual_network){
    if (vertex == n - 1){
        ans_arr.emplace_back();
        return flow;
    }
    for (auto& i:residual_network[vertex]){
        if (edge_arr[i].flow > 0){
            int flow2 = dfs_and_way(edge_arr[i].b,min(flow,edge_arr[i].flow),n,ans_arr,residual_network);
            if (flow2){
                ans_arr.back().push_back(i/2 + 1);
                if (vertex == 0){
                    ans_arr.back().push_back(ans_arr.back().size());
                    ans_arr.back().push_back(flow2);
                    reverse(ans_arr.back().begin(),ans_arr.back().end());
                }
                edge_arr[i].flow -= flow2;
                return flow2;
            }
        }
    }
    return 0;
}


int main(){
    ifstream cin("decomposition.in");
    ofstream cout("decomposition.out");
    cin.tie(NULL);
    int n,m,s,e,b;
    cin >> n >> m;
    vector<vector<int>> residual_network(n);
    for (int i = 0; i < m; ++i) {
        cin >> s >> e >> b;
        s--;
        e--;
        add_edge(s,e,b,residual_network);
    }
    int maxflow = dinic(n,residual_network);
    vector<vector<int>> ans_arr(0);
    while (dfs_and_way(0,INT_MAX,n,ans_arr,residual_network)){
        continue;
    }

    cout << ans_arr.size() << "\n";
    for (auto& i:ans_arr){
        for (auto& j: i){
            cout << j << " ";
        }
        cout << "\n";
    }
    cin.close();
    cout.close();
    return 0;
}
