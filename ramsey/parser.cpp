#include <iostream>
#include <queue>
#include<stack>
using namespace std;

string peek(queue<token> q)
{
	tokenObject _t = q.front();
	return _t.token;
}

void match(stack<token> s, queue<token> q, tokenObject _t, string expected_value)
{
	if(expected_value == _t.token){
		s.push(_t);
		q.pop();
	}
	else
		ERROR
}

void numLit(stack<token> s, queue<token> q)
{
	if(peek(q) == "NUMLIT")
		match(s,q,q.front(),"NUMLIT");
}

void booLit(stack<token> s, queue<token> q)
{
	if(peek(q) == "BOOLIT")
		match(s,q,q.front(),"BOOLIT");
}

void ident(stack<token> s, queue<token> q)
{
	if(peek(q) == "IDENT")
		match(s,q,q.front(),"IDENT");
}

void boolop(stack<token> s, queue<token> q)
{
	if(peek(q) == "COMPOP")
		match(s,q,q.front(),"COMPOP");
}

void op(stack<token> s, queue<token> q)
{
	if(peek(q) == "NUMOP")
		match(s,q,q.front(),"NUMOP");
}

void type(stack<token> s, queue<token> q)
{
	if(peek(q) == "TYPE")
		match(s,q,q.front(),"TYPE");
}

void boolExprTailParen(stack<token> s, queue<token> q)
{
	if(peek(q) == "AND")
	{
		match(s,q,q.front(),"AND");
		boolexp(s,q);
		match(s,q,q.front(),"RPAREN");
		boolExprTail(s,q);
	}
	else if(peek(q) == "OR")
	{
		match(s,q,q.front(),"OR");
		boolexp(s,q);
		match(s,q,q.front(),"RPAREN");
		boolExprTail(s,q);
	}
	else if(peek(q) == "RPAREN")
	{
		match(s,q,q.front(),"RPAREN");
		boolExprTail(s,q);
	}
	else
		ERROR
}

void exprTailAParen(stack<token> s, queue<token> q)
{
	if(peek(q) == "COMPOP")
	{
		boolop(s,q);
		boolNumExprTail(s,q);
		match(s,q,q.front(),"RPAREN");
		boolExprTail(s,q);
	}
	else if(peek(q) == "NUMOP"){
		op(s,q);
		numExpr(s,q);
		match(s,q,q.front(),"RPAREN");
		exprTailA(s,q);
	}
	else
		ERROR
}

void exprTailBParen(stack<token> s, queue<token> q)
{
	if(peek(q) == "AND" || peek(q) == "OR" || peek(q) == "RPAREN")
	{
		boolExprTail(s,q);
		match(s,q,q.front(),"RPAREN");
		boolExprTail(s,q);
	}
	else if(peek(q) == "COMPOP"){
		boolop(s,q);
		boolNumExprTail(s,q);
		match(s,q,q.front(),"RPAREN");
		boolExprTail(s,q);
	}
	else if(peek(q) == "NUMOP"){
		op(s,q);
		numExp(s,q);
		match(s,q,q.front(),"RPAREN");
		exprTailA(s,q);
	}
	else
		ERROR
}

void parenExpr(stack<token> s, queue<token> q)
{
	if(peek(q) == "IDENT")
	{
		ident(s,q);
		exprTailBParen(s,q);
	}
	else if(peek(q) == "NUMLIT")
	{
		numLit(s,q);
		exprTailAParen(s,q);
	}
	else if(peek(q)== "LPAREN")
	{
		match(s,q,q.front(),"LPAREN");
		parenExpr(s,q);
		parenExpr(s,q);
	}
	else if(peek(q) == "CHOP")
	{
		match(s,q,q.front(),"CHOP");
		match(s,q,q.front(),"LPAREN");
		chopTail(s,q);
		match(s,q,q.front(),"RPAREN");
		exprTailAParen(s,q);
	}
	else if(peek(q) == "BOOLIT")
	{
		booLit(s,q);
		boolExprTailParen(s,q);
	}
	else if(peek(q) == "RPAREN")
	{
		match(s,q,q.front(),"RPAREN");
	}
	else
		ERROR
}

