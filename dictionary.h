#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "symbol.h"
#include "ast.h"
#include <string>
#include <vector>
#include <map>

using namespace std;

class dictionary {
	map<string, symbol*>	symbol_map;
	map<symbol*, ast*>		ast_map; //only keeps top-level ast
	vector<int>	variable_id_list;
	vector<int>	constant_id_list; //faster access
	vector<int> process_id_list;
public:
	inline dictionary() {}
	~dictionary();
	inline unsigned get_size() { return symbol_map.size();}
	inline void add(symbol* s) 
		{ symbol_map.insert(pair<string,symbol*>(s->get_name(), s)); }
	inline void add_ast(symbol* s, ast* a)
		{ ast_map.insert(pair<symbol*, ast*>(s, a)); }	
	symbol*	locate_symbol(string);

	//node*	locate_node(string);
	//ast*	locate_ast(string);
};

#endif