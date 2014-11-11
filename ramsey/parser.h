#include <iostream>
#include <queue>
#include <stack>
using namespace std;

string peek(queue<tokenObject> & q)
{
	tokenObject _t = q.front();
	return _t.token;
}

void match(stack<tokenObject> s, queue<tokenObject> & q, tokenObject _t, string expected_value, int & flag)
{
	if(expected_value == _t.token){
		cout << "MATCHED TOKEN: " << _t.token << endl; //token
		s.push(_t);
		q.pop();
		cout << "NEXT TOKEN: " << q.front().token << endl; //token



	}
	else{
		cout << "Invalid Token matching on line" << _t.lineNumber << endl;
		cout << "*Invalid Token *" << _t.token << endl;
		flag = 1;
	}
}

void numLit(stack<tokenObject> s, queue<tokenObject> & q, int & flag)
{
	if(peek(q) == "NUMLIT")
		match(s,q,q.front(),"NUMLIT",flag);
}

void booLit(stack<tokenObject> s, queue<tokenObject> & q, int & flag)
{
	if(peek(q) == "BOOLIT")
		match(s,q,q.front(),"BOOLIT",flag);
}

void ident(stack<tokenObject> s, queue<tokenObject> & q, int & flag)
{
	cout << "Entering ident " << endl;
	if(peek(q) == "IDENT")
		match(s,q,q.front(),"IDENT",flag);
}

void boolop(stack<tokenObject> s, queue<tokenObject> & q, int & flag)
{
	cout << "Entering boolop " << endl;
	if(peek(q) == "COMPOP")
		match(s,q,q.front(),"COMPOP",flag);
}

void op(stack<tokenObject> s, queue<tokenObject> & q, int & flag)
{
	cout << "Entering op " << endl;
	if(peek(q) == "NUMOP")
		match(s,q,q.front(),"NUMOP",flag);
}

void type(stack<tokenObject> s, queue<tokenObject> & q, int & flag)
{
	cout << "Entering type " << endl;

	if(peek(q) == "TYPE")
		match(s,q,q.front(),"TYPE",flag);
}

void boolexp(stack<tokenObject> s, queue<tokenObject> & q, int & flag);

void boolExprTailParen(stack<tokenObject> s, queue<tokenObject> & q, int & flag);

void exprTailAParen(stack<tokenObject> s, queue<tokenObject> & q, int & flag);

void exprTailBParen(stack<tokenObject> s, queue<tokenObject> & q, int & flag);

void parenExpr(stack<tokenObject> s, queue<tokenObject> & q, int & flag);

void boolexp(stack<tokenObject> s, queue<tokenObject> & q, int & flag);

void boolExprTailParen(stack<tokenObject> s, queue<tokenObject> & q, int & flag);

void exprTailAParen(stack<tokenObject> s, queue<tokenObject> & q, int & flag);

void exprTailBParen(stack<tokenObject> s, queue<tokenObject> & q, int & flag);

void parenExpr(stack<tokenObject> s, queue<tokenObject> & q, int & flag);

void numExprTail_w_op(stack<tokenObject> s, queue<tokenObject> & q, int & flag);

void boolNumExprTail(stack<tokenObject> s, queue<tokenObject> & q, int & flag);

void boolExprTail(stack<tokenObject> s, queue<tokenObject> & q, int & flag);

void numExpr(stack<tokenObject> s, queue<tokenObject> & q, int & flag);

void evalToBoolFollow(stack<tokenObject> s, queue<tokenObject> & q, int & flag);

void identFollow(stack<tokenObject> s, queue<tokenObject> & q, int & flag);

void exprTailB(stack<tokenObject> s, queue<tokenObject> & q, int & flag);

void exprTailA(stack<tokenObject> s, queue<tokenObject> & q, int & flag);

void chopTail(stack<tokenObject> s, queue<tokenObject> & q, int & flag);

void expr(stack<tokenObject> s, queue<tokenObject> & q, int & flag);

void param(stack<tokenObject> s, queue<tokenObject> & q, int & flag);

