#include <iostream>
#include <fstream>
#include <stdio.h>
#include <regex>

struct tokenObject
{
  std::string token;
  std::string lexeme;
  int lineNumber;
};
// creates copy of source file and removes comments from 2nd copy
std::string preprocessor(std::string source)
{
    std::string clone = "_" + source + "_";
    std::regex e ("#(.*)");
    std::ifstream in(source.c_str());
    std::ofstream out(clone.c_str());
    std::string line;

    while(getline(in, line))
		out << std::regex_replace (line,e,"") << "\n";
    return clone;
}
//deletes specified file
void removeFile(std::string filename){
	const char * c_filename = filename.c_str();
	if( remove( c_filename ) != 0 )
    	perror( "Error source file not deleted" );
    else
    	puts( "Source file deleted" );
}
//convert char to string
std::string charToStr(char c){
  std::stringstream ss;
  std::string str;
  ss << c;
  ss >> str;
  return str;
}
//duplicate file and return filename of duplicate file
// std::string duplicateFile(std::string source){
//     std::string clone = "_" + source + "_";

//     std::ifstream in(source.c_str()); // Open for reading
//     std::ofstream out(clone.c_str()); // Create and open for writing
//     std::string s;
//     while(getline(in, s))
//         out << s << "\n";
//     return clone;
// }