#include <iostream>
#include <queue>
#include <stack>
using namespace std;

string peek(queue<tokenObject> & q)
{
	tokenObject _t = q.front();
	return _t.token;
}

void match(stack<tokenObject> s, queue<tokenObject> & q, tokenObject _t, string expected_value)
{
	if(expected_value == _t.token){
		cout << "MATCHED TOKEN: " << _t.token << endl; //token
		s.push(_t);
		q.pop();

	}
	else
		return;
}

void numLit(stack<tokenObject> s, queue<tokenObject> & q)
{
	if(peek(q) == "NUMLIT")
		match(s,q,q.front(),"NUMLIT");
}

void booLit(stack<tokenObject> s, queue<tokenObject> & q)
{
	if(peek(q) == "BOOLIT")
		match(s,q,q.front(),"BOOLIT");
}

void ident(stack<tokenObject> s, queue<tokenObject> & q)
{
	cout << "Entering ident " << endl;
	if(peek(q) == "IDENT")
		match(s,q,q.front(),"IDENT");
}

void boolop(stack<tokenObject> s, queue<tokenObject> & q)
{
	cout << "Entering boolop " << endl;
	if(peek(q) == "COMPOP")
		match(s,q,q.front(),"COMPOP");
}

void op(stack<tokenObject> s, queue<tokenObject> & q)
{
	cout << "Entering op " << endl;
	if(peek(q) == "NUMOP")
		match(s,q,q.front(),"NUMOP");
}

void type(stack<tokenObject> s, queue<tokenObject> & q)
{
	cout << "Entering type " << endl;

	if(peek(q) == "TYPE")
		match(s,q,q.front(),"TYPE");
}

void boolexp(stack<tokenObject> s, queue<tokenObject> & q);

void boolExprTailParen(stack<tokenObject> s, queue<tokenObject> & q);

void exprTailAParen(stack<tokenObject> s, queue<tokenObject> & q);

void exprTailBParen(stack<tokenObject> s, queue<tokenObject> & q);

void parenExpr(stack<tokenObject> s, queue<tokenObject> & q);

void boolexp(stack<tokenObject> s, queue<tokenObject> & q);

void boolExprTailParen(stack<tokenObject> s, queue<tokenObject> & q);

void exprTailAParen(stack<tokenObject> s, queue<tokenObject> & q);

void exprTailBParen(stack<tokenObject> s, queue<tokenObject> & q);

void parenExpr(stack<tokenObject> s, queue<tokenObject> & q);

void numExprTail_w_op(stack<tokenObject> s, queue<tokenObject> & q);

void boolNumExprTail(stack<tokenObject> s, queue<tokenObject> & q);

void boolExprTail(stack<tokenObject> s, queue<tokenObject> & q);

void numExpr(stack<tokenObject> s, queue<tokenObject> & q);

void evalToBoolFollow(stack<tokenObject> s, queue<tokenObject> & q);

void identFollow(stack<tokenObject> s, queue<tokenObject> & q);

void exprTailB(stack<tokenObject> s, queue<tokenObject> & q);

void exprTailA(stack<tokenObject> s, queue<tokenObject> & q);

void chopTail(stack<tokenObject> s, queue<tokenObject> & q);

void expr(stack<tokenObject> s, queue<tokenObject> & q);

void param(stack<tokenObject> s, queue<tokenObject> & q);

void paramsA(stack<tokenObject> s, queue<tokenObject> & q);

void params(stack<tokenObject> s, queue<tokenObject> & q);

void opt_params(stack<tokenObject> s, queue<tokenObject> & q);

void fun_stmts(stack<tokenObject> s, queue<tokenObject> & q);

void optional_stmts(stack<tokenObject> s, queue<tokenObject> & q);

void elvesA(stack<tokenObject> s, queue<tokenObject> & q);

void elves(stack<tokenObject> s, queue<tokenObject> & q);