void paramsA(stack<tokenObject> s, queue<tokenObject> & q, int & flag);

void params(stack<tokenObject> s, queue<tokenObject> & q, int & flag);

void opt_params(stack<tokenObject> s, queue<tokenObject> & q, int & flag);

void fun_stmts(stack<tokenObject> s, queue<tokenObject> & q, int & flag);

void optional_stmts(stack<tokenObject> s, queue<tokenObject> & q, int & flag);

void elvesA(stack<tokenObject> s, queue<tokenObject> & q, int & flag);

void elves(stack<tokenObject> s, queue<tokenObject> & q, int & flag);

void stmtC(stack<tokenObject> s, queue<tokenObject> & q, int & flag);

void stmtB(stack<tokenObject> s, queue<tokenObject> & q, int & flag);

void stmtA(stack<tokenObject> s, queue<tokenObject> & q, int & flag);

void stmt(stack<tokenObject> s, queue<tokenObject> & q, int & flag);

void stmtX(stack<tokenObject> s, queue<tokenObject> & q, int & flag);

void stmts(stack<tokenObject> s, queue<tokenObject> & q, int & flag);

void toplvlstmt(stack<tokenObject> s, queue<tokenObject> & q, int & flag);

void toplvlstmtsA(stack<tokenObject> s, queue<tokenObject> & q, int & flag);

void toplvlstmts(stack<tokenObject> s, queue<tokenObject> & q, int & flag);

void program(stack<tokenObject> s, queue<tokenObject> & q, int & flag);

void boolexp(stack<tokenObject> s, queue<tokenObject> & q, int & flag)
{
	cout << "Entering Function boolexp" << endl;
	if(peek(q) == "BOOLIT"){
		booLit(s,q,flag);
		boolExprTail(s,q,flag);
	}
	else if(peek(q) == "NOT"){
		match(s,q,q.front(),"NOT",flag);
		boolexp(s,q,flag);
	}
	else if(peek(q) == "LPAREN"){
		match(s,q,q.front(),"LPAREN",flag);
		boolexp(s,q,flag);
		match(s,q,q.front(),"RPAREN",flag);
		boolExprTail(s,q,flag);
	}
	else if(peek(q) == "IDENT"){
		ident(s,q,flag);
		identFollow(s,q,flag);
	}
	else if(peek(q) == "NUMLIT"){
		numLit(s,q,flag);
		evalToBoolFollow(s,q,flag);
	}
	else
	{
		cout << "Error in boolean expression on line " << q.front().lineNumber << endl;
		flag =1;
	}
}

void boolExprTailParen(stack<tokenObject> s, queue<tokenObject> & q, int & flag)
{
	cout << "Entering Function boolExprTailParen" << endl;
	if(peek(q) == "AND")
	{
		match(s,q,q.front(),"AND",flag);
		boolexp(s,q,flag);
		match(s,q,q.front(),"RPAREN",flag);
		boolExprTail(s,q,flag);
	}
	else if(peek(q) == "OR")
	{
		match(s,q,q.front(),"OR",flag);
		boolexp(s,q,flag);
		match(s,q,q.front(),"RPAREN",flag);
		boolExprTail(s,q,flag);
	}
	else if(peek(q) == "RPAREN")
	{
		match(s,q,q.front(),"RPAREN",flag);
		boolExprTail(s,q,flag);
	}
	else
	{
		cout << "Error on line " << q.front().lineNumber << endl;
		flag = 1;
	}
}

void exprTailAParen(stack<tokenObject> s, queue<tokenObject> & q, int & flag)
{
	cout << "Entering Function exprTailAParen" << endl;
	if(peek(q) == "COMPOP")
	{
		boolop(s,q,flag);
		boolNumExprTail(s,q,flag);
		match(s,q,q.front(),"RPAREN",flag);
		boolExprTail(s,q,flag);
	}
	else if(peek(q) == "NUMOP"){
		op(s,q,flag);
		numExpr(s,q,flag);
		match(s,q,q.front(),"RPAREN",flag);
		exprTailA(s,q,flag);
	}
	else
	{
		cout << "Error on line " << q.front().lineNumber << endl;
		flag = 1;
	}
}

