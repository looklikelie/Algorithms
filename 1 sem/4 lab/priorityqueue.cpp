#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main()
{
    ifstream cin("priorityqueue.in");
    ofstream cout("priorityqueue.out");
    int arr[1000000][2];
    int head = 0;
    int iter = 0;
    string command;
    while(cin >> command){
        iter++;
        if(command == "push"){
            cin >> arr[head][0];
            arr[head][1] = iter;
            head++;
        }
        int min_el;
        int min_el_pos;
        if(command == "extract-min"){
            if(0 == head){
                cout << '*' << '\n';
            } else {
                min_el = arr[0][0];
                min_el_pos = 0;
                for(int i = 1; i < head; i++){
                    if(arr[i][0] < min_el){
                        min_el = arr[i][0];
                        min_el_pos = i;
                    }
                }
                cout << min_el << '\n';
                for(int i = min_el_pos; i < head - 1; i++){
                    arr[i][0] = arr[i+1][0];
                    arr[i][1] = arr[i+1][1];
                }
                head--;
            }
        }
        int number_command;
        int decrease;
        if(command == "decrease-key"){
            cin >> number_command >> decrease;
            for(int i = 0; i < head; i++){
                if(arr[i][1] == number_command){
                    arr[i][0] = decrease;
                    break;
                }
            }
        }
    }
    return 0;
}