void stmtC(stack<tokenObject> s, queue<tokenObject> & q);

void stmtB(stack<tokenObject> s, queue<tokenObject> & q);

void stmtA(stack<tokenObject> s, queue<tokenObject> & q);

void stmt(stack<tokenObject> s, queue<tokenObject> & q);

void stmtX(stack<tokenObject> s, queue<tokenObject> & q);

void stmts(stack<tokenObject> s, queue<tokenObject> & q);

void toplvlstmt(stack<tokenObject> s, queue<tokenObject> & q);

void toplvlstmtsA(stack<tokenObject> s, queue<tokenObject> & q);

void toplvlstmts(stack<tokenObject> s, queue<tokenObject> & q);

void program(stack<tokenObject> s, queue<tokenObject> & q);


void boolexp(stack<tokenObject> s, queue<tokenObject> & q)
{
	cout << "Entering Function boolexp" << endl;
	if(peek(q) == "BOOLIT"){
		booLit(s,q);
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
		return;
}

void boolExprTailParen(stack<tokenObject> s, queue<tokenObject> & q)
{
	cout << "Entering Function boolExprTailParen" << endl;
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
		return;
}

void exprTailAParen(stack<tokenObject> s, queue<tokenObject> & q)
{
	cout << "Entering Function exprTailAParen" << endl;
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
		return;
}

void exprTailBParen(stack<tokenObject> s, queue<tokenObject> & q)
{
	cout << "Entering Function exprTailBParen" << endl;
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
		numExpr(s,q);
		match(s,q,q.front(),"RPAREN");
		exprTailA(s,q);
	}
	else
		return;
}

void parenExpr(stack<tokenObject> s, queue<tokenObject> & q)
{
	cout << "Entering Function parenExpr" << endl;
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
		return;
}

void numExprTail_w_op(stack<tokenObject> s, queue<tokenObject> & q)
{
	cout << "Entering Function numExprTail_w_op" << endl;
	if(peek(q) == "NUMOP")
	{
		op(s,q);
		numExpr(s,q);
	}
	else if(peek(q) == "COMPOP" || peek(q) == "RPAREN" || peek(q) == "EOL")
		return;
	else
		return;
}

void boolNumExprTail(stack<tokenObject> s, queue<tokenObject> & q)
{
	cout << "Entering Function boolNumExprTail" << endl;
	if(peek(q) == "NUMLIT" || peek(q) == "IDENT" || peek(q) == "CHOP" || peek(q) == "LPAREN")
	{
		numExpr(s,q);
		boolExprTail(s,q);
	}
	else
		return;
}

void boolExprTail(stack<tokenObject> s, queue<tokenObject> & q)
{
	cout << "Entering Function boolExprTail" << endl;
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
	else if(peek(q) == "EOL")
	{
		match(s,q,q.front(),"EOL");
		// return;
	}
	// else if(peek(q) == "RPAREN")
	// {
	// 	match(s,q,q.front(),"RPAREN");
	// }
	else
		return;
}

void numExpr(stack<tokenObject> s, queue<tokenObject> & q)
{
	cout << "Entering Function numExpr" << endl;
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
		return;
}

void evalToBoolFollow(stack<tokenObject> s, queue<tokenObject> & q)
{
	cout << "Entering Function evalToBoolFollow" << endl;
	if(peek(q) == "NUMOP" || peek(q) == "COMPOP")
	{
		numExprTail_w_op(s,q);
		boolop(s,q);
		boolNumExprTail(s,q);
	}
	else
		return;
}

void identFollow(stack<tokenObject> s, queue<tokenObject> & q)
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

void exprTailB(stack<tokenObject> s, queue<tokenObject> & q)
{
	cout << "Entering Function exprTailB" << endl;

	if(peek(q) == "AND" || peek(q) == "OR" || peek(q) == "RPAREN" || peek(q) == "EOL")
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
		return;
}

