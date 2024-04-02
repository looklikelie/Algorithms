#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;


struct Stack
{
    string key, value;
    Stack *next_in_stack;
    Stack *next_element, *previous_element;
};

class List
{
    Stack *start;
public:
    List();
    void put_key(string input_key, string input_value, Stack *head);
    void delete_key(string input_key);
    Stack* get_key(string input_key);
};

List::List()
{
    start = new Stack();
    start->value = start->key = "";
    start->next_in_stack = nullptr;
}

void List::put_key(string input_key, string input_value, Stack *head)
{
    Stack *new_stack = get_key(input_key);
    if (get_key(input_key) == nullptr)
    {
        new_stack = new Stack;
        new_stack->key = input_key;
        new_stack->value = input_value;
        new_stack->next_in_stack = start->next_in_stack;
        start->next_in_stack = new_stack;
        Stack *tail = head->previous_element;
        tail->next_element = new_stack;
        head->previous_element = new_stack;
        new_stack->next_element = head;
        new_stack->previous_element = tail;
    }
    else
    {
        new_stack->value = input_value;
    }
}

void List::delete_key(string input_key)
{
    Stack *input_stack = start;
    while (input_stack->next_in_stack != nullptr)
    {
        if (input_stack->next_in_stack->key == input_key)
        {
            Stack *delete_stack = input_stack->next_in_stack;
            input_stack->next_in_stack = input_stack->next_in_stack->next_in_stack;
            Stack *previous_stack = delete_stack->previous_element, *next_stack = delete_stack->next_element;
            delete_stack->previous_element->next_element = next_stack;
            delete_stack->next_element->previous_element = previous_stack;
            delete delete_stack;
            return;
        }
        else
        {
            input_stack = input_stack->next_in_stack;
        }
    }
}

Stack* List::get_key(string input_key)
{
    Stack *input_stack = start;
    while (input_stack->next_in_stack != nullptr)
    {
        if (input_stack->next_in_stack->key == input_key)
        {
            return input_stack->next_in_stack;
        }
        else
        {
            input_stack = input_stack->next_in_stack;
        }
    }
    return nullptr;
}

class Linked_map
{
    vector<List> hash_table;
    Stack *head;
    int hash_function(string input_key);
public:
    Linked_map();
    void put_key(string input_key, string input_value);
    void delete_key(string input_key);
    string get_key(string input_key);
    string next(string input_key);
    string prev(string input_key);
};

Linked_map::Linked_map()
{
    hash_table.resize(1000);
    head = new Stack;
    head->next_element = head->previous_element = head;
    head->value = head->key = "";
}

int Linked_map::hash_function(string input_key)
{
    unsigned int result = 0, power = 1, index = 31, size = hash_table.size();
    for (int i = 0; i < input_key.length(); ++i)
    {
        result += (input_key[i] - 'A') * power;
        power *= index;
    }
    return result % size;
}

void Linked_map::put_key(string input_key, string input_value)
{
    hash_table[hash_function(input_key)].put_key(input_key, input_value, head);
}

string Linked_map::get_key(string input_key)
{
    Stack *result = hash_table[hash_function(input_key)].get_key(input_key);
    if (result == nullptr)
        return "none";
    else
        return result->value;
}

void Linked_map::delete_key(string input_key)
{
    hash_table[hash_function(input_key)].delete_key(input_key);
}

string Linked_map::next(string input_key)
{
    Stack *result = hash_table[hash_function(input_key)].get_key(input_key);
    if (result == nullptr || result->next_element == head)
        return "none";
    else
        return result->next_element->value;
}

string Linked_map::prev(string input_key)
{
    Stack *result = hash_table[hash_function(input_key)].get_key(input_key);
    if (result == nullptr || result->previous_element == head)
        return "none";
    else
        return result->previous_element->value;
}

int main()
{
    ifstream file_in("linkedmap.in");
    ofstream file_out("linkedmap.out");
    Linked_map input_hash_table;
    string command;
    while (file_in >> command)
    {
        string input_key, input_value;
        if (command == "put")
        {
            file_in >> input_key >> input_value;
            input_hash_table.put_key(input_key, input_value);
        }
        else if (command == "delete")
        {
            file_in >> input_key;
            input_hash_table.delete_key(input_key);
        }
        else if (command == "get")
        {
            file_in >> input_key;
            file_out << input_hash_table.get_key(input_key) << "\n";
        }
        else if (command == "next")
        {
            file_in >> input_key;
            file_out << input_hash_table.next(input_key) << "\n";
        }
        else if (command == "prev")
        {
            file_in >> input_key;
            file_out << input_hash_table.prev(input_key) << "\n";
        }
    }
    return 0;
}
