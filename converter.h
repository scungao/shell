#ifndef CONVERTER_H
#define CONVERTER_H

#include "table.h"

class converter {
	ast*	source;
	table*	local_table;
public:
	inline converter(table* t):
		local_table(t) {}
	inline ~converter() {}
	inline table*	get_table() {return local_table;}
	string substitute(ast*, ast*, symbol*, symbol*); //substitute symbol by symbol
	string substitute(ast*, ast*, symbol*, ast*); //substitute symbol by ast
	ast*	process_to_formula(ast*);
	ast*	copy(ast*);	
};


#endif