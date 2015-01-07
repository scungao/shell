#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "symbol.h"
#include <string>
#include <vector>
#include <map>

using namespace std;

class dictionary {
	map<string, symbol*>	symbol_map;
	//map<string, ast*>	ast_map;
	//map< string*, s_type >		name_type_map;
	vector<int>	variable_id_list;
	vector<int>	constant_id_list; //faster access
	vector<int> function_id_list;
public:
	inline dictionary() {}
	~dictionary();
	inline unsigned get_size() { return symbol_map.size();}
	inline void add(symbol* s) 
		{ symbol_map.insert(pair<string,symbol*>(s->get_name(), s)); }
	symbol*	locate_symbol(string);
	//node*	locate_node(string);
	//ast*	locate_ast(string);
};

#endif