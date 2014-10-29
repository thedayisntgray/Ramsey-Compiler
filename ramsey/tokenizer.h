#include <iostream>
#include <string>
#include <regex>

std::string getTokenType(std::string lexeme){
    //LITERAL
    if (std::regex_match (lexeme, std::regex("-?[0-9]+") ))
        return "LITERAL";
    //END OF LINE
    if (std::regex_match (lexeme, std::regex("\n") ))
        return "EOL";
    //ASSIGN
    if (std::regex_match (lexeme, std::regex("^<-$") ))
        return "ASSIGN";
    if (std::regex_match (lexeme, std::regex(">=|<=|!=|=|<|>") ))
        return "COMPOP";
    if (std::regex_match (lexeme, std::regex("\\+|-|/|\\*|mod") ))
	return "NUMOP";
    if (std::regex_match (lexeme, std::regex("^,$") ))
        return "COMMA";
    if (std::regex_match (lexeme, std::regex("^if$") ))
        return "IF";
    if (std::regex_match (lexeme, std::regex("^elf$") ))
        return "ELF";
    if (std::regex_match (lexeme, std::regex("^else$") ))
        return "ELSE";
    if (std::regex_match (lexeme, std::regex("^endif$") ))
        return "ENDIF";
    if (std::regex_match (lexeme, std::regex("^while$") ))
        return "WHILE";
    if (std::regex_match (lexeme, std::regex("^endwhile$") ))
        return "ENDWHILE";
    if (std::regex_match (lexeme, std::regex("^take$") ))
        return "TAKE";
    if (std::regex_match (lexeme, std::regex("^toss$") ))
        return "TOSS";
    if (std::regex_match (lexeme, std::regex("^fun$") ))
        return "FUN";
    if (std::regex_match (lexeme, std::regex("^endfun$") ))
        return "ENDFUN";
    if (std::regex_match (lexeme, std::regex("^as$") ))
        return "AS";
    if (std::regex_match (lexeme, std::regex("^and$") ))
        return "AND";
    if (std::regex_match (lexeme, std::regex("^or$") ))
        return "OR";
    if (std::regex_match (lexeme, std::regex("^give$") ))
        return "GIVE";
    if (std::regex_match (lexeme, std::regex("^\\($") ))
        return "LPAREN";
    if (std::regex_match (lexeme, std::regex("^\\)$") ))
        return "RPAREN";
    if (std::regex_match (lexeme, std::regex("boo|in|big|small") ))
	return "TYPE";
    if (std::regex_match (lexeme, std::regex("^chop$") ))
        return "CHOP";
        //IDENTIFIER
    if (std::regex_match (lexeme, std::regex("[a-zA-Z]+[a-zA-Z0-9_]*") ))
        return "IDENT";

    return "INVALID";
}
