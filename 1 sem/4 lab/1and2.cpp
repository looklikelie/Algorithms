#include <iostream>
#include <fstream>

using namespace std;

/*class stacks{
public:
    int arr[1000001];
    int iter;
};*/

int main()
{
    //stacks first;
    ifstream cin("queue.in");
    ofstream cout("queue.out");
    int arr[1000000];
    int iter_add = 0;
    int iter_delete = 0;
    int n;
    cin >> n;
    int number;
    char sign;
    for(int i = 0; i < n; i++){
        cin >> sign;
        if(sign == '+'){
            cin >> number;
            arr[iter_add] = number;
            iter_add++;
        } else {
            cout << arr[iter_delete] << '\n';
            arr[iter_delete] = 0;
            iter_delete++;
        }
    }

    return 0;
}
