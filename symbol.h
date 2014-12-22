#ifndef SYMBOL_H
#define SYMBOL_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class symbol {
public:
	symbol(string);
	~symbol();

private:
	string	name;

public:
	inline string	getname() { return name; }
};

#endif