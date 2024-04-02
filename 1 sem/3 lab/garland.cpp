#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main()
{
    //ifstream cin("garland.in");
    //ofstream cout("garland.out");
    int n;
    cin >> n;
    double A;
    cin >> A;
    double current, previous, minimum, someoneelse;
    double l = 0, r = A;
    double A2;
    while(r-l > 0.0000000000001){
        A2 = (l+r)/2;
        previous = A;
        current = A2;
        minimum = min(A,A2);
        for(int i = 2; i < n; i++){
            someoneelse = current;
            current = current*2 - previous + 2;
            minimum = min(min(current, previous),minimum);
            previous = someoneelse;
        }
        if(minimum < 0){
            l = A2;
        }else{
            r = A2;
        }
    }
    cout << fixed << setprecision(2) << current;

    return 0;
}