void numExprTail_w_op(stack<token> s, queue<token> q)
{
	if(peek(q) == "NUMOP")
	{
		op(s,q);
		numExpr(s,q);
	}
	else if(peek(q) == "COMPOP" || peek(q) == "RPAREN" || peek(q) == "EOL")
		return;
	else
		ERROR
}

void boolNumExprTail(stack<token> s, queue<token> q)
{
	if(peek(q) == "NUMLIT" || peek(q) == "IDENT" || peek(q) == "CHOP" || peek(q) == "LPAREN")
	{
		numExpr(s,q);
		boolExprTail(s,q);
	}
	else
		ERROR
}

void boolExprTail(stack<token> s, queue<token> q)
{
	if(peek(q) == "AND")
	{
		match(s,q,q.front(),"AND");
		boolexp(s,q);
	}
	else if(peek(q) == "OR")
	{
		match(s,q,q.front(),"OR");
		boolexp(s,q);
	}
	else if(peek(q) == "RPAREN" || peek(q) == "EOL")
		return;
	else
		ERROR
}

void numExpr(stack<token> s, queue<token> q)
{
	if(peek(q) == "NUMLIT")
	{
		numLit(s,q);
		numExprTail_w_op(s,q);
	}
	else if(peek(q) == "IDENT")
	{
		ident(s,q);
		numExprTail_w_op(s,q);
	}
	else if(peek(q) == "CHOP")
	{
		match(s,q,q.front(),"CHOP");
		match(s,q,q.front(), "LPAREN");
		chopTail(s,q);
		match(s,q,q.front(), "RPAREN");
		numExprTail_w_op(s,q);
	}
	else if(peek(q) == "LPAREN")
	{
		match(s,q,q.front(), "LPAREN");
		numExpr(s,q);
		match(s,q,q.front(), "RPAREN");
		numExprTail_w_op(s,q);
	}
	else
		ERROR
}

void evalToBoolFollow(stack<token> s, queue<token> q)
{
	if(peek(q) == "NUMOP" || peek(q) == "COMPOP")
	{
		numExprTail_w_op(s,q);
		boolop(s,q);
		boolNumExprTail(s,q);
	}
	else
		ERROR
}

void identFollow(stack<token> s, queue<token> q)
{
	if(peek(q) == "AND" || peek(q) == "OR" || peek(q) == "RPAREN" || peek(q) == "EOL")
	{
		boolExprTail(s,q);
	}
	else if(peek(q) == "COMPOP" || peek(q) == "NUMOP" || peek(q) == "EOL")
	{
		evalToBoolFollow(s,q);
	}
}

void boolexp(stack<token> s, queue<token> q)
{
	if(peek(q) == "BOOLIT"){
		boolLit(s,q);
		boolExprTail(s,q);
	}
	else if(peek(q) == "NOT"){
		match(s,q,q.front(),"NOT");
		boolexp(s,q);
	}
	else if(peek(q) == "LPAREN"){
		match(s,q,q.front(),"LPAREN");
		boolexp(s,q);
		match(s,q,q.front(),"RPAREN");
		boolExprTail(s,q);
	}
	else if(peek(q) == "IDENT"){
		ident(s,q);
		identFollow(s,q);
	}
	else if(peek(q) == "NUMLIT"){
		numLit(s,q);
		evalToBoolFollow(s,q);
	}
	else
		ERROR
}

void exprTailB(stack<token> s, queue<token> q)
{
	if(peek(q) == "AND" || peek(q) == "OR" || peek(q) == "RPAREN")
	{
		boolExprTail(s,q);
	}
	else if(peek(q) == "COMPOP")
	{
		boolop(s,q);
		boolNumExprTail(s,q);
	}
	else if(peek(q) == "NUMOP")
	{
		op(s,q);
		numExpr(s,q);
	}
	else
		ERROR
}

void exprTailA(stack<token> s, queue<token> q)
{
	if(peek(q) == "COMPOP"){
		boolop(s,q);
		boolNumExprTail(s,q);
	}
	else if(peek(q) == "NUMOP"){
		op(s,q);
		numExpr(s,q);
	}
	else if(peek(q)  == "RPAREN" || peek(q) == "EOL")
		return;
	else
		ERROR
}

