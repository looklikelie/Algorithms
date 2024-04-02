#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void mergee(vector<vector<string> >& p, int left, int mid, int right){
    int it1 = 0;
    int it2 = 0;
    vector<vector<string> > result;
    while(left + it1 < mid && mid + it2 < right){
        if (p[left + it1][0] <= p[mid + it2][0]){
            result.push_back(p[left + it1]);
            it1++;
        }else{
            result.push_back(p[mid + it2]);
            it2++;
        }
    }
    while(left + it1 < mid){
        result.push_back(p[left + it1]);
        it1++;
    }
    while(mid + it2 < right){
        result.push_back(p[mid + it2]);
        it2++;
    }
    for(int i = 0; i < it1 + it2; i++){
        p[left + i] = result[i];
    }
}

void mergesort(vector<vector<string> >& p, int left, int right){
    if(left + 1 >= right){
        return;
    }
    int mid = (left + right) / 2;
    mergesort(p, left, mid);
    mergesort(p, mid, right);
    mergee(p, left, mid, right);
}
int main()
{
    ifstream ifile("race.in");
    int n;
    ifile >> n;
    vector<vector<string> > p (n);
    for(int i = 0; i < n; i++){
        string asd;
        for(int j = 0; j < 2; j++){
             ifile >> asd;
             p[i].push_back(asd);
        }
    }
    mergesort(p, 0, n);
    string country;
    ofstream ofile("race.out");
    ofile << "=== " << p[0][0] << " ===" << '\n';
    ofile << p[0][1] << '\n';
    country = p[0][0];
    for(int j = 1; j < n; j++){
        for(int i = 0; i < 1; i++){
            if(country != p[j][0]){
                ofile << "=== " << p[j][0] << " ===" << '\n';
                ofile << p[j][1] << '\n';
            }else{
                ofile << p[j][1] << '\n';
            }
            country = p[j][0];
        }
    }
    return 0;
}
