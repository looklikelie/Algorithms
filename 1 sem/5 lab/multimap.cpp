#include <iostream>
#include <vector>
using namespace std;

struct List{
    List* prev = nullptr;
    string value;
    List* next = nullptr;
};

class Map{
    static const long long mode = 317;
    long long size = 0;
    vector<List*> set;
    static long long Hash_function(string& input_string){
        const int index = 31;
        long long hash = 0, power = 1;
        for (char i : input_string){
            hash += (i - 'a' + 1) * power;
            power *= index;
        }
        if (hash >= 0)
            return hash % mode;
        else
            return (mode - abs(hash) % mode) % mode;
    }
public:
    Map() {
        size = 0;
        set = vector<List*>(mode);
    }
    List* Create_stack(string key) {
        auto Stack = new List;
        Stack->prev = nullptr;
        Stack->value = key;
        Stack->next = nullptr;
        return Stack;
    }
    List* AddStack(List* tail, string key){
        List* Stack = Create_stack(key);
        Stack->prev = tail;
        tail->next = Stack;
        Stack->value = key;
        return Stack;
    }
    void add(string input_string){
        long long hashed_x = Hash_function(input_string);
        List* head = set[hashed_x];
        if (head == nullptr){
            set[hashed_x] = Create_stack(input_string);
            size++;
        }
        else{
            List* pointer = set[Hash_function(input_string)];
            while (pointer->next != nullptr){
                if (pointer->value == input_string)
                    return;
                pointer = pointer->next;
            }
            if (pointer->value != input_string){
                AddStack(pointer, input_string);
                size++;
            }
        }
    }

    void remove(string input_string){
        List* pointer = set[Hash_function(input_string)];
        if (pointer == nullptr) return;
        if (pointer->value == input_string){
            set[Hash_function(input_string)] = pointer->next;
            size--;
            free(pointer);
            return;
        }
        while (pointer != nullptr){
            if (pointer->value == input_string){
                if (pointer->prev != nullptr)
                    pointer->prev->next = pointer->next;
                if (pointer->next != nullptr)
                    pointer->next->prev = pointer->prev;
                size--;
                free(pointer);
                return;
            }
            pointer = pointer->next;
        }
    }
    void print(){
        cout << size << " ";
        for (long long i = 0; i < mode; ++i){
            if (set[i] != nullptr){
                List* pointer = set[i];
                while (pointer != nullptr){
                    cout << pointer->value << " ";
                    pointer = pointer->next;
                }
            }
        }
        cout << "\n";
    }
};

struct Map_Stack{
    Map_Stack* prev = nullptr;
    string key;
    Map values;
    Map_Stack* next = nullptr;
};

Map_Stack* Map_create_stack(string& key, string& value){
    auto Stack = new Map_Stack;
    Stack->prev = nullptr;
    Stack->key = key;
    Stack->values = Map();
    Stack->values.add(value);
    Stack->next = nullptr;
    return Stack;
}

Map_Stack* Map_add_stack(Map_Stack* tail, string& key, string& value){
    Map_Stack* Stack = Map_create_stack(key, value);
    Stack->prev = tail;
    tail->next = Stack;
    return Stack;
}

long long Hash_function(string& input_string){
    const int index = 31;
    long long hash = 0, power = 1;
    for (char i : input_string){
        hash += (i - 'a' + 1) * power;
        power *= index;
    }
    long long m = 10007;
    if (hash >= 0)
        return hash % m;
    else
        return (m - abs(hash) % m) % m;

}

void Put(string& key, string& value, vector<Map_Stack*>& set){
    Map_Stack* head = set[Hash_function(key)];
    if (head == nullptr)
        set[Hash_function(key)] = Map_create_stack(key, value);
    else{
        Map_Stack* pointer = set[Hash_function(key)];
        while (pointer->next != nullptr){
            if (pointer->key == key){
                pointer->values.add(value);
                return;
            }
            pointer = pointer->next;
        }
        if (pointer->key != key)
            Map_add_stack(pointer, key, value);
        else
            pointer->values.add(value);
    }
}

void Delete(string key, string value, vector<Map_Stack*>& set){
    Map_Stack* pointer = set[Hash_function(key)];
    while (pointer != nullptr){
        if (pointer->key == key){
            pointer->values.remove(value);
            return;
        }
        pointer = pointer->next;
    }
}

void DeleteAll(string key, vector<Map_Stack*>& set){
    Map_Stack* pointer = set[Hash_function(key)];
    if (pointer == nullptr) return;

    if (pointer->key == key){
        set[Hash_function(key)] = pointer->next;
        free(pointer);
        return;
    }

    while (pointer != nullptr){
        if (pointer->key == key){
            if (pointer->prev != nullptr)
                pointer->prev->next = pointer->next;
            if (pointer->next != nullptr)
                pointer->next->prev = pointer->prev;
            free(pointer);
            return;
        }
        pointer = pointer->next;
    }

}

bool Get(string& key, vector<Map_Stack*>& set){
    Map_Stack* pointer = set[Hash_function(key)];
    while (pointer != nullptr){
        if (pointer->key == key){
            pointer->values.print();
            return true;
        }
        pointer = pointer->next;
    }
    cout << "0\n";
    return false;
}


int main() {
    freopen("multimap.in", "r", stdin);
    freopen("multimap.out", "w", stdout);
    vector<Map_Stack *> set(10007);
    string command;
    string key, value;
    while (cin >> command) {
        cin >> key;
        if (command == "put") {
            cin >> value;
            Put(key, value, set);
        } else if (command == "delete") {
            cin >> value;
            Delete(key, value, set);
        } else if (command == "deleteall")
            DeleteAll(key, set);

        else if (command == "get")
            Get(key, set);
    }
}
