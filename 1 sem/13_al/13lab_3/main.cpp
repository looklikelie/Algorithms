#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

int main(){
    ifstream cin("prefix.in");
    ofstream cout("prefix.out");
    string s;
    cin >> s;
    vector<int> pi_func(s.size(),0);
    int j = 0;
    int i = 1;
    while (i < s.size()){
        if (s[i] == s[j]){
            pi_func[i] = j+1;
            i++;
            j++;
        } else if (j == 0){
            pi_func[i] = 0;
            i++;
        } else{
            j = pi_func[j - 1];
        }
    }
    for( auto& i:pi_func){
        cout << i << " ";
    }
    cin.close();
    cout.close();

    return 0;
}
