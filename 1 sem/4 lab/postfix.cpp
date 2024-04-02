#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>

using namespace std;

int main()
{
    ifstream cin("postfix.in");
    ofstream cout("postfix.out");
    int arr[101];
    string term;
    int iter = 0;
    getline(cin, term);
    for(int i = 0; i < term.size(); i+=2){
        if(term[i] != '+' && term[i] != '-' && term[i] != '*'){
            arr[iter] = term[i] - 48;
            iter++;
        } else if (term[i] == '-'){
            arr[iter - 2] = arr[iter - 2] - arr[iter - 1];
            iter--;
        } else if (term[i] == '+'){
            arr[iter - 2] = arr[iter - 2] + arr[iter - 1];
            iter--;
        } else if (term[i] == '*'){
            arr[iter - 2] = arr[iter - 2] * arr[iter - 1];
            iter--;
        }
    }
    cout << arr[0];
    return 0;
}
