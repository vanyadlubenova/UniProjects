#include <iostream>
#include "Stack.h"
#include "CharBuffer.h"
#include <fstream>
using namespace std;

void decompress(ifstream& in, Stack<int>& numbers, Stack<CharBuffer>& symbols)
{
    char next;
    if(!in.eof())
    {
        next = in.get();
    }
    while(!in.eof())
    {
        CharBuffer n;
        if(next >= '0' && next <= '9')
        {
            in.unget();
            int num;
            in >> num;
            numbers.push(num);
        }
        else if(next == '\\')
        {
            n.push(in.get());
            symbols.push(n);
        }
        else if(next != ')')
        {
            n.push(next);
            symbols.push(n);
        }
        else
        {
            CharBuffer buff;
            CharBuffer n = symbols.pop();
            while(n.get(0) != '(')
            {
                buff.concat(n);
                n = symbols.pop();
            }
            int it = numbers.pop();
            CharBuffer tmp(buff);
            while(it - 1 > 0)
            {
                buff.concat(tmp);
                it--;
            }
            symbols.push(buff);
        }

     next = in.get();
    }
}
int main(int argc, char* argv[])
{
    if(argc == 1)
    {
        cout << "Missing main arguments";
    }
    ifstream in(argv[1]);
    if(!in)
    {
        cout << "Can't open file for reading";
        return -1;
    }

    Stack<int> numbers;
    Stack<CharBuffer> symbols;
    try{
    decompress(in, numbers, symbols);
    }
    catch(string ex)
    {
        cout << ex;
        return -1;
    }
    CharBuffer decompressed;
    while(!symbols.isEmpty())
    {
        decompressed.concat(symbols.pop());
    }
    decompressed.reverse();
    in.close();

    ofstream out(argv[2]);
    if(!out)
    {
        cout << "Can't open file for writing";
        return -1;
    }
    out << decompressed.getBuffer();
    cout << decompressed.getBuffer();
    out.close();

    return 0;
}
