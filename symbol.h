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
	const string	name;

public:
	inline string	get_name() { return name; }
};

#endif