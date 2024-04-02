#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ifstream cin("search1.in");
    ofstream cout ("search1.out");
    string p,t;
    cin >> p >> t;
    vector<int> ans{};
    if (t.size() >= p.size()){
        for (int i = 0;i < t.size() - p.size() + 1;i++){
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
    cout << ans.size() << "\n";
    for (auto& i:ans){
        cout << i << " ";
    }
    cin.close();
    cout.close();
    return 0;
}
