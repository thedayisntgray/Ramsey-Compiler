#include <iostream>
#include <fstream>
#include <stdio.h>
#include <regex>

// creates copy of source file and removes comments from 2nd copy
void preprocessor(std::string source)
{
    std::string clone = "_" + source;
    std::regex e ("#(.*)");
    std::ifstream in(source.c_str());
    std::ofstream out(clone.c_str());
    std::string line;

    while(getline(in, line))
		out << std::regex_replace (line,e,"") << "\n";
}
//deletes specified file
void removeFile(string filename){
	const char * c_filename = filename.c_str();
	if( remove( c_filename ) != 0 )
    	perror( "Error source file not deleted" );
    else
    	puts( "Source file deleted" );
}