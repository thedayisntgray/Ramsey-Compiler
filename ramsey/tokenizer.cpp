#include <iostream>
#include <string>
#include "tokenizer.h"
using namespace std;

int main()
{   
    string lexeme = "\n";
    while(lexeme != "quit")
    {
        cout << "Enter lexeme to be classified:" << endl;
        cin >> lexeme;
        cout << getTokenType(lexeme) << '\n';
        //break;
    }
}
