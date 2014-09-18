#include "lexi.h"
#include <iostream>
#include <fstream>
#include <stdio.h>

using namespace std;

int main(){
	string filename;
	cout << "Enter filename\n";
	cin >> filename;
	preprocessor(filename);
	// duplicateFile(filename);
}