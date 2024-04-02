#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

using namespace std;


int main() {
    ifstream cin("pathbgep.in");
    ofstream cout("pathbgep.out");
    int n,m;
    int start,end,len,pointer,point;
    long long ans = 0;
    cin >> n >> m;
    vector<pair<int,int>> distance(n);
    vector<int> distance2(n,777777777);
    vector<bool> used(n,0);
    for (int l = 0; l < n; ++l) {
        distance[l] = {777777777,l};
    }
    vector<vector<pair<int,int>>> matrix(n, vector<pair<int,int>>());
    for (int i = 0; i < m; ++i) {
        cin >> start >> end >> len;
        if (start == 1){
            distance[end - 1].first = min(distance[end - 1].first,len);
            distance2[end - 1] = min(distance2[end - 1],len);
        }
        if (end == 1){
            distance[start - 1].first = min(distance[start - 1].first,len);
            distance2[start - 1] = min(distance2[start - 1],len);
        }
        if (start != end){
            matrix[start - 1].push_back({end - 1,len});
            matrix[end - 1].push_back({start - 1,len});
        }
    }
    distance[0].first = 888888888;
    distance2[0] = 0;
    used[0] = 1;
    swap(distance[0],distance[n-1]);
    int counter;
    int buffer2;
    for (int j = n/2 - 1; j > -1; --j) {
        buffer2 = j;
        counter = 0;
        while (2*buffer2 + 1 < n && counter == 0) {
            if (2 * buffer2 + 2 >= n) {
                if (distance[2 * buffer2 + 1] < distance[buffer2]) {
                    swap(distance[buffer2], distance[2 * buffer2 + 1]);
                    buffer2 = buffer2*2 + 1;
                }else{
                    counter = 1;
                }
            }else {
                if (distance[2 * buffer2 + 1] < distance[2 * buffer2 + 2]) {
                    if (distance[2 * buffer2 + 1] < distance[buffer2]) {
                        swap(distance[buffer2], distance[2 * buffer2 + 1]);
                        buffer2 = buffer2*2 + 1;
                    }else{
                        counter = 1;
                    }
                }else {
                    if (distance[2 * buffer2 + 2] < distance[buffer2]) {
                        swap(distance[buffer2], distance[2 * buffer2 + 2]);
                        buffer2 = buffer2*2 + 2;
                    } else{
                        counter = 1;
                    }
                }
            }
        }
    }
    counter = n - 1;
    while (counter > 0){
        pointer = distance[0].first;
        point = distance[0].second;
        swap(distance[0],distance[counter - 1]);
        counter--;
        int cnt = 0;
        while (cnt*2 + 1 < counter){
            if (cnt*2 + 2 < counter){
                if (distance[cnt*2 + 1] < distance[cnt*2 + 2]){
                    if (distance[cnt*2 + 1] < distance[cnt]){
                        swap(distance[cnt*2 + 1],distance[cnt]);
                        cnt = cnt*2 + 1;
                    }else{
                        break;
                    }
                } else{
                    if (distance[cnt*2 + 2] < distance[cnt]){
                        swap(distance[cnt*2 + 2],distance[cnt]);
                        cnt = cnt*2 + 2;
                    }else{
                        break;
                    }
                }
            } else{
                if (distance[cnt*2 + 1] < distance[cnt]){
                    swap(distance[cnt*2 + 1],distance[cnt]);
                    cnt = cnt*2 + 1;
                }else{
                    break;
                }
            }
        }
        if (pointer == distance2[point] and !used[point]){
            for (const pair<int,int>& i: matrix[point]){
                if (i.second + pointer < distance2[i.first] and distance2[i.first] != 999999){
                    distance2[i.first] = i.second + pointer;
                    if (counter < distance.size()){
                        distance[counter] = {i.second + pointer,i.first};
                    } else{
                        distance.emplace_back(i.second + pointer,i.first);
                    }
                    counter++;
                    int buf = counter - 1;
                    int buf2 = counter - 1;
                    if (buf % 2 == 0){
                        buf--;
                    }
                    while (buf > 0){
                        buf = buf / 2;
                        if (distance[buf2] < distance[buf]){
                            swap(distance[buf2],distance[buf]);
                            buf2 = buf;
                        }else{
                            break;
                        }
                        if (buf % 2 == 0){
                            buf--;
                        }
                    }
                }
            }
        }
    }
    for (int k = 0; k < n; ++k) {
        cout << distance2[k] << " ";
    }
    return 0;
}
