#ifndef TABLE_H
#define TABLE_H

#include "ast.h"
#include <string>
#include <vector>
#include <map>

using namespace std;

class table {
	map<string, symbol*>	symbol_table;
	map<symbol*, ast*>		ast_table; //only keeps top-level ast
	vector<int>	variable_id_list;
	vector<int>	constant_id_list; //faster access
	vector<int> process_id_list;
public:
	table();
	~table();
	inline unsigned get_size() { return symbol_table.size();}
	inline void add(symbol* s) 
		{ symbol_table.insert(pair<string,symbol*>(s->get_name(), s)); }
	inline void add_ast(symbol* s, ast* a)
		{ ast_table.insert(pair<symbol*, ast*>(s, a)); }	
	symbol*	locate_symbol(string);

	//node*	locate_node(string);
	//ast*	locate_ast(string);
};

#endif