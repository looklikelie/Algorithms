#include <vector>
#include <iostream>
#include <string>

using namespace std;

int main(){
    int n;
    string s;
    cin >> n >> s;
    vector<int> pi_func(s.size(),0);
    for (int i = 1; i < s.size(); ++i) {
        int k = pi_func[i - 1];
        while (k > 0 and s[k] != s[i]){
            k = pi_func[k - 1];
        }
        if (s[i] == s[k]){
            k++;
        }
        pi_func[i] = k;
    }
    vector<vector<int>> ans(s.size() + 1,vector<int>(n,0));
    for (int j = 0; j < s.size() + 1; ++j) {
        for (int i = 0; i < n; ++i) {
            if (j > 0 and (char)(i + 'a') != s[j]){
                ans[j][i] = ans[pi_func[j - 1]][i];
            }else{
                if ((char)(i + 'a') == s[j]){
                    ans[j][i] = j + 1;
                } else{
                    ans[j][i] = j;
                }
            }
        }
    }
    for(auto i : ans){
        for(auto j : i)
            cout << j << ' ';
        cout << '\n';
    }
    return 0;
}