void exprTailBParen(stack<tokenObject> s, queue<tokenObject> & q, int & flag)
{
	cout << "Entering Function exprTailBParen" << endl;
	if(peek(q) == "AND" || peek(q) == "OR" || peek(q) == "RPAREN")
	{
		boolExprTail(s,q,flag);
		match(s,q,q.front(),"RPAREN",flag);
		boolExprTail(s,q,flag);
	}
	else if(peek(q) == "COMPOP"){
		boolop(s,q,flag);
		boolNumExprTail(s,q,flag);
		match(s,q,q.front(),"RPAREN",flag);
		boolExprTail(s,q,flag);
	}
	else if(peek(q) == "NUMOP"){
		op(s,q,flag);
		numExpr(s,q,flag);
		match(s,q,q.front(),"RPAREN",flag);
		exprTailA(s,q,flag);
	}
	else
	{
		cout << "Error on line " << q.front().lineNumber << endl;
		flag = 1;
	}
}

void parenExpr(stack<tokenObject> s, queue<tokenObject> & q, int & flag)
{
	cout << "Entering Function parenExpr" << endl;
	if(peek(q) == "IDENT")
	{
		ident(s,q,flag);
		exprTailBParen(s,q,flag);
	}
	else if(peek(q) == "NUMLIT")
	{
		numLit(s,q,flag);
		exprTailAParen(s,q,flag);
	}
	else if(peek(q)== "LPAREN")
	{
		match(s,q,q.front(),"LPAREN",flag);
		parenExpr(s,q,flag);
		parenExpr(s,q,flag);
	}
	else if(peek(q) == "CHOP")
	{
		match(s,q,q.front(),"CHOP",flag);
		match(s,q,q.front(),"LPAREN",flag);
		chopTail(s,q,flag);
		match(s,q,q.front(),"RPAREN",flag);
		exprTailAParen(s,q,flag);
	}
	else if(peek(q) == "BOOLIT")
	{
		booLit(s,q,flag);
		boolExprTailParen(s,q,flag);
	}
	else if(peek(q) == "RPAREN")
	{
		match(s,q,q.front(),"RPAREN",flag);
	}
	else
	{
		cout << "Error on line " << q.front().lineNumber << endl;
		flag = 1;
	}
}

void numExprTail_w_op(stack<tokenObject> s, queue<tokenObject> & q, int & flag)
{
	cout << "Entering Function numExprTail_w_op" << endl;
	cout << "----------" << peek(q) << endl;
	if(peek(q) == "NUMOP")
	{
		op(s,q,flag);
		numExpr(s,q,flag);
	}
	else if(peek(q) == "COMPOP" || peek(q) == "LPAREN" || peek(q) == "RPAREN" || peek(q) == "EOL")
		return;
}

void boolNumExprTail(stack<tokenObject> s, queue<tokenObject> & q, int & flag)
{
	cout << "Entering Function boolNumExprTail" << endl;
	if(peek(q) == "NUMLIT" || peek(q) == "IDENT" || peek(q) == "CHOP" || peek(q) == "LPAREN")
	{
		numExpr(s,q,flag);
		boolExprTail(s,q,flag);
	}
	else
	{
		cout << "Error on line " << q.front().lineNumber << endl;
		flag = 1;
	}
}

void boolExprTail(stack<tokenObject> s, queue<tokenObject> & q, int & flag)
{
	cout << "Entering Function boolExprTail" << endl;
	if(peek(q) == "AND")
	{
		match(s,q,q.front(),"AND",flag);
		boolexp(s,q,flag);
	}
	else if(peek(q) == "OR")
	{
		match(s,q,q.front(),"OR",flag);
		boolexp(s,q,flag);
	}
	else if(peek(q) == "EOL")
	{
		match(s,q,q.front(),"EOL",flag);
		return;
	}
	else if(peek(q) == "RPAREN" || peek(q) == "IDENT" || peek(q) == "NUMLIT" || peek(q) == "LPAREN" || peek(q) == "BOOLIT" || peek(q) == "CHOP")
		return;
	else if(peek(q) == "RPAREN" || peek(q) == "LPAREN")
		return;
}

