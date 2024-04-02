#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
using namespace std;
const int len = 1000000;

struct Stack{
    int key;
    int right = NULL;
    int left = NULL;
};
Stack *vector_node[len];
int height_bin( int bin_v ){
    int elevation, second_elevation;
    if( vector_node[bin_v] == NULL)
        return 0;
    elevation = height_bin( vector_node[bin_v]->left )+1;
    second_elevation = height_bin( vector_node[bin_v]->right )+1;
    int bin_elev = max(elevation, second_elevation);
    return(bin_elev);
}
void add(int i, int int_key, int int_left, int int_right ){
    vector_node[i] = new Stack;
    vector_node[i]->key= int_key;
    vector_node[i]->left = int_left;
    vector_node[i]->right = int_right;
}

int main(){
    ifstream cin("height.in");
    ofstream cout("height.out");
    int n, key, left, right;
    int begin_index = 1;
    cin >> n;
    for( int i = 1; i <= n; i++ ){
        cin >> key >> left >> right;
        add( i, key, left, right );
    }
    cout << height_bin(begin_index);
    return 0;
}
