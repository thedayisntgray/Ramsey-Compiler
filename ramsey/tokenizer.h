#include <iostream>
#include <string>
#include <regex>

std::string getTokenType(std::string lexeme){
    //IDENTIFIER
    if (std::regex_match (lexeme, std::regex("[a-z,A-Z_]+[a-zA-Z0-9_]*") ))
        return "IDENT\n";
    //LITERAL
    if (std::regex_match (lexeme, std::regex("[0-9]+") ))
        return "LITERAL\n";
    //END OF LINE
    if (std::regex_match (lexeme, std::regex("\n") ))
        return "EOL\n";
    //ASSIGN
    if (std::regex_match (lexeme, std::regex("^<-$") ))
        return "ASSIGN\n";
    //PLUS
    if (std::regex_match (lexeme, std::regex("^+$") ))
        return "PLUS\n";
    //MINUS
    if (std::regex_match (lexeme, std::regex("^-$") ))
        return "MINUS\n";
    //DIVIDE
    if (std::regex_match (lexeme, std::regex("^/$") ))
        return "DIV\n";
    //MULTIPLY
    if (std::regex_match (lexeme, std::regex("^\\*$") ))
        return "MUL\n";
    //MODULAR DIVISION
    if (std::regex_match (lexeme, std::regex("^mod$") ))
        return "MOD\n";
    if (std::regex_match (lexeme, std::regex(">=|<=|!=|=|<|>") ))
        return "COMPOP\n";
    if (std::regex_match (lexeme, std::regex("^$if$") ))
        return "IF\n";
    if (std::regex_match (lexeme, std::regex("^elf$") ))
        return "ELF\n";
    if (std::regex_match (lexeme, std::regex("^else$") ))
        return "ELSE\n";
    if (std::regex_match (lexeme, std::regex("^endif$") ))
        return "ENDIF\n";
    if (std::regex_match (lexeme, std::regex("^while$") ))
        return "WHILE\n";
    if (std::regex_match (lexeme, std::regex("^endwhile$") ))
        return "ENDWHILE\n";
    if (std::regex_match (lexeme, std::regex("^take$") ))
        return "TAKE\n";
    if (std::regex_match (lexeme, std::regex("^toss$") ))
        return "TOSS\n";
    if (std::regex_match (lexeme, std::regex("^fun$") ))
        return "FUN\n";
    if (std::regex_match (lexeme, std::regex("^endfun$") ))
        return "ENDFUN\n";
    if (std::regex_match (lexeme, std::regex("^as$") ))
        return "AS\n";
    if (std::regex_match (lexeme, std::regex("^and$") ))
        return "AND\n";
    if (std::regex_match (lexeme, std::regex("^or$") ))
        return "OR\n";
    if (std::regex_match (lexeme, std::regex("^give$") ))
        return "GIVE\n";
    if (std::regex_match (lexeme, std::regex("\\(") ))
        return "LPAREN\n";
    if (std::regex_match (lexeme, std::regex("^\\)$") ))
        return "RPAREN\n";
    if (std::regex_match (lexeme, std::regex("^boo$") ))
        return "BOO\n";
    if (std::regex_match (lexeme, std::regex("^in$") ))
        return "IN\n";
    if (std::regex_match (lexeme, std::regex("^big$") ))
        return "BIG\n";
    if (std::regex_match (lexeme, std::regex("^small$") ))
        return "SMALL\n";

    return "Error: Unclassified Lexeme\n";
}