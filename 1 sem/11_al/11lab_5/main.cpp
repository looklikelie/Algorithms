#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

int main(){
    ifstream cin("negcycle.in");
    ofstream cout("negcycle.out");
    int n;
    cin >> n;
    vector<vector<int>> matrix(n,vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> matrix[i][j];
        }
    }
    vector<int> dist(n,100000000);
    vector<int> p(n,-1);
    int flag;
    for (int k = 0; k < n; ++k) {
        flag = -1;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n ; ++j) {
                if (dist[j] > dist[i] + matrix[i][j]){
                    dist[j] = max(-1000000000,dist[i] + matrix[i][j]);
                    p[j] = i;
                    flag = j;
                }
            }
        }
    }
    if (flag == -1){
        cout << "NO";
    }else{
        cout << "YES" << endl;
        int y = flag;
        for (int i = 0; i < n; ++i) {
            y = p[y];
        }
        vector<int> path;
        for (int cur=y; ; cur=p[cur]) {
            path.push_back (cur);
            if (cur == y && path.size() > 1)  break;
        }
        reverse (path.begin(), path.end());
        cout << path.size() << endl;
        for (const int& i:path) {
            cout << i + 1 << " ";
        }
    }
    return 0;
}
