#include <iostream>
#include <fstream>

using namespace std;


struct top
{
    long long val = 0;
    int left = 0;
    int right = 0;
};

bool Check_top(top *array, int check, long long min, long long max){
    if (array[check].val <= min){
        return false;
    }
    if (array[check].val >= max){
        return false;
    }
    if (array[check].left > 0){
        if (!Check_top(array, array[check].left, min, array[check].val)){
            return false;
        }
    }
    if (array[check].right > 0){
        if (!Check_top(array, array[check].right,array[check].val, max)){
            return false;
        }
    }
    return true;
}

bool Check_Tree(top * array)
{
    if (array[0].left > 0){
        if (!Check_top(array,array[0].left,-1000000000,array[0].val)){
            return false;
        }
    }

    if (array[0].right > 0){
        if (!Check_top(array, array[0].right, array[0].val, 1000000000)){
            return false;
        }
    }

    return true;
}

int main(){
    ifstream cin("check.in");
    ofstream cout("check.out");

    int size;
    cin >> size;
    if (size < 2){
        cout << "YES";
        return 0;
    }

    top * array = new top[size];
    int left_child, right_child;
    long long value;
    cin >> value >> left_child >> right_child;
    array[0].val = value;
    array[0].left = left_child - 1;
    array[0].right = right_child - 1;

    for (int i = 1; i < size; i++){
        cin >> value >> left_child >> right_child;
        left_child--;
        right_child--;
        array[i].val = value;
        array[i].left = left_child;
        array[i].right = right_child;

    }

    if (!Check_Tree(array)){
        cout << "NO";
    }
    else{
        cout << "YES";
    }
    return 0;
}
