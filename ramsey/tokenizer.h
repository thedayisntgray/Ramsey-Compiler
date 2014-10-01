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
    //PLUS
    if (std::regex_match (lexeme, std::regex("^\\+$") ))
        return "PLUS";
    //MINUS
    if (std::regex_match (lexeme, std::regex("^-$") ))
        return "MINUS";
    //DIVIDE
    if (std::regex_match (lexeme, std::regex("^/$") ))
        return "DIV";
    //MULTIPLY
    if (std::regex_match (lexeme, std::regex("^\\*$") ))
        return "MUL";
    //MODULAR DIVISION
    if (std::regex_match (lexeme, std::regex("^mod$") ))
        return "MOD";
    if (std::regex_match (lexeme, std::regex(">=|<=|!=|=|<|>") ))
        return "COMPOP";
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
    if (std::regex_match (lexeme, std::regex("\\(") ))
        return "LPAREN";
    if (std::regex_match (lexeme, std::regex("^\\)$") ))
        return "RPAREN";
    if (std::regex_match (lexeme, std::regex("^boo$") ))
        return "BOO";
    if (std::regex_match (lexeme, std::regex("^in$") ))
        return "IN";
    if (std::regex_match (lexeme, std::regex("^big$") ))
        return "BIG";
    if (std::regex_match (lexeme, std::regex("^small$") ))
        return "SMALL";
        //IDENTIFIER
    if (std::regex_match (lexeme, std::regex("[a-z,A-Z_]+[a-zA-Z0-9_]*") ))
        return "IDENT";

    return "Error: Unclassified Lexeme\n";
}