#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>
#include <queue>
#include "lexi.h"
#include "tokenizer.h"
#include "parser.h"

int main (int argc, char *argv[]) {

	//allows compiled program to accept a source file via command line
	std::string source = argv[1];

	// std::string filename = source;

	//need to rewrite the preproceesor
	std::string filename = preprocessor(source);

	std::ifstream is(filename);

	std::string lex = "";
	int lineNum = 1;

	tokenObject t;
	std::queue<tokenObject> qlist;

	while (is.good())
	{
		char c = is.get();
		std::string cn = charToStr(c);

		char p = is.peek();
		std::string peek = charToStr(p);

		while(is.good()){

			if(c == '\n'  ||  getTokenType(cn) == "EOL" || getTokenType(peek) == "EOL" ){
				lineNum++;
				t.token = "EOL";
				t.lexeme = '\n';
				t.lineNumber = lineNum;
				lex = "";
				qlist.push(t);
				break;
			}
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
			if( peek == "(" || peek == ")" || peek == "+" || peek == "*" || peek == "/" || peek == "," || ((getTokenType(lex) == "IDENT" || getTokenType(lex) == "PLUS" || getTokenType(lex) == "MINUS" || getTokenType(lex) == "DIV" || getTokenType(lex) == "MUL" || getTokenType(lex) == "RPAREN") && peek == "-")){
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
			if(lex == ","){
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
			//TODO These two if cases should be combined
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
			if( (lex == "while" && peek == "") || (lex == "endwhile" && peek == "") || (lex == "fun" && (peek == "(" || peek == "")) || (lex == "endfun" && peek == "") || (lex == "as" && peek == "") || (lex == "and" && peek == "") || (lex == "or" && peek == "") || (lex == "toss" && peek == "") || (lex == "take" && peek == "") || (lex == "not" && (peek == "(" || peek == "")) || (lex == "big" && peek == "") || (lex == "small" && peek == "") || (lex == "boo" && peek == "") || (lex == "mod" && peek == "") || (lex == "if" && (peek == "" || peek == "(")) || (lex == "elf" && (peek == "" || peek == "(")) || (lex == "else" && peek == "") || (lex == "endif" && peek == "") || (lex == "give" && peek == "") || (lex == "chop" && peek == "") ){
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
	stack<tokenObject> s;
	
	// while (!qlist.empty()){
	// 		std::cout << qlist.front().token << "\n";
	// 		qlist.pop();
	// }


	int flag = 0;
	program(s,qlist,flag);
	if(qlist.empty() && flag == 0)
		cout << "Acceptable syntax" << endl;
	else{
		cout << "Failure" << endl;
		cout << qlist.front().token << endl;
	}
}
