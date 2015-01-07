#include "dictionary.h"

dictionary::~dictionary() {
	map<string, symbol*>::iterator loc_s;
	//map<string, ast*>::iterator loc_a;
	for (loc_s = symbol_map.begin(); loc_s!= symbol_map.end(); loc_s++) {
		delete loc_s->second;
	}
	//for (loc_a = ast_map.begin(); loc_a!= ast_map.end(); loc_a++) {
	//	delete loc_a->second;
	//}
	symbol_map.clear();
}

symbol* dictionary::locate_symbol(string name) {
	map<string, symbol*>::iterator	loc;
	loc = symbol_map.find(name);
	if (loc!=symbol_map.end()) 
		return loc -> second;
	else 
		return NULL;
}