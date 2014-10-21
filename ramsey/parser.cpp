#include <iostream>
#include <queue>
#include<stack>
using namespace std;

string peek(queue<token> q)
{
	tokenObject _t = q.front();
	return _t.token;
}

void match(stack<token> s, queue<token> q, tokenObject _t)
{
		s.push(_t);
		q.pop();
}

void literal(stack<token> s, queue<token> q)
{
	if(peek(q) == "LITERAL")
		match(s,q,q.front());
}

void ident(stack<token> s, queue<token> q)
{
	if(peek(q) == "IDENT")
		match(s,q,q.front());
}

void boolop(stack<token> s, queue<token> q)
{
	if(peek(q) == "COMPOP")
		match(s,q,q.front());
}

void op(stack<token> s, queue<token> q)
{
	if(peek(q) == "PLUS" || peek(q) == "MINUS" || peek(q) == "DIV" || peek(q) == "MUL" || peek(q) == "MOD")
		match(s,q,q.front());
}

void type(stack<token> s, queue<token> q)
{
	if(peek(q) == "BOO" || peek(q) == "IN" || peek(q) == "SMALL" || peek(q) == "BIG")
		match(s,q,q.front());
}

void boolexpC(stack<token> s, queue<token> q)
{
	if(peek(q) == "IDENT")
		ident(s,q);
	else if(peek(q) == "LITERAL")
		literal(s,q);
}

void boolexpB(stack<token> s, queue<token> q)
{
	if()
}

void boolexpA(stack<token> s, queue<token> q)
{
	if(peek(q) == "AND"){
		match(s,q,q.front());
		boolexp(s,q);
	}
	
	else if(peek(q) == "OR"){
		match(s,q,q.front());
		boolexp(s,q);
	}
	else
		ERROR
}

void boolexp(stack<token> s, queue<token> q)
{
	if(peek(q) == "AND" || peek(q) == "OR")
		boolexpA(s,q);
	else if(peek(q) == "NOT"){
		match(s,q,q.front());
		boolexp(s,q);
	}
	else if(peek(q) == "LPAREN"){
		match(s,q,q.front());
		boolexp(s,q);
	}
	else if(peek(q) == "IDENT"){
		ident(s,q);
		boolop(s,q);
		boolexpB(s,q);
	}
	else if(peek(q) == "LITERAL"){
		literal(s,q);
		boolop(s,q);
		boolexpC(s,q);
	}
	else
		ERROR
}

void exprB(stack<token> s, queue<token> q)
{
	if(peek(q) == "LPAREN"){
		match(s,q,q.front());
		expr(s,q);
	}
	else
		ERROR
}

void exprA(stack<token> s, queue<token> q)
{
	if(peek(q) == "IDENT")
		ident(s,q);
	else if(peek(q) == "LITERAL")
		literal(s,q);
	else if(peek(q)  == "LPAREN")
		expr(s,q);
	else if(peek(q) == "CHOP"){
		match(s,q,q.front());
		match(s,q,q.front());
		expr(s,q);
	}
	else
		ERROR
}

void exprTail(stack<token> s, queue<token> q)
{
	if(peek(q) == "PLUS" || peek(q) == "MINUS" || peek(q) == "DIV" || peek(q) == "MUL" || peek(q) == "MOD")
	{
		op(s,q);
		exprA(s,q);
	}
	else if(peek(q) == "RPAREN" || peek(q) == "EOL")
		return;
	else
		ERROR
}

void expr(stack<token> s, queue<token> q)
{
	if(peek(q) == "IDENT" || peek(q) == "LITERAL" || peek(q) == "LPAREN" || peek(q) == "CHOP")
	{
		exprA(s,q);
		exprTail(s,q);
	}
	else
		ERROR
}

void param(stack<token> s, queue<token> q)
{	
	if(peek(q) == "BOO" || peek(q) == "IN" || peek(q) == "SMALL" || peek(q) == "BIG")
	{
		type(s,q);
		ident(s,q);
	}
	else
		ERROR
}

