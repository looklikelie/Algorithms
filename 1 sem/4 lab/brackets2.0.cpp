#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    ifstream cin("brackets.in");
    ofstream cout("brackets.out");
    char arr[1000000];
    string brack;
    int iter = 0;
    while(getline(cin, brack)){
            iter = 0;
        for(unsigned int i = 0; i < brack.size(); i++){
            if (brack[i] == '(' || brack[i] == '['){
                arr[iter] = brack[i];
                iter++;
            } else if(brack[i] == ')'){
                if(arr[iter-1] == '('){
                    iter--;
                    arr[iter] = ' ';
                } else {
                    arr[0] = '1';
                    break;
                }
            } else if(brack[i] == ']'){
                if(arr[iter-1] == '['){
                    iter--;
                    arr[iter] = ' ';
                } else {
                    arr[0] = '1';
                    break;
                }
            }
        }
        if(arr[0] == ' '){
            cout << "YES" << '\n';
        } else if(arr[0] != ' '){
            cout << "NO" << '\n';
        }
    }
    return 0;
}
