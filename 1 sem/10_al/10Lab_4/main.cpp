#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

using namespace std;


int main() {
    ifstream cin("spantree3.in");
    ofstream cout("spantree3.out");
    int n,m;
    int start,end,len,index,dot;
    long long alldist = 0;
    cin >> n >> m;
    vector < pair<int,int> > dist (n);
    vector < int > dist2 (n,1000000);
    for (int l = 0; l < n; l++) {
        dist[l] = {1000000,l};
    }
    vector < vector < pair<int,int> > > matrix(n, vector<pair<int,int> >());
    for (int i = 0; i < m; ++i) {
        cin >> start >> end >> len;
        if (start == 1){
            dist[end - 1].first = min(dist[end - 1].first,len);
            dist2[end - 1] = min(dist2[end - 1],len);
        }
        if (end == 1){
            dist[start - 1].first = min(dist[start - 1].first,len);
            dist2[start - 1] = min(dist2[start - 1],len);
        }
        if (start != end){
            matrix[start - 1].push_back({end - 1,len});
            matrix[end - 1].push_back({start - 1,len});
        }
    }
    dist[0].first = 999999;
    dist2[0] = 999999;
    swap(dist[0],dist[n-1]);
    int counter;
    int buf2;
    for (int j = n/2 - 1; j > -1; --j) {
        buf2 = j;
        counter = 0;
        while (2*buf2 + 1 < n && counter == 0) {
            if (2 * buf2 + 2 >= n) {
                if (dist[2 * buf2 + 1] < dist[buf2]) {
                    swap(dist[buf2], dist[2 * buf2 + 1]);
                    buf2 = buf2*2 + 1;
                }else{
                    counter = 1;
                }
            }else {
                if (dist[2 * buf2 + 1] < dist[2 * buf2 + 2]) {
                    if (dist[2 * buf2 + 1] < dist[buf2]) {
                        swap(dist[buf2], dist[2 * buf2 + 1]);
                        buf2 = buf2*2 + 1;
                    }else{
                        counter = 1;
                    }
                }else {
                    if (dist[2 * buf2 + 2] < dist[buf2]) {
                        swap(dist[buf2], dist[2 * buf2 + 2]);
                        buf2 = buf2*2 + 2;
                    } else{
                        counter = 1;
                    }
                }
            }
        }
    }
    counter = n - 1;
    while (counter > 0){
        index = dist[0].first;
        dot = dist[0].second;
        swap(dist[0],dist[counter - 1]);
        counter--;
        int cnt = 0;
        while (cnt*2 + 1 < counter){
            if (cnt*2 + 2 < counter){
                if (dist[cnt*2 + 1] < dist[cnt*2 + 2]){
                    if (dist[cnt*2 + 1] < dist[cnt]){
                        swap(dist[cnt*2 + 1],dist[cnt]);
                        cnt = cnt*2 + 1;
                    }else{
                        break;
                    }
                } else{
                    if (dist[cnt*2 + 2] < dist[cnt]){
                        swap(dist[cnt*2 + 2],dist[cnt]);
                        cnt = cnt*2 + 2;
                    }else{
                        break;
                    }
                }
            } else{
                if (dist[cnt*2 + 1] < dist[cnt]){
                    swap(dist[cnt*2 + 1],dist[cnt]);
                    cnt = cnt*2 + 1;
                }else{
                    break;
                }
            }
        }
        if (index == dist2[dot] and dist2[dot] != 999999){
            dist2[dot] = 999999;
            alldist += index;
            for (const pair<int,int>& i: matrix[dot]){
                if (i.second < dist2[i.first] and dist2[i.first] != 999999){
                    dist2[i.first] = i.second;
                    if (counter < dist.size()){
                        dist[counter] = {i.second,i.first};
                    } else{
                        dist.emplace_back(i.second,i.first);
                    }
                    counter++;
                    int buf = counter - 1;
                    int buf2 = counter - 1;
                    if (buf % 2 == 0){
                        buf--;
                    }
                    while (buf > 0){
                        buf = buf / 2;
                        if (dist[buf2] < dist[buf]){
                            swap(dist[buf2],dist[buf]);
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
    cout << alldist;
    return 0;
}
