#include <fstream>
#include <vector>

using namespace std;

int main(){
    ifstream cin("pathsg.in");
    ofstream cout("pathsg.out");
    int n,m,s,f,len;
    cin >> n >> m;
    vector<vector<int>> matrix(n,vector<int>(n,10000000));
    for (int j = 0; j < n; ++j) {
        matrix[j][j] = 0;
    }
    for (int i = 0; i < m; ++i) {
        cin >> s >> f >> len;
        matrix[s-1][f-1] = len;
    }
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
            }
        }
    }
    for (int l = 0; l < n; ++l) {
        for (int i = 0; i < n; ++i) {
            cout << matrix[l][i] << " ";
        }
        cout << endl;
    }
    return 0;
}
