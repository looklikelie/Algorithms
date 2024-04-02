#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

template<typename T>
class tree {

    template<typename A>
    struct node {
        int height = 0;
        int idx = 0;
        A value = 0;
        node<A> *left  = nullptr;
        node<A> *right = nullptr;
    };

    node<T> *elem = new node<T>[200000];

    node<T> *root = elem + 1;

    int height1(node<T> *p) {
        int l, r, h = 0;
        if (p != NULL) {
            l = height1(p->left);
            r = height1(p->right);
            h = (l > r ? l : r) + 1;
            p->height = h;
        }
        return h;
    }

    int height(node<T> *p)
    {
        return p ? p->height : 0;
    }

    int bfactor(node<T> *p)
    {
        return height(p->right) - height(p->left);
    }

    void fixheight(node<T> *p)
    {
        int l = height(p->left);
        int r = height(p->right);
        p->height = (l > r ? l : r) + 1;
    }

    node<T>* bigLeftRotate (node<T> *p){
        node<T>* q = p->left;
        p->left = q->right;
        q->right = p;
        fixheight(p);
        fixheight(q);
        return q;
    }

    node<T>* leftRotate(node<T> *q){
        node<T>* p = q->right;
        q->right = p->left;
        p->left = q;
        fixheight(q);
        fixheight(p);
        return p;
    }

    node<T>* balance(node<T> *p){
        if (bfactor(p) == 2)
        {
            if (bfactor(p->right) < 0)
                p->right = bigLeftRotate(p->right);
            return leftRotate(p);
        }
    }

    int count(node<T> *p, int i) {
        if (p != NULL) {
            p->idx = i;
            if(p->left != NULL)
                i = count(p->left, i + 1);
            if (p->right != NULL)
                i = count(p->right, i + 1);
        }
        return i;
    }

    void print(node<T> *p, ofstream &cout) {
        if (p != NULL) {
            cout << p->value << " ";
            if (p->left != NULL)
                cout << p->left->idx << " ";
            else
                cout << 0 << " ";
            if (p->right != NULL)
                cout << p->right->idx << " ";
            else
                cout << 0 << " ";
            cout << endl;

            if (p->left != NULL)
                print(p->left, cout);
            if (p->right != NULL)
                print(p->right, cout);
        }
    }

public:

    void push(int idx, T value, int l, int r) {
        elem[idx].value = value;
        if (l != 0)
            elem[idx].left = &elem[l];
        if (r != 0)
            elem[idx].right = &elem[r];
    }

    int height() {
        return height1(root);
    }

    void help_print(ofstream &cout) {
        count(root, 1);
        print(root, cout);
    }

    void help_balance() {
        height();
        root = balance(root);
    }
};

int main() {
    ifstream cin("rotation.in");
    ofstream cout("rotation.out");
    tree<int> a;
    int n;
    int value;
    int l, r;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> value >> l >> r;
        a.push(i, value, l, r);
    }
    a.help_balance();
    cout << n << endl;
    a.help_print(cout);
    return 0;
}
