#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;


struct Stack
{
    string key, value;
    Stack *next;
};

class List
{
    Stack *pointer;
public:
    List();
    void put_key(string input_key, string input_value);
    void delete_key(string input_key);
    Stack* get_key(string input_key);
};

List::List()
{
    pointer = new Stack();
    pointer->value = pointer->key = "";
    pointer->next = nullptr;
}

void List::put_key(string input_key, string input_value)
{
    Stack *new_stack = get_key(input_key);
    if (get_key(input_key) == nullptr)
    {
        new_stack = new Stack;
        new_stack->key = input_key;
        new_stack->value = input_value;
        new_stack->next = pointer->next;
        pointer->next = new_stack;

    }
    else
    {
        new_stack->value = input_value;
    }
}

void List::delete_key(string input_key)
{
    Stack *current_stack = pointer;
    while (current_stack->next != nullptr)
    {
        if (current_stack->next->key == input_key)
        {
            Stack *delete_stack = current_stack->next;
            current_stack->next = current_stack->next->next;

            delete delete_stack;
            return;
        }
        else
        {
            current_stack = current_stack->next;
        }
    }
}

Stack* List::get_key(string input_key)
{
    Stack *current_stack = pointer;
    while (current_stack->next != nullptr)
    {
        if (current_stack->next->key == input_key)
        {
            return current_stack->next;
        }
        else
        {
            current_stack = current_stack->next;
        }
    }
    return nullptr;
}

class Input_map
{
    vector<List> input_hash_table;
    int hash_function(string input_key);
public:
    Input_map();
    void put_key(string input_key, string input_value);
    void delete_key(string input_key);
    string get_key(string input_key);
};

Input_map::Input_map()
{
    input_hash_table.resize(1000);
}

int Input_map::hash_function(string input_key)
{
    unsigned int result = 0, power = 1, index = 31, size = input_hash_table.size();
    for (int i = 0; i < input_key.length(); ++i)
    {
        result += (input_key[i] - 'A') * power;
        power *= index;
    }
    return result % size;
}

void Input_map::put_key(string input_key, string input_value)
{
    input_hash_table[hash_function(input_key)].put_key(input_key, input_value);
}

string Input_map::get_key(string input_key)
{
    Stack *result = input_hash_table[hash_function(input_key)].get_key(input_key);
    if (result == nullptr)
        return "none";
    else
        return result->value;
}

void Input_map::delete_key(string input_key)
{
    input_hash_table[hash_function(input_key)].delete_key(input_key);
}



int main()
{
    ifstream file_in("map.in");
    ofstream file_out("map.out");
    Input_map hash_table;
    string command;
    while (file_in >> command)
    {
        string input_key, input_value;
        if (command == "put")
        {
            file_in >> input_key >> input_value;
            hash_table.put_key(input_key, input_value);
        }
        else if (command == "delete")
        {
            file_in >> input_key;
            hash_table.delete_key(input_key);
        }
        else if (command == "get")
        {
            file_in >> input_key;
            file_out << hash_table.get_key(input_key) << "\n";
        }

    }
    return 0;

}
