#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

void bfs(vector<vector<pair<int,long long>>>& matrix,vector<long long>& d, int start,long long flag){
    vector<int> dynamic(1,start);
    vector<bool> used(matrix.size(),0);
    used[start] = 1;
    int left = 0;
    while (left < dynamic.size()){
        for (const pair<int,long long>& i: matrix[dynamic[left]]) {
            if (!used[i.first]){
                dynamic.push_back(i.first);
                d[i.first] = flag-1;
                used[i.first] = 1;
            }
        }
        left++;
    }
}

void bfs2(vector<vector<pair<int,long long>>>& matrix,vector<long long>& d, int start,long long flag){
    d[start] = -flag;
    vector<int> dynamic(1,start);
    vector<bool> used(matrix.size(),0);
    used[start] = 1;
    int left = 0;
    while (left < dynamic.size()){
        for (const pair<int,long long>& i: matrix[dynamic[left]]) {
            if (!used[i.first]){
                dynamic.push_back(i.first);
                d[i.first] = -flag;
                used[i.first] = 1;
            }
        }
        left++;
    }
}



int main(){
    ifstream cin("path.in");
    ofstream cout("path.out");
    int n,m,s,beg,end;
    long long len;
    cin >> n >> m >> s;
    s--;
    vector<vector<pair<int,long long>>> matrix(n);
    for (int i = 0; i < m; ++i) {
        cin >> beg >> end >> len;
        matrix[beg - 1].push_back({end-1,len});
    }
    long long flag = 3110000000000000000;
    vector<long long> d(n,flag);
    d[s] = 0;
    vector<int> p (n, -1);
    bfs(matrix,d,s,flag);
    int x = -1;
    for (int k=0; k<n; ++k) {
        x = -1;
        for (int j = 0; j < n; ++j) {
            if (d[j] != flag) {
                for (const pair<int, long long> &i:matrix[j]) {
                    if (d[i.first] != flag) {
                        if (d[i.first] > d[j] + i.second) {
                            d[i.first] = max(-flag, d[j] + i.second);
                            p[i.first] = j;
                            x = i.first;
                        }
                    }
                }
            }
        }
    }
    if (x != -1) {
        int y = x;
        for (int i = 0; i < n; ++i) {
            y = p[y];
        }
        bfs2(matrix,d,y,flag);
//        x = -1;
//        for (int j = 0; j < n; ++j) {
//            if (d[j] != -flag) {
//                for (const pair<int, long long> &i:matrix[j]) {
//                    if (d[i.first] != flag or d[i.first] != -flag) {
//                        if (d[i.first] > d[j] + i.second) {
//                            d[i.first] = max(-flag, d[j] + i.second);
//                            p[i.first] = j;
//                            x = i.first;
//                        }
//                    }
//                }
//            }
//        }
    }
    for (int k = 0; k < n; ++k) {
        if (d[k] == flag){
            cout << "*" << "\n";
        } else{
            if (d[k] == -flag){
                cout << "-" << "\n";
            }else{
                cout << d[k] << "\n";
            }
        }
    }
    cin.close();
    cout.close();
    return 0;
}
