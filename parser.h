#ifndef PARSER_H
#define PARSER_H

#include <string>
#include "string.h"
#include "ast.h"

using namespace std;

class parser {
public:
	parser();
	~parser();

private:
	vector<symbol>	symbol_list;
	string	symbol_list_string; //collects all symbol names

public:
	inline unsigned symbol_list_size()	
		{ return symbol_list.size(); }

	void add_symbol(symbol);
	//ast* parse(string);
};

#endif