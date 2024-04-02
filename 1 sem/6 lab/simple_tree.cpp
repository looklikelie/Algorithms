#include <string>
#include <iostream>

using namespace std;

int glob_size = 0;

struct Top {
    long long val = 0;
    Top * parent = nullptr;
    Top * left = nullptr;
    Top * right = nullptr;
};



void Insert_Top(Top * root, long long val) {
    if (glob_size == 0) {
        root->val = val;
        glob_size = 1;
        return;
    }
    if (val < root->val) {
        if (root->left == nullptr) {
            root->left = new Top;
            root->left->val = val;
            root->left->parent = root;
            glob_size++;
            return;
        }
        return (Insert_Top(root->left, val));
    }
    if (val > root->val) {
        if (root->right == nullptr) {
            root->right = new Top;
            root->right->val = val;
            root->right->parent = root;
            glob_size++;
            return;
        }
        return (Insert_Top(root->right, val));
    }
}
bool Exists_Top(Top * root, long long val) {
    if (root == nullptr)
        return false;

    if (val == root->val)
        return true;

    if (val > root->val)
        return(Exists_Top(root->right, val));

    if (val < root->val)
        return(Exists_Top(root->left, val));
    return false;
}

void Delete_Top(Top * root, long long val);

void Delete_root(Top * root) {
    Top * vert = root;
    if (glob_size <= 0)
        return;

    if (vert->left == nullptr && vert->right == nullptr) {
        glob_size = 0;
        return;
    }

    if (glob_size == 1) {
        glob_size = 0;
        return;
    }

    if (vert->left != nullptr && vert->right != nullptr) {
        Top * swap = vert->right;
        while (swap->left != nullptr)
            swap = swap->left;

        long long tmp = swap->val;
        Delete_Top(root, swap->val);
        vert->val = tmp;
        return;
    }
    Top * change;
    if (vert->left != nullptr)
        change = vert->left;
    else change = vert->right;

    *root = *change;

    if (change->left != nullptr)
        change->left->parent = root;
    if (change->right != nullptr)
        change->right->parent = root;
    glob_size--;
    delete change;
}

void Delete_Top(Top * root, long long val) {
    if (glob_size <= 0)
        return;
    if (root->val == val) {
        Delete_root(root);
        return;
    }

    Top * vert = root;
    while (vert != nullptr) {
        if (val < vert->val)
            vert = vert->left;
        else if (val > vert->val)
            vert = vert->right;
        else break;
    }

    if (vert == nullptr)
        return;

    if (vert->left == nullptr && vert->right == nullptr) {
        if (vert->parent->left == vert)
            vert->parent->left = nullptr;
        else vert->parent->right = nullptr;
        delete vert;
        glob_size--;
    }
    else if (vert->left != nullptr && vert->right != nullptr) {
        Top * swap = vert->right;
        while (swap->left != nullptr)
            swap = swap->left;

        long long tmp = swap->val;
        Delete_Top(root, swap->val);
        vert->val = tmp;
    }
    else {
        Top * change;
        if (vert->left != nullptr)
            change = vert->left;
        else change = vert->right;

        if (vert->parent->left == vert)
            vert->parent->left = change;
        else vert->parent->right = change;
        change->parent = vert->parent;
        delete vert;
        glob_size--;
    }
}

Top * Next_Top(Top * root, long long val) {
    if (glob_size <= 0)
        return nullptr;

    if (glob_size == 1) {
        if (val < root->val)
            return root;
        else return nullptr;
    }

    Top * vert = root;
    while (vert != nullptr) {
        if (val < vert->val)
            if (vert->left != nullptr)
                vert = vert->left;
            else break;
        else if (val > vert->val)
            if (vert->right != nullptr)
                vert = vert->right;
            else break;
        else break;
    }

    if (vert == nullptr)
        return nullptr;

    if (val < vert->val)
        return vert;

    if (vert->right != nullptr) {
        vert = vert->right;
        while (vert->left != nullptr)
            vert = vert->left;
        return vert;
    }

    Top * check = vert;
    Top * parent = vert->parent;
    while (true) {
        if (parent == nullptr)
            return nullptr;
        else if (check == parent->right) {
            check = parent;
            parent = parent->parent;
        }
        else if (check == parent->left)
            return parent;
        else return nullptr;
    }
}
Top * Prev_Top(Top * root, long long val) {
    if (glob_size <= 0)
        return nullptr;

    if (glob_size == 1) {
        if (val > root->val)
            return root;
        else return nullptr;
    }

    Top *vert = root;
    while (vert != nullptr) {
        if (val < vert->val)
            if (vert->left != nullptr)
                vert = vert->left;
            else break;
        else if (val > vert->val)
            if (vert->right != nullptr)
                vert = vert->right;
            else break;
        else break;
    }

    if (vert == nullptr)
        return nullptr;

    if (val > vert->val)
        return vert;

    if (vert->left != nullptr) {
        vert = vert->left;
        while (vert->right != nullptr)
            vert = vert->right;
        return vert;
    }

    Top *check = vert;
    Top *parent = vert->parent;
    while (true) {
        if (parent == nullptr)
            return nullptr;
        else if (check == parent->left) {
            check = parent;
            parent = parent->parent;
        } else if (check == parent->right)
            return parent;
        else return nullptr;
    }

}

int main() {
    freopen ( "bstsimple.in", "r", stdin );
    freopen ( "bstsimple.out", "w", stdout );


    Top root;
    string command;
    long long val;
    Top * check = nullptr;


    while (cin >> command >> val) {

        if (command == "insert")
            Insert_Top(&root, val);
        else if (command == "exists")
            if (Exists_Top(&root, val))
                cout << "true\n";
            else cout << "false\n";
        else if (command == "delete")
            Delete_Top(&root, val);
        else if (command == "next") {
            check = Next_Top(&root, val);
            if (check != nullptr)
                cout << check->val <<"\n";
            else cout << "none\n";
        }
        else if (command == "prev") {
            check = Prev_Top(&root, val);
            if (check != nullptr)
                cout << check->val << "\n";
            else cout << "none\n";
        }
    }

    return 0;
}
