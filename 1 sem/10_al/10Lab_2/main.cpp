#include <iostream>
#include <math.h>
#include <fstream>

using namespace std;

int main()
{
    int n;
    ifstream cin("spantree.in");
    ofstream cout("spantree.out");
    cin >> n;
    double arr[n][2];
    double dist[n];
    bool flags[n];
    double alldist, mindist;
    for(int i = 0; i < n; i++){
        flags[i] = false;
        cin >> arr[i][0] >> arr[i][1];
        dist[i] = pow(pow(arr[i][0] - arr[0][0],2) + pow(arr[i][1] - arr[0][1],2), 0.5);
    }
    flags[0] = true;
    while (true) {
        int dot, index;
        index = flags[0];
        mindist = 1000000;
        for (int j = 1; j < n; ++j) {
            if (flags[j] < index) {
                index = flags[j];
            }
            if (!flags[j] and dist[j] < mindist){
                dot = j;
                mindist = dist[j];
            }
        }
        if (index) {
            break;
        }
        alldist += mindist;
        flags[dot] = true;
        for (int i = 0; i < n; ++i) {
            if (!flags[i]){
                dist[i] = min(dist[i],pow(pow(arr[i][0] - arr[dot][0],2) + pow(arr[i][1] - arr[dot][1],2), 0.5));
            }
        }
    }
    cout.precision(20);
    cout << alldist;
    return 0;
}
