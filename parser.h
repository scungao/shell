#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <vector>
#include <set>
#include <sstream>
#include <regex>
#include "ast.h"
#include "dictionary.h"


using namespace std;

class parser {
	dictionary*		symbol_table;
	string		symbol_name_list; //collects all symbol names
	set<int>	precedence_set;
public:
	parser(dictionary*);
	~parser();

	inline int symbol_table_size()	
		{ return symbol_table -> get_size(); }
	string	collect_variable(istream&, char&);
	string	collect_constant(istream&, char&);
	string	collect_process(istream&, char&);
	string	collect_body(istream&, char&, ast*, int);

	//ast* parse(string);
};

#endif