void chopTail(stack<token> s, queue<token> q)
{
	if(peek(q) == "NUMLIT")
	{
		numLit(s,q);
		numExprTail_w_op(s,q);
	}
	else if(peek(q) == "IDENT")
	{
		ident(s,q);
		numExprTail_w_op(s,q);
	}
	else
		ERROR
}

void expr(stack<token> s, queue<token> q)
{
	if(peek(q) == "IDENT")
	{
		ident(s,q);
		exprTailB(s,q);
	}
	else if(peek(q) == "NUMLIT")
	{
		numLit(s,q);
		exprTailA(s,q);
	}
	else if(peek(q) == "BOOLIT")
	{
		booLit(s,q);
		boolExprTail(s,q);
	}
	else if(peek(q) == "LPAREN")
	{
		match(s,q,q.front(),"LPAREN");
		parenexpr(s,q);
	}
	else if(peek(q) == "CHOP")
	{
		match(s,q,q.front(),"CHOP");
		match(s,q,q.front(),"LPAREN");
		chopTail(s,q);
		match(s,q,q.front(),"RPAREN");
		exprTailA(s,q);
	}
	else
		ERROR
}

void param(stack<token> s, queue<token> q)
{
	if(peek(q) == "TYPE")
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
		match(s,q,q.front(),"COMMA");
		params(s,q);
	}
	else if(peek(q) == "RPAREN")
		return;
	else
		ERROR
}

void params(stack<token> s, queue<token> q)
{
	if(peek(q) == "TYPE")
	{
		param(s,q);
		paramsA(s,q);
	}
	else
		ERROR
}

void opt_params(stack<token> s, queue<token> q)
{
	if(peek(q) == "TYPE")
		params(s,q);
	else if(peek(q) == "RPAREN")
		return;
	else
		ERROR
}

void fun_stmts(stack<token> s, queue<token> q)
{
	if(peek(q) == "IF" || peek(q) == "WHILE" || peek(q) == "TYPE" || peek(q) == "IDENT" || peek(q) == "NUMLIT" || peek(q) == "LPAREN" || peek(q) == "CHOP")
		stmts(s,q);
	else if(peek(q) == "TOSS"){
		match(s,q,q.front(),"TOSS");
		expr(s,q);
	}
	else if(peek(q) == "EOL")
		return;
	else
		ERROR
}

void optional_stmts(stack<token> s, queue<token> q)
{
	if(peek(q) == "IF" || peek(q) == "WHILE" || peek(q) == "TYPE" || peek(q) == "IDENT" || peek(q) == "NUMLIT" || peek(q) == "LPAREN" || peek(q) == "CHOP")
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
		match(s,q,q.front(),"ELF");
		match(s,q,q.front(),"LPAREN");
		boolexp(s,q);
		match(s,q,q.front(),"RPAREN");
		match(s,q,q.front(),"EOL");
		optional_stmts(s,q);
		match(s,q,q.front(), "EOL");
		elvesA(s,q);
	}
	else
		ERROR
}

