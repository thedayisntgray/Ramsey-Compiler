#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>
#include <queue>
#include "tokenizer.h"

struct token
{
  std::string token;
  std::string lexeme;
  int lineNumber;
};

std::string charToStr(char c){
  std::stringstream ss;
  std::string str;
  ss << c;
  ss >> str;
  return str;
}

int main () {
  char str[256];

  std::cout << "Enter the name of an existing text file: ";
  std::cin.get (str,256);    // get c-string
  std::ifstream is(str);     // open file

  std::string lex = "";
  int lineNum = 1;

  token t;
  std::queue<token> qlist;

  while (is.good())
  {
    std::stringstream ss;

    char c = is.get();
    std::string cn = charToStr(c);

    char p = is.peek();
    std::string peek = charToStr(p);

    std::cout << "outer loop" << std::endl;

    while(is.good()){

      if(cn == "" || cn == " ")
        break;

      lex += cn;
      //single parens
      if(lex == "("){
        t.token = getTokenType(lex);
        t.lexeme = lex;
        t.lineNumber = lineNum;
        lex = "";
        break;
      }
      if( peek == "(" ||
          peek == ")" ||
          peek == "+" ||
          peek == "*" ||
          peek == "/" ||
          ((getTokenType(lex) == "IDENT" ||
            getTokenType(lex) == "PLUS" ||
            getTokenType(lex) == "MINUS" ||
            getTokenType(lex) == "DIV" ||
            getTokenType(lex) == "MUL" ||
            getTokenType(lex) == "RPAREN")
            && peek == "-")
          ){
        t.token = getTokenType(lex);
        t.lexeme = lex;
        t.lineNumber = lineNum;
        lex = "";
        break;
      }
      if(lex == ")"){
        t.token = getTokenType(lex);
        t.lexeme = lex;
        t.lineNumber = lineNum;
        lex = "";
        break;
      }
      //single operators
      if(lex == "="){
        t.token = getTokenType(lex);
        t.lexeme = lex;
        t.lineNumber = lineNum;
        lex = "";
        break;
      }
      if(lex == "+"){
        t.token = getTokenType(lex);
        t.lexeme = lex;
        t.lineNumber = lineNum;
        lex = "";
        break;
      }
      //case for negative numbers
      if(lex == "-" && getTokenType(peek) == "LITERAL"){
        c = is.get();
        cn = charToStr(c); 

        while(getTokenType(cn) == "LITERAL"){
          lex += cn;
          c = is.get();
          cn = charToStr(c);

        }
        t.token = getTokenType(lex);
        t.lexeme = lex;
        t.lineNumber = lineNum;
        lex = "";
        break;

        p = is.peek();
        peek = charToStr(p);
      }
      //TODO These two if `cases should be combined
      if(lex == "-"){
        t.token = getTokenType(lex);
        t.lexeme = lex;
        t.lineNumber = lineNum;
        lex = "";
        break;
      }
      if(lex == "/"){
        t.token = getTokenType(lex);
        t.lexeme = lex;
        t.lineNumber = lineNum;
        lex = "";
        break;
      }
      if(lex == "*"){
        t.token = getTokenType(lex);
        t.lexeme = lex;
        t.lineNumber = lineNum;
        lex = "";
        break;
      }
      //double operators
      if(lex == "<" && peek == "-"){//lex == "<" && peek == "-"){
        c = is.get(); // c = "-"
        lex += c; // lex = "<-"
        t.token = getTokenType(lex);
        t.lexeme = lex;
        t.lineNumber = lineNum;
        lex = "";
        break;
      }
      if(lex == "<" && (getTokenType(peek) == "IDENT"  || getTokenType(peek) == "LITERAL" || peek == " ") ){
        t.token = getTokenType(lex);
        t.lexeme = lex;
        t.lineNumber = lineNum;
        lex = "";
        break;
      }
      if(lex == ">" && (getTokenType(peek) == "IDENT"  || getTokenType(peek) == "LITERAL" || peek == " ") ){
        t.token = getTokenType(lex);
        t.lexeme = lex;
        t.lineNumber = lineNum;
        lex = "";
        break;
      }
      if(lex == "<" && peek == "="){
        c = is.get();
        lex += c;
        t.token = getTokenType(lex);
        t.lexeme = lex;
        t.lineNumber = lineNum;
        lex = "";
        break;
      }
      if(lex == ">" && peek == "="){
        c = is.get();
        lex += c;
        t.token = getTokenType(lex);
        t.lexeme = lex;
        t.lineNumber = lineNum;
        lex = "";
        break;
      }
      if(lex == "!" && peek == "="){
        c = is.get();
        lex += c;
        t.token = getTokenType(lex);
        t.lexeme = lex;
        t.lineNumber = lineNum;
        lex = "";
        break;
      }
      if(lex == "!" && peek == "="){
        c = is.get();
        lex += c;
        t.token = getTokenType(lex);
        t.lexeme = lex;
        t.lineNumber = lineNum;
        lex = "";
        break;
      }
      if( lex == "\n"){
        t.token = getTokenType(lex);
        t.lexeme = lex;
        t.lineNumber = lineNum;
        lineNum++;
        lex = "";
        break;
      }
      if( (lex == "while" && peek == "") ||
          (lex == "endwhile" && peek == "") ||
          (lex == "fun" && (peek == "(" || peek == "")) ||
          (lex == "endfun" && peek == "") ||
          (lex == "as" && peek == "") ||
          (lex == "and" && peek == "") ||
          (lex == "or" && peek == "") ||
          (lex == "toss" && peek == "") ||
          (lex == "take" && peek == "") ||
          (lex == "not" && (peek == "(" || peek == "")) ||
          (lex == "in" && peek == "") ||
	  (lex == "big" && peek == "") ||
	  (lex == "small" && peek == "") ||
          (lex == "boo" && peek == "") ||
          (lex == "mod" && peek == "") ||
          (lex == "if" && (peek == "" || peek == "(")) ||
          (lex == "elf" && (peek == "" || peek == "(")) ||
          (lex == "else" && peek == "") ||
          (lex == "endif" && peek == "") ||
          (lex == "give" && peek == "") ){

        t.token = getTokenType(lex);
        t.lexeme = lex;
        t.lineNumber = lineNum;
        lex = "";
        break;
      }
      if(peek == ""){
        t.token = getTokenType(lex);
        t.lexeme = lex;
        t.lineNumber = lineNum;
        lex = "";
        break;
      }
      if( getTokenType(lex) == "INVALID"){
        std::cout << "invalid tokent:" << lex << "\n";
        break;
      }

      c = is.get();
      cn = charToStr(c);

      p = is.peek();
      peek = charToStr(p);
    }
    if (cn != "" and cn != " ")
      qlist.push(t);
  }

  is.close();
  while (!qlist.empty())
  {
    std::cout << "Lexeme: " << qlist.front().lexeme << "\n" << "Token: " << qlist.front().token << "\n";
    qlist.pop();
  }
}