void paramsA(stack<token> s, queue<token> q)
{
	if(peek(q) == "COMMA"){
		match(s,q,q.front());
		params(s,q);
	}
	else if(peek(q) == "RPAREN")
		return;
	else
		ERROR
}

void params(stack<token> s, queue<token> q)
{
	if(peek(q) == "BOO" || peek(q) == "IN" || peek(q) == "SMALL" || peek(q) == "BIG")
	{
		param(s,q);
		paramsA(s,q);
	}
	else
		ERROR
}

void opt_params(stack<token> s, queue<token> q)
{
	if(peek(q) == "BOO" || peek(q) == "IN" || peek(q) == "SMALL" || peek(q) == "BIG")
		params(s,q);
	else if(peek(q) == "RPAREN")
		return;
	else
		ERROR
}

void fun_stmts(stack<token> s, queue<token> q)
{
	if(peek(q) == "IF" || peek(q) == "WHILE" || peek(q) == "BOO" || peek(q) == "IN" || peek(q) == "SMALL" || peek(q) == "BIG" || peek(q) == "IDENT" || peek(q) == "LITERAL" || peek(q) == "LPAREN" || peek(q) == "CHOP")
		stmts(s,q);
	else if(peek(q) == "TOSS"){
		match(s,q,q.front());
		expr(s,q);
	}
	else if(peek(q) == "EOL")
		return;
	else
		ERROR
}

void optional_stmts(stack<token> s, queue<token> q)
{
	if(peek(q) == "IF" || peek(q) == "WHILE" || peek(q) == "BOO" || peek(q) == "IN" || peek(q) == "SMALL" || peek(q) == "BIG" || peek(q) == "IDENT" || peek(q) == "LITERAL" || peek(q) == "LPAREN" || peek(q) == "CHOP")
		stmts(s,q);
	else if(peek(q) == "EOL")
		return;
	else
		ERROR
}

void elvesA(stack<token> s, queue<token> q)
{
	if(peek(q) == "ELF")
		elves(s,q);
	else if(peek(q) == "ENDIF" || peek(q) == "ELSE")
		return;
	else
		ERROR
}

void elves(stack<token> s, queue<token> q)
{
	if(peek(q) == "ELF")
	{
		match(s,q,q.front());
		match(s,q,q.front());
		boolexp(s,q);
		match(s,q,q.front());
		match(s,q,q.front());
		optional_stmts(s,q);
		match(s,q,q.front());
		elvesA(s,q);
	}
}

void stmtC(stack<token> s, queue<token> q)
{
	if(peek(q) == "ASSIGN"){
		match(s,q,q.front());
		expr(s,q);
	}
	else if(peek(q) == "EOL")
		return;
	else
		ERROR
}

void stmtB(stack<token> s, queue<token> q)
{
	if(peek(q) == "ENDIF")
		match(s,q,q.front());
	else if(peek(q) == "ELSE")
	{
		match(s,q,q.front());
		match(s,q,q.front());
		optional_stmts(s,q);
		match(s,q,q.front());
		match(s,q,q.front());
	}
}

void stmtA(stack<token> s, queue<token> q)
{
	if(peek(q) == "ENDIF")
		match(s,q,q.front());
	else if(peek(q) == "ELSE")
	{
		match(s,q,q.front());
		match(s,q,q.front());
		optional_stmts(s,q);
		match(s,q,q.front());
		match(s,q,q.front());
	}
	else if(peek(q) == "ELF")
	{
		elves(s,q);
		stmtB(s,q);
	}
}

void stmt(stack<token> s, queue<token> q)
{
	if(peek(q) == "IF")
	{
		match(s,q,q.front());
		match(s,q,q.front());
		boolexp(s,q);
		match(s,q,q.front());
		match(s,q,q.front());
		optional_stmts(s,q);
		match(s,q,q.front());
		stmtA(s,q);
	}
	else if(peek(q) == "WHILE")
	{
		match(s,q,q.front());
		match(s,q,q.front());
		boolexp(s,q);
		match(s,q,q.front());
		match(s,q,q.front());
		optional_stmts(s,q);
		match(s,q,q.front());
		match(s,q,q.front());
	}
	else if(peek(q) == "IDENT")
	{
		ident(s,q);
		match(s,q,q.front());
		expr(s,q);
	}
	else if(peek(q) == "BOO" || peek(q) == "IN" || peek(q) == "SMALL" || peek(q) == "BIG")
	{
		type(s,q);
		ident(s,q);
		stmtC(s,q);
	}
	else if(peek(q) == "IDENT" || peek(q) == "LITERAL" || peek(q) == "LPAREN" || peek(q) == "CHOP")
		expr(s,q);
}

