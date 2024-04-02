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
vector<int> cur(210,0);

void add_edge (int a, int b, int l,int c,vector<vector<int>>& residual_network,int n) {
    edge e1 = { a, b, c-l, 0 };
    edge e2 = { b, a, 0, 0 };
    edge e3 = {0,b,l,0};
    edge e4 = {b,0,0,0};
    edge e5 = {a,n-1,l,0};
    edge e6 = {n-1,a,0,0};
    residual_network[a].push_back ((int) edge_arr.size());
    edge_arr.push_back (e1);
    residual_network[b].push_back ((int) edge_arr.size());
    edge_arr.push_back (e2);
    residual_network[0].push_back((int)edge_arr.size());
    edge_arr.push_back(e3);
    residual_network[b].push_back ((int) edge_arr.size());
    edge_arr.push_back (e4);
    residual_network[a].push_back ((int) edge_arr.size());
    edge_arr.push_back (e5);
    residual_network[n-1].push_back((int)edge_arr.size());
    edge_arr.push_back(e6);
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

int main(){
    ifstream cin("circulation.in");
    ofstream cout("circulation.out");
    cin.tie(NULL);
    int n,m,s,e,l,c;
    cin >> n >> m;
    n = n + 2;
    vector<vector<int>> residual_network(n);
    for (int i = 0; i < m; ++i) {
        cin >> s >> e >> l >> c;
        add_edge(s,e,l,c,residual_network,n);
    }
    int maxflow = dinic(n,residual_network);
    bool circulation = true;
    for (auto& i:residual_network[0]){
        if (edge_arr[i].flow != edge_arr[i].cap){
            circulation = false;
        }
    }
    if (circulation){
        cout << "YES" << "\n";
        for (int i = 0; i < edge_arr.size();i += 6){
            cout << edge_arr[i].flow  + edge_arr[i+2].cap << "\n";
        }
    }else{
        cout << "NO";
    }
    cin.close();
    cout.close();
    return 0;
}
