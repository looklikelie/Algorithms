#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

short dfs(int first,const vector<vector<int> >& matrix,vector<short>& used,short player){
    short buffer = player;
    for(const int& i: matrix[first]){
        if (used[i] == 0){
            used[i] = 2;
            if (player == 1) {
                buffer = min(dfs(i, matrix, used, -1), buffer);
            }else{
                buffer = max(dfs(i, matrix, used, 1), buffer);
            }
        }
        else {
            if (used[i] == 1 and player == 1) {
                buffer = -1;
            }
            if (used[i] == -1 and player == -1) {
                buffer = 1;
            }
        }
    }
    used[first] = buffer;
    return buffer;
}

int main() {
    int n,m,s, first, second;
    short player = 1;
    ifstream cin("game.in");
    ofstream cout("game.out");
    cin >> n >> m >> s;
    s--;
    vector<vector<int> > matrix(n,(vector<int>()));
    vector<short> used(n,0);
    for (int i = 0; i < m; ++i) {
        cin >> first >> second;
        matrix[first - 1].push_back(second - 1);
    }
    short ans =  dfs(s,matrix,used,player);
    if (ans == 1){
        cout << "Second player wins";
    }else{
        cout << "First player wins";
    }
    cin.close();
    cout.close();
    return 0;
}
