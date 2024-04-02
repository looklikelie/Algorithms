#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

int main(){
    ifstream cin("search2.in");
    ofstream cout("search2.out");
    vector<int> ans{};
    string p,t;
    cin >> p >> t;
    if (t.size() >= p.size()){
        int big = 1000000007;
        const int pp = 31;
        vector<long long> p_pow (max (p.length(), t.length()));
        p_pow[0] = 1;
        for (size_t i=1; i<p_pow.size(); ++i)
            p_pow[i] = p_pow[i-1] * pp;
        vector<long long> h (t.length());
        for (size_t i=0; i<t.length(); ++i)
        {
            h[i] = (t[i] - 'a' + 1) * p_pow[i];
            if (i)  h[i] += h[i-1];
        }
        long long h_p = 0;
        for (size_t i=0; i<p.length(); ++i)
            h_p += (p[i] - 'a' + 1) * p_pow[i];
        for (size_t i = 0; i + p.length() - 1 < t.length(); ++i)
        {
            long long cur_h = h[i+p.length()-1];
            if (i)  cur_h -= h[i-1];
            if (cur_h == h_p * p_pow[i]){
                bool flag = true;
                for (int j = 0; j < p.size(); ++j) {
                    if (t[i+j] != p[j]){
                        flag = false;
                        break;
                    }
                }
                if (flag){
                    ans.push_back(i+1);
                }
            }
        }
    }

    cout << ans.size() << "\n";
    for (auto& i:ans){
        cout << i << " ";
    }
    cin.close();
    cout.close();
    return 0;
}