void stmtX(stack<token> s, queue<token> q)
{
	if(peek(q) == "IF" || peek(q) == "WHILE" || peek(q) == "BOO" || peek(q) == "IN" || peek(q) == "SMALL" || peek(q) == "BIG" || peek(q) == "IDENT" || peek(q) == "LITERAL" || peek(q) == "LPAREN" || peek(q) == "CHOP")
		stmts(s,q);
	else if(peek(q) == "EOL")
		return;
}

void stmts(stack<token> s, queue<token> q)
{
	if(peek(q) == "IF" || peek(q) == "WHILE" || peek(q) == "BOO" || peek(q) == "IN" || peek(q) == "SMALL" || peek(q) == "BIG" || peek(q) == "IDENT" || peek(q) == "LITERAL" || peek(q) == "LPAREN" || peek(q) == "CHOP")
	{
		stmt(s,q);
		match(s,q,q.front());
		stmtX(s,q);
	}
}

void toplvlstmt(stack<token> s, queue<token> q)
{
	if(peek(q) == "FUN")
	{
		match(s,q,q.front());
		ident(s,q);
		match(s,q,q.front());
		opt_params(s,q);
		match(s,q,q.front());
		match(s,q,q.front());
		type(s,q);
		match(s,q,q.front());
		fun_stmts(s,q);
		match(s,q,q.front());
		match(s,q,q.front());
		expr(s,q);
		match(s,q,q.front());
		match(s,q,q.front());
	}
	else if(peek(q) == "IF" || peek(q) == "WHILE" || peek(q) == "BOO" || peek(q) == "IN" || peek(q) == "SMALL" || peek(q) == "BIG" || peek(q) == "IDENT" || peek(q) == "LITERAL" || peek(q) == "LPAREN" || peek(q) == "CHOP")
		stmts(s,q);
}

void toplvlstmtsA(stack<token> s, queue<token> q)
{
	if(peek(q) == "IF" || peek(q) == "WHILE" || peek(q) == "BOO" || peek(q) == "IN" || peek(q) == "SMALL" || peek(q) == "BIG" || peek(q) == "IDENT" || peek(q) == "LITERAL" || peek(q) == "LPAREN" || peek(q) == "CHOP" || peek(q) == "FUN" || peek(q) == "EOL")
		toplvlstmts(s,q);
	else if(peek(q) == "EOL")
		return;
}

void toplvlstmts(stack<token> s, queue<token> q)
{
	if(peek(q) == "IF" || peek(q) == "WHILE" || peek(q) == "BOO" || peek(q) == "IN" || peek(q) == "SMALL" || peek(q) == "BIG" || peek(q) == "IDENT" || peek(q) == "LITERAL" || peek(q) == "LPAREN" || peek(q) == "CHOP" || peek(q) == "FUN" || peek(q) == "EOL")
	{
		toplvlstmt(s,q);
		match(s,q,q.front());
		toplvlstmtsA(s,q);
	}
}

void program(stack<token> s, queue<token> q)
{
	if(peek(q) == "IF" || peek(q) == "WHILE" || peek(q) == "BOO" || peek(q) == "IN" || peek(q) == "SMALL" || peek(q) == "BIG" || peek(q) == "IDENT" || peek(q) == "LITERAL" || peek(q) == "LPAREN" || peek(q) == "CHOP" || peek(q) == "FUN" || peek(q) == "EOL")
	{
		toplvlstmts();
		match(s,q,q.front());
	}
}

int main(queue<token> q)
{
	stack<token> s;
	program(s,q);
	if(q.empty())
		cout << "Acceptable syntax" << endl;
	else
		cout << "Failure" << endl;
}