void exprTailA(stack<tokenObject> s, queue<tokenObject> & q)
{
	cout << "Entering Function exprTailA" << endl;
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
		return;
}

void chopTail(stack<tokenObject> s, queue<tokenObject> & q)
{
	cout << "Entering Function chopTail" << endl;
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
		return;
}

void expr(stack<tokenObject> s, queue<tokenObject> & q)
{
	cout << "Entering Function expr" << endl;
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
		parenExpr(s,q);
		parenExpr(s,q);
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
		return;
}

void param(stack<tokenObject> s, queue<tokenObject> & q)
{
	cout << "Entering Function param" << endl;
	if(peek(q) == "TYPE")
	{
		type(s,q);
		ident(s,q);
	}
	else
		return;
}

void paramsA(stack<tokenObject> s, queue<tokenObject> & q)
{
	cout << "Entering Function paramsA" << endl;
	if(peek(q) == "COMMA"){
		match(s,q,q.front(),"COMMA");
		params(s,q);
	}
	else if(peek(q) == "RPAREN")
		return;
	else
		return;
}

void params(stack<tokenObject> s, queue<tokenObject> & q)
{
	cout << "Entering Function params" << endl;
	if(peek(q) == "TYPE")
	{
		param(s,q);
		paramsA(s,q);
	}
	else
		return;
}

void opt_params(stack<tokenObject> s, queue<tokenObject> & q)
{
	cout << "Entering Function opt_params" << endl;
	if(peek(q) == "TYPE")
		params(s,q);
	else if(peek(q) == "RPAREN")
		return;
	else
		return;
}

void fun_stmts(stack<tokenObject> s, queue<tokenObject> & q)
{
	cout << "Entering Function fun_stmts" << endl;
	if(peek(q) == "IF" || peek(q) == "WHILE" || peek(q) == "TYPE" || peek(q) == "IDENT" || peek(q) == "NUMLIT" || peek(q) == "LPAREN" || peek(q) == "CHOP")
	{
		stmts(s,q);
		fun_stmts(s,q);
	}
	else if(peek(q) == "TOSS"){
		match(s,q,q.front(),"TOSS");
		expr(s,q);
	}
	else if(peek(q) == "EOL")
		return;
	else
		return;
}

void optional_stmts(stack<tokenObject> s, queue<tokenObject> & q)
{
	cout << "Entering Function optional_stmts" << endl;
	// if(peek(q) == "IF" || peek(q) == "WHILE" || peek(q) == "TYPE" || peek(q) == "IDENT" || peek(q) == "NUMLIT" || peek(q) == "LPAREN" || peek(q) == "CHOP")
	// {
	// 	stmts(s,q);
	// 	match(s,q,q.front(),"EOL");
	// }
	// else if(peek(q) == "EOL")
	// 	return;
	// else
	// 	return;
	fun_stmts(s,q);
}

void elvesA(stack<tokenObject> s, queue<tokenObject> & q)
{
	cout << "Entering Function elvesA" << endl;
	if(peek(q) == "ELF")
		elves(s,q);
	else if(peek(q) == "ENDIF" || peek(q) == "ELSE")
		return;
	else
		return;
}

void elves(stack<tokenObject> s, queue<tokenObject> & q)
{
	cout << "Entering Function elves" << endl;
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
		return;
}

void stmtC(stack<tokenObject> s, queue<tokenObject> & q)
{
	cout << "Entering Function stmtC" << endl;
	if(peek(q) == "ASSIGN"){
		match(s,q,q.front(),"ASSIGN");
		expr(s,q);
	}
	else if(peek(q) == "EOL")
		return;
	else
		return;
}

void stmtB(stack<tokenObject> s, queue<tokenObject> & q)
{
	cout << "Entering Function stmtB" << endl;
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
		return;
}

void stmtA(stack<tokenObject> s, queue<tokenObject> & q)
{
	cout << "Entering Function stmtA" << endl;
	cout << "PEEK OF Q IN STATEMENT A " << peek(q) << endl;
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
		return;
}

void stmt(stack<tokenObject> s, queue<tokenObject> & q)
{
	cout << "Entering Function stmt" << endl;
	if(peek(q) == "IF")
	{
		match(s,q,q.front(),"IF");
		match(s,q,q.front(),"LPAREN");
		boolexp(s,q);
		match(s,q,q.front(),"RPAREN");
		match(s,q,q.front(),"EOL");
		optional_stmts(s,q);
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
		match(s,q,q.front(),"ENDWHILE");
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
		return;
}

void stmtX(stack<tokenObject> s, queue<tokenObject> & q)
{
	cout << "Entering Function stmtX" << endl;
	if(peek(q) == "IF" || peek(q) == "WHILE" || peek(q) == "TYPE" || peek(q) == "IDENT" || peek(q) == "NUMLIT" || peek(q) == "LPAREN" || peek(q) == "CHOP")
		stmts(s,q);
	else if(peek(q) == "EOL")
		return;
	else
		return;
}

void stmts(stack<tokenObject> s, queue<tokenObject> & q)
{
	cout << "Entering Function stmt" << endl;
	if(peek(q) == "IF" || peek(q) == "WHILE" || peek(q) == "TYPE" || peek(q) == "IDENT" || peek(q) == "NUMLIT" || peek(q) == "LPAREN" || peek(q) == "CHOP")
	{
		stmt(s,q);
		match(s,q,q.front(),"EOL");
		stmtX(s,q);
	}
	else
		return;
}

void toplvlstmt(stack<tokenObject> s, queue<tokenObject> & q)
{
	cout << "Entering Function toplvlstmt" << endl;

	if(peek(q) == "FUN")
	{
		match(s,q,q.front(),"FUN");
		cout << "current front->" << q.front().lexeme << endl;
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
		cout << "End of toplvlstmt" << endl;
		return;
	}
	else if(peek(q) == "IF" || peek(q) == "WHILE" || peek(q) == "TYPE" || peek(q) == "IDENT" || peek(q) == "NUMLIT" || peek(q) == "LPAREN" || peek(q) == "CHOP")
		stmts(s,q);
	else
		return;
}

void toplvlstmtsA(stack<tokenObject> s, queue<tokenObject> & q)
{
	if(peek(q) == "IF" || peek(q) == "WHILE" || peek(q) == "TYPE" || peek(q) == "IDENT" || peek(q) == "NUMLIT" || peek(q) == "LPAREN" || peek(q) == "CHOP" || peek(q) == "FUN" || peek(q) == "EOL")
		toplvlstmts(s,q);
	else if(peek(q) == "EOL")
		return;
	else
		return;
}

void toplvlstmts(stack<tokenObject> s, queue<tokenObject> & q)
{
	if(peek(q) == "IF" || peek(q) == "WHILE" || peek(q) == "TYPE" || peek(q) == "IDENT" || peek(q) == "NUMLIT" || peek(q) == "LPAREN" || peek(q) == "CHOP" || peek(q) == "FUN" || peek(q) == "EOL")
	{
		cout << "Entering toplvlstmts " << endl;
		toplvlstmt(s,q);
		match(s,q,q.front(),"EOL");
		toplvlstmtsA(s,q);
		cout << "Leaving function program..." << endl;
	}
	else
		return;
}

void program(stack<tokenObject> s, queue<tokenObject>  & q)
{
	
	cout << q.front().token << endl;

	if(peek(q) == "IF" || peek(q) == "WHILE" || peek(q) == "TYPE" || peek(q) == "IDENT" || peek(q) == "NUMLIT" || peek(q) == "LPAREN" || peek(q) == "CHOP" || peek(q) == "FUN" || peek(q) == "EOL")
	{
		toplvlstmts(s,q);
		cout << "Leaving function program..." << endl;
	}
	else
		cout << "failed in program" << endl;
}

