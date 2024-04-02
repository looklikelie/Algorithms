#include <iostream>
#include <vector>

using namespace std;

void bfs(vector<vector<int> > arr, vector<int> first, int n, int m, int num){
    vector<int> arnold;
    for(int i = 0; i < arr[1].size(), i++){

    }
}

int main()
{
    int m, n, num;
    cin >> n >> m;
    int answer[n];
    vector<int> first (n);
    vector<int> sec (n);
    vector<vector<int> > arr (n);
    for( int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        a--; b--;
        arr[a].push_back(b);
        arr[b].push_back(a);
    }
    for(int i =  0; i < n; i++){
        first[i] = i;
    }
    while(!first.empty){
        sec = bfs(arr, first, n, m, num);
        for(int i = 0; i < sec.size(); i++){
            answer[sec[i]] = num;
        }
        num++;
    }
    cout << num << '\n';
    for(int i = 0; i < n; i++){
        cout << answer[i] << ' ';
    }
    return 0;
}
