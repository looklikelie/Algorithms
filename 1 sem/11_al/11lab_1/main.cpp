#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void dijkstra(vector<vector<int>>& matrix,int n,int s,int f,vector<unsigned long long>& distance,unsigned long long flag){
    distance[s] = 0;
    vector<bool> used(n,0);
    bool mark = true;
    while (mark){
        int new_vertex = -1;
        flag= 223372036854775999;
        for (int i = 0; i < n; ++i) {
            if (distance[i] < flag and used[i] == 0){
                new_vertex = i;
                flag = distance[i];
            }
        }
        if (new_vertex == -1){
            break;
        } else{
            used[new_vertex] = 1;
            for (int i = 0; i < n; ++i) {
                if (!used[i]) {
                    if (matrix[new_vertex][i] >= 0 and (distance[new_vertex] + matrix[new_vertex][i] < distance[i])) {
                        distance[i] = distance[new_vertex] + matrix[new_vertex][i];
                    }
                }
            }
        }
    }
}

int main() {
    ifstream cin("pathmgep.in");
    ofstream cout("pathmgep.out");
    int n,s,f;
    cin >> n >> s >> f;
    s--;
    f--;
    vector<vector<int>> matrix(n,vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> matrix[i][j];
        }
    }
    unsigned long long flag= 223372036854775999;
    vector<unsigned long long> distance(n,flag);
    dijkstra(matrix,n,s,f,distance,flag);
    if (distance[f] == flag){
        cout << -1;
    }else{
        cout << distance[f];
    }
    return 0;
}
