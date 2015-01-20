#include "dictionary.h"

dictionary::~dictionary() {
	map<string, symbol*>::iterator loc_s;
	//map<string, ast*>::iterator loc_a;
	for (loc_s = symbol_table.begin(); loc_s!= symbol_table.end(); loc_s++) {
		delete loc_s->second;
	}
	//for (loc_a = ast_map.begin(); loc_a!= ast_map.end(); loc_a++) {
	//	delete loc_a->second;
	//}
	symbol_table.clear();

	add(new symbol("+", sfunction, 2));
	add(new symbol("-", sfunction, 2));
	add(new symbol("*", sfunction, 2));
	add(new symbol("/", sfunction, 2));

	add(new symbol("&&", connective));
	add(new symbol("||", connective));
	add(new symbol("~", connective, 1));
	add(new symbol("->", connective, 2));

	add(new symbol(">", relation, 2));
	add(new symbol("<", relation, 2));
	add(new symbol(">=", relation, 2));
	add(new symbol("<=", relation, 2));
	add(new symbol("=", relation, 2));

	add(new symbol("(", aux, 0));
	add(new symbol(")", aux, 0));
	add(new symbol(" ", aux, 0));
	add(new symbol("\t", aux, 0));

	add(new symbol("d/dt", sfunction, 1));
}

symbol* dictionary::locate_symbol(string name) {
	map<string, symbol*>::iterator	loc;
	loc = symbol_table.find(name);
	if (loc!=symbol_table.end()) 
		return loc -> second;
	else 
		return NULL;
}