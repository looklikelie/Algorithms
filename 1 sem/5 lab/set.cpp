#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;


struct Stack
{
    int Value;
    Stack *Next;
};

class List
{
    Stack *Start;
public:
    List();
    void Insert(int number);
    void Delete(int number);
    bool Search(int number);
};
List::List()
{
    Start = new Stack();
    Start->Value;
    Start->Next = nullptr;
}

void List::Insert(int number)
{
    Stack *New_Stack = new Stack;
    New_Stack->Value = number;
    New_Stack->Next = Start->Next;
    Start->Next = New_Stack;
}

void List::Delete(int number)
{
    Stack *Current_Stack = Start;
    while (Current_Stack->Next != nullptr)
    {
        if (Current_Stack->Next->Value == number)
        {
            Stack *Stack_to_Delete = Current_Stack->Next;
            Current_Stack->Next = Current_Stack->Next->Next;
            delete Stack_to_Delete;
            return;
        }
        else
        {
            Current_Stack = Current_Stack->Next;
        }
    }
}

bool List::Search(int number)
{
    Stack *Current_Stack = Start;
    while (Current_Stack->Next != nullptr)
    {
        if (Current_Stack->Next->Value == number)
        {
            return true;
        }
        else
        {
            Current_Stack = Current_Stack->Next;
        }
    }
    return false;
}


class Set
{
    vector<List> Src;
    int Hash_function(int number);
public:
    Set();
    void Insert(int number);
    bool Search(int number);
    void Delete(int number);
};

Set::Set()
{
    Src.resize(100000);
}

int Set::Hash_function(int number)
{
    int res = number % (int)Src.size();
    if (res < 0) res += Src.size();
    return res;
}

void Set::Insert(int number)
{
    if (!Search(number)) Src[Hash_function(number)].Insert(number);
}

bool Set::Search(int number)
{
    return Src[Hash_function(number)].Search(number);
}

void Set::Delete(int number)
{
    Src[Hash_function(number)].Delete(number);
}



int main()
{
    ifstream fin("set.in");
    ofstream fout("set.out");
    Set S;
    string Command;
    while (fin >> Command)
    {
        int number;
        if (Command == "insert")
        {
            fin >> number;
            S.Insert(number);
        }
        else if (Command == "delete")
        {
            fin >> number;
            S.Delete(number);
        }
        else if (Command == "exists")
        {
            fin >> number;
            if (S.Search(number))
                fout << "true\n";
            else
                fout << "false\n";
        }
    }
    return 0;
}