void numExpr(stack<tokenObject> s, queue<tokenObject> & q, int & flag)
{
	cout << "Entering Function numExpr" << endl;
	if(peek(q) == "NUMLIT")
	{
		numLit(s,q,flag);
		numExprTail_w_op(s,q,flag);
	}
	else if(peek(q) == "IDENT")
	{
		ident(s,q,flag);
		numExprTail_w_op(s,q,flag);
	}
	else if(peek(q) == "CHOP")
	{
		match(s,q,q.front(),"CHOP",flag);
		match(s,q,q.front(), "LPAREN",flag);
		chopTail(s,q,flag);
		match(s,q,q.front(), "RPAREN",flag);
		numExprTail_w_op(s,q,flag);
	}
	else if(peek(q) == "LPAREN")
	{
		match(s,q,q.front(), "LPAREN",flag);
		numExpr(s,q,flag);
		match(s,q,q.front(), "RPAREN",flag);
		numExprTail_w_op(s,q,flag);
	}
	else
	{
		cout << "Error on line " << q.front().lineNumber << endl;
		flag = 1;
	}
}

void evalToBoolFollow(stack<tokenObject> s, queue<tokenObject> & q, int & flag)
{
	cout << "Entering Function evalToBoolFollow" << endl;
	if(peek(q) == "NUMOP" || peek(q) == "COMPOP")
	{
		numExprTail_w_op(s,q,flag);
		boolop(s,q,flag);
		boolNumExprTail(s,q,flag);
	}
	else
	{
		cout << "Error on line " << q.front().lineNumber << endl;
		flag = 1;
	}
}

void identFollow(stack<tokenObject> s, queue<tokenObject> & q, int & flag)
{
	if(peek(q) == "AND" || peek(q) == "OR" || peek(q) == "RPAREN" || peek(q) == "EOL")
	{
		boolExprTail(s,q,flag);
	}
	else if(peek(q) == "COMPOP" || peek(q) == "NUMOP" || peek(q) == "EOL")
	{
		evalToBoolFollow(s,q,flag);
	}
	else
	{
		cout << "Error on line " << q.front().lineNumber << endl;
		flag = 1;
	}
}

void exprTailB(stack<tokenObject> s, queue<tokenObject> & q, int & flag)
{
	cout << "Entering Function exprTailB" << endl;

	if(peek(q) == "AND" || peek(q) == "OR" || peek(q) == "RPAREN" || peek(q) == "LPAREN" || peek(q) == "EOL")
	{
		boolExprTail(s,q,flag);
	}
	else if(peek(q) == "COMPOP")
	{
		boolop(s,q,flag);
		boolNumExprTail(s,q,flag);
	}
	else if(peek(q) == "NUMOP")
	{
		op(s,q,flag);
		numExpr(s,q,flag);
	}
	else
	{
		cout << "Error on line " << q.front().lineNumber << endl;
		flag = 1;
	}
}

void exprTailA(stack<tokenObject> s, queue<tokenObject> & q, int & flag)
{
	cout << "Entering Function exprTailA" << endl;
	if(peek(q) == "COMPOP"){
		boolop(s,q,flag);
		boolNumExprTail(s,q,flag);
	}
	else if(peek(q) == "NUMOP"){
		op(s,q,flag);
		numExpr(s,q,flag);
	}
	else if(peek(q)  == "RPAREN" || peek(q) == "EOL")
		return;
}

void chopTail(stack<tokenObject> s, queue<tokenObject> & q, int & flag)
{
	cout << "Entering Function chopTail" << endl;
	if(peek(q) == "NUMLIT")
	{
		numLit(s,q,flag);
		numExprTail_w_op(s,q,flag);
	}
	else if(peek(q) == "IDENT")
	{
		ident(s,q,flag);
		numExprTail_w_op(s,q,flag);
	}
	else
	{
		cout << "Error on line " << q.front().lineNumber << endl;
		flag = 1;
	}
}

void expr(stack<tokenObject> s, queue<tokenObject> & q, int & flag)
{
	cout << "Entering Function expr" << endl;
	if(peek(q) == "IDENT")
	{
		ident(s,q,flag);
		exprTailB(s,q,flag);
	}
	else if(peek(q) == "NUMLIT")
	{
		numLit(s,q,flag);
		exprTailA(s,q,flag);
	}
	else if(peek(q) == "BOOLIT")
	{
		booLit(s,q,flag);
		boolExprTail(s,q,flag);
	}
	else if(peek(q) == "LPAREN")
	{
		match(s,q,q.front(),"LPAREN",flag);
		parenExpr(s,q,flag);
		parenExpr(s,q,flag);
	}
	else if(peek(q) == "CHOP")
	{
		match(s,q,q.front(),"CHOP",flag);
		match(s,q,q.front(),"LPAREN",flag);
		chopTail(s,q,flag);
		match(s,q,q.front(),"RPAREN",flag);
		exprTailA(s,q,flag);
	}
	else
	{
		cout << "Error on line " << q.front().lineNumber << endl;
		flag = 1;
	}
}

void param(stack<tokenObject> s, queue<tokenObject> & q, int & flag)
{
	cout << "Entering Function param" << endl;
	if(peek(q) == "TYPE")
	{
		type(s,q,flag);
		ident(s,q,flag);
	}
	else
	{
		cout << "Error on line " << q.front().lineNumber << endl;
		flag = 1;
	}
}

void paramsA(stack<tokenObject> s, queue<tokenObject> & q, int & flag)
{
	cout << "Entering Function paramsA" << endl;
	if(peek(q) == "COMMA"){
		match(s,q,q.front(),"COMMA",flag);
		params(s,q,flag);
	}
	else if(peek(q) == "RPAREN")
		return;
}

void params(stack<tokenObject> s, queue<tokenObject> & q, int & flag)
{
	cout << "Entering Function params" << endl;
	if(peek(q) == "TYPE")
	{
		param(s,q,flag);
		paramsA(s,q,flag);
	}
	else
	{
		cout << "Error on line " << q.front().lineNumber << endl;
		flag = 1;
	}
}

void opt_params(stack<tokenObject> s, queue<tokenObject> & q, int & flag)
{
	cout << "Entering Function opt_params" << endl;
	if(peek(q) == "TYPE")
		params(s,q,flag);
	else if(peek(q) == "RPAREN")
		return;
}

void fun_stmts(stack<tokenObject> s, queue<tokenObject> & q, int & flag)
{
	cout << "Entering Function fun_stmts" << endl;
	if(peek(q) == "IF" || peek(q) == "WHILE" || peek(q) == "TYPE" || peek(q) == "IDENT" || peek(q) == "NUMLIT" || peek(q) == "LPAREN" || peek(q) == "CHOP")
	{
		stmts(s,q,flag);
		fun_stmts(s,q,flag);
	}
	else if(peek(q) == "TOSS"){
		match(s,q,q.front(),"TOSS",flag);
		expr(s,q,flag);
	}
	else if(peek(q) == "EOL")
		return;
}

void optional_stmts(stack<tokenObject> s, queue<tokenObject> & q, int & flag)
{
	cout << "Entering Function optional_stmts" << endl;

	fun_stmts(s,q,flag);
}

void elvesA(stack<tokenObject> s, queue<tokenObject> & q, int & flag)
{
	cout << "Entering Function elvesA" << endl;
	if(peek(q) == "ELF")
		elves(s,q,flag);
	else if(peek(q) == "ENDIF" || peek(q) == "ELSE")
		return;
}

void elves(stack<tokenObject> s, queue<tokenObject> & q, int & flag)
{
	cout << "Entering Function elves" << endl;
	if(peek(q) == "ELF")
	{
		match(s,q,q.front(),"ELF",flag);
		match(s,q,q.front(),"LPAREN",flag);
		boolexp(s,q,flag);
		match(s,q,q.front(),"RPAREN",flag);
		match(s,q,q.front(),"EOL",flag);
		optional_stmts(s,q,flag);
		match(s,q,q.front(), "EOL",flag);
		elvesA(s,q,flag);
	}
	else
	{
		cout << "Error on line " << q.front().lineNumber << endl;
		flag = 1;
	}
}

void stmtC(stack<tokenObject> s, queue<tokenObject> & q, int & flag)
{
	cout << "Entering Function stmtC" << endl;
	if(peek(q) == "ASSIGN"){
		match(s,q,q.front(),"ASSIGN",flag);
		expr(s,q,flag);
	}
	else if(peek(q) == "EOL")
		return;
}

void stmtB(stack<tokenObject> s, queue<tokenObject> & q, int & flag)
{
	cout << "Entering Function stmtB" << endl;
	if(peek(q) == "ENDIF")
		match(s,q,q.front(),"ENDIF",flag);
	else if(peek(q) == "ELSE")
	{
		match(s,q,q.front(),"ELSE",flag);
		match(s,q,q.front(),"EOL",flag);
		optional_stmts(s,q,flag);
		match(s,q,q.front(),"EOL",flag);
		match(s,q,q.front(),"ENDIF",flag);
	}
	else
	{
		cout << "Error on line " << q.front().lineNumber << endl;
		flag = 1;
	}
}

void stmtA(stack<tokenObject> s, queue<tokenObject> & q, int & flag)
{
	cout << "Entering Function stmtA" << endl;
	cout << "PEEK OF Q IN STATEMENT A " << peek(q) << endl;
	if(peek(q) == "ENDIF")
		match(s,q,q.front(),"ENDIF",flag);
	else if(peek(q) == "ELSE")
	{
		match(s,q,q.front(),"ELSE",flag);
		match(s,q,q.front(),"EOL",flag);
		optional_stmts(s,q,flag);
		match(s,q,q.front(),"EOL",flag);
		match(s,q,q.front(),"ENDIF",flag);
	}
	else if(peek(q) == "ELF")
	{
		elves(s,q,flag);
		stmtB(s,q,flag);
	}
	else
	{
		cout << "Error on line " << q.front().lineNumber << endl;
		flag = 1;
	}
}

void stmt(stack<tokenObject> s, queue<tokenObject> & q, int & flag)
{
	cout << "Entering Function stmt" << endl;
	if(peek(q) == "IF")
	{
		match(s,q,q.front(),"IF",flag);
		match(s,q,q.front(),"LPAREN",flag);
		boolexp(s,q,flag);
		match(s,q,q.front(),"RPAREN",flag);
		match(s,q,q.front(),"EOL",flag);
		optional_stmts(s,q,flag);
		stmtA(s,q,flag);
	}
	else if(peek(q) == "WHILE")
	{
		match(s,q,q.front(),"WHILE",flag);
		match(s,q,q.front(),"LPAREN",flag);
		boolexp(s,q,flag);
		match(s,q,q.front(),"RPAREN",flag);
		match(s,q,q.front(),"EOL",flag);
		optional_stmts(s,q,flag);
		match(s,q,q.front(),"ENDWHILE",flag);
	}
	else if(peek(q) == "TYPE")
	{
		type(s,q,flag);
		ident(s,q,flag);
		stmtC(s,q,flag);
	}
	else if(peek(q) == "IDENT" || peek(q) == "NUMLIT" || peek(q) == "LPAREN" || peek(q) == "CHOP")
		expr(s,q,flag);
	else
	{
		cout << "Error on line " << q.front().lineNumber << endl;
		flag = 1;
	}
}

void stmtX(stack<tokenObject> s, queue<tokenObject> & q, int & flag)
{
	cout << "Entering Function stmtX" << endl;
	if(peek(q) == "IF" || peek(q) == "WHILE" || peek(q) == "TYPE" || peek(q) == "IDENT" || peek(q) == "BOOLIT" || peek(q) == "NUMLIT" || peek(q) == "LPAREN" || peek(q) == "CHOP")
		stmts(s,q,flag);
	else if(peek(q) == "EOL")
		return;
}

void stmts(stack<tokenObject> s, queue<tokenObject> & q, int & flag)
{
	cout << "Entering Function stmt" << endl;
	if(peek(q) == "IF" || peek(q) == "WHILE" || peek(q) == "TYPE" || peek(q) == "IDENT" || peek(q) == "NUMLIT" || peek(q) == "LPAREN" || peek(q) == "CHOP")
	{
		stmt(s,q,flag);
		match(s,q,q.front(),"EOL",flag);
		stmtX(s,q,flag);
	}
	else
	{
		cout << "Error on line " << q.front().lineNumber << endl;
		flag = 1;
	}
}

void toplvlstmt(stack<tokenObject> s, queue<tokenObject> & q, int & flag)
{
	cout << "Entering Function toplvlstmt" << endl;

	if(peek(q) == "FUN")
	{
		//functional declaration
		match(s,q,q.front(),"FUN",flag);
		cout << "current front->" << q.front().lexeme << endl;
		ident(s,q,flag);
		match(s,q,q.front(),"LPAREN",flag);
		opt_params(s,q,flag);
		match(s,q,q.front(),"RPAREN",flag);
		match(s,q,q.front(),"AS",flag);
		type(s,q,flag);
		match(s,q,q.front(),"EOL",flag);


		fun_stmts(s,q,flag);
		match(s,q,q.front(),"EOL",flag); //i think this is righ
		match(s,q,q.front(),"TOSS",flag);
		expr(s,q,flag);
		cout << "heluuuuurrrr-----" << endl;
		match(s,q,q.front(),"EOL",flag);
		match(s,q,q.front(),"ENDFUN",flag);
		cout << "End of toplvlstmt" << endl;
		return;
	}
	else if(peek(q) == "IF" || peek(q) == "WHILE" || peek(q) == "TYPE" || peek(q) == "IDENT" || peek(q) == "NUMLIT" || peek(q) == "LPAREN" || peek(q) == "CHOP")
		stmts(s,q,flag);
	else
	{
		cout << "Error on line " << q.front().lineNumber << endl;
		flag = 1;
	}
}

void toplvlstmtsA(stack<tokenObject> s, queue<tokenObject>  & q, int & flag)
{
	if(peek(q) == "IF" || peek(q) == "WHILE" || peek(q) == "TYPE" || peek(q) == "IDENT" || peek(q) == "NUMLIT" || peek(q) == "LPAREN" || peek(q) == "CHOP" || peek(q) == "FUN" || peek(q) == "EOL")
		toplvlstmts(s,q,flag);
	else if(peek(q) == "EOL")
		return;
}

void toplvlstmts(stack<tokenObject> s, queue<tokenObject> & q, int & flag)
{
	if(peek(q) == "IF" || peek(q) == "WHILE" || peek(q) == "TYPE" || peek(q) == "IDENT" || peek(q) == "NUMLIT" || peek(q) == "LPAREN" || peek(q) == "CHOP" || peek(q) == "FUN" || peek(q) == "EOL")
	{
		cout << "Entering toplvlstmts " << endl;
		toplvlstmt(s,q,flag);
		match(s,q,q.front(),"EOL",flag);
		toplvlstmtsA(s,q,flag);
		cout << "Leaving function program..." << endl;
	}
	else
	{
		cout << "Error on line " << q.front().lineNumber << endl;
		flag = 1;
	}
}

void program(stack<tokenObject> s, queue<tokenObject>  & q, int & flag)
{

	cout << q.front().token << endl;

	if(peek(q) == "IF" || peek(q) == "WHILE" || peek(q) == "TYPE" || peek(q) == "IDENT" || peek(q) == "NUMLIT" || peek(q) == "LPAREN" || peek(q) == "CHOP" || peek(q) == "FUN" || peek(q) == "EOL")
	{
		toplvlstmts(s,q,flag);
		cout << "Leaving function program..." << endl;
	}
	else{
		cout << "failed in program" << endl;
		flag = 1;
	}
}