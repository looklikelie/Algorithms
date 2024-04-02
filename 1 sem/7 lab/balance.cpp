#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

template<typename T>
class tree {
public:

    template<typename A>
    struct Node {
        int fac = 0;
        A value = 0;
        Node<A> *left = nullptr;
        Node<A> *right = nullptr;
    };

    Node<T> *element = new Node<T>[200000];

    int height(Node<T> *p) {
        int l, r, h = 0;
        if (p != NULL) {
            l = height(p->left);
            r = height(p->right);
            if (l > r){
                h = l + 1;
            }
            else {
                h = r + 1;
            }
            p->fac = r - l;
        }
        return h;
    }

    void push(int index, T value, int l, int r) {
        element[index].value = value;
        if (l != 0)
            element[index].left = &element[l];
        if (r != 0)
            element[index].right = &element[r];
    }

    int helpHeight() {
        return height(&element[1]);
    }

    void output(int n, ofstream &cout) {
        for (int i = 1; i <= n; i++)
            cout << element[i].fac << endl;
    }
};

int main() {
    ifstream cin("balance.in");
    ofstream cout("balance.out");
    tree<int> a;
    int n;
    int value;
    int l, r;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> value >> l >> r;
        a.push(i, value, l, r);
    }
    a.helpHeight();
    a.output(n, cout);
    return 0;
}