void stmtC(stack<token> s, queue<token> q)
{
	if(peek(q) == "ASSIGN"){
		match(s,q,q.front(),"ASSIGN");
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
		match(s,q,q.front(),"ENDIF");
	else if(peek(q) == "ELSE")
	{
		match(s,q,q.front(),"ELSE");
		match(s,q,q.front(),"EOL");
		optional_stmts(s,q);
		match(s,q,q.front(),"EOL");
		match(s,q,q.front(),"ENDIF");
	}
	else
		ERROR
}

void stmtA(stack<token> s, queue<token> q)
{
	if(peek(q) == "ENDIF")
		match(s,q,q.front(),"ENDIF");
	else if(peek(q) == "ELSE")
	{
		match(s,q,q.front(),"ELSE");
		match(s,q,q.front(),"EOL");
		optional_stmts(s,q);
		match(s,q,q.front(),"EOL");
		match(s,q,q.front(),"ENDIF");
	}
	else if(peek(q) == "ELF")
	{
		elves(s,q);
		stmtB(s,q);
	}
	else
		ERROR
}

void stmt(stack<token> s, queue<token> q)
{
	if(peek(q) == "IF")
	{
		match(s,q,q.front(),"IF");
		match(s,q,q.front(),"LPAREN");
		boolexp(s,q);
		match(s,q,q.front(),"RPAREN");
		match(s,q,q.front(),"EOL");
		optional_stmts(s,q);
		match(s,q,q.front(),"EOL");
		stmtA(s,q);
	}
	else if(peek(q) == "WHILE")
	{
		match(s,q,q.front(),"WHILE");
		match(s,q,q.front(),"LPAREN");
		boolexp(s,q);
		match(s,q,q.front(),"RPAREN");
		match(s,q,q.front(),"EOL");
		optional_stmts(s,q);
		match(s,q,q.front(),"EOL");
		match(s,q,q.front(),"ENDWHILE");
	}
	else if(peek(q) == "IDENT")
	{
		ident(s,q);
		identTail(s,q);
	}
	else if(peek(q) == "TYPE")
	{
		type(s,q);
		ident(s,q);
		stmtC(s,q);
	}
	else if(peek(q) == "IDENT" || peek(q) == "NUMLIT" || peek(q) == "LPAREN" || peek(q) == "CHOP")
		expr(s,q);
	else
		ERROR
}

void stmtX(stack<token> s, queue<token> q)
{
	if(peek(q) == "IF" || peek(q) == "WHILE" || peek(q) == "TYPE" || peek(q) == "IDENT" || peek(q) == "NUMLIT" || peek(q) == "LPAREN" || peek(q) == "CHOP")
		stmts(s,q);
	else if(peek(q) == "EOL")
		return;
	else
		ERROR
}

void stmts(stack<token> s, queue<token> q)
{
	if(peek(q) == "IF" || peek(q) == "WHILE" || peek(q) == "TYPE" || peek(q) == "IDENT" || peek(q) == "NUMLIT" || peek(q) == "LPAREN" || peek(q) == "CHOP")
	{
		stmt(s,q);
		match(s,q,q.front(),"EOL");
		stmtX(s,q);
	}
	else
		ERROR
}

void toplvlstmt(stack<token> s, queue<token> q)
{
	if(peek(q) == "FUN")
	{
		match(s,q,q.front(),"FUN");
		ident(s,q);
		match(s,q,q.front(),"LPAREN");
		opt_params(s,q);
		match(s,q,q.front(),"RPAREN");
		match(s,q,q.front(),"AS");
		type(s,q);
		match(s,q,q.front(),"EOL");
		fun_stmts(s,q);
		match(s,q,q.front(),"EOL");
		match(s,q,q.front(),"TOSS");
		expr(s,q);
		match(s,q,q.front(),"EOL");
		match(s,q,q.front(),"ENDFUN");
	}
	else if(peek(q) == "IF" || peek(q) == "WHILE" || peek(q) == "TYPE" || peek(q) == "IDENT" || peek(q) == "NUMLIT" || peek(q) == "LPAREN" || peek(q) == "CHOP")
		stmts(s,q);
	else
		ERROR
}

void toplvlstmtsA(stack<token> s, queue<token> q)
{
	if(peek(q) == "IF" || peek(q) == "WHILE" || peek(q) == "TYPE" || peek(q) == "IDENT" || peek(q) == "NUMLIT" || peek(q) == "LPAREN" || peek(q) == "CHOP" || peek(q) == "FUN" || peek(q) == "EOL")
		toplvlstmts(s,q);
	else if(peek(q) == "EOL")
		return;
	else
		ERROR
}

void toplvlstmts(stack<token> s, queue<token> q)
{
	if(peek(q) == "IF" || peek(q) == "WHILE" || peek(q) == "TYPE" || peek(q) == "IDENT" || peek(q) == "NUMLIT" || peek(q) == "LPAREN" || peek(q) == "CHOP" || peek(q) == "FUN" || peek(q) == "EOL")
	{
		toplvlstmt(s,q);
		match(s,q,q.front(),"EOL");
		toplvlstmtsA(s,q);
	}
	else
		ERROR
}

void program(stack<token> s, queue<token> q)
{
	if(peek(q) == "IF" || peek(q) == "WHILE" || peek(q) == "BOO" || peek(q) == "TYPE" || peek(q) == "IDENT" || peek(q) == "NUMLIT" || peek(q) == "LPAREN" || peek(q) == "CHOP" || peek(q) == "FUN" || peek(q) == "EOL")
	{
		toplvlstmts();
	}
	else
		ERROR
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
