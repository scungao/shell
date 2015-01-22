#ifndef CONVERTER_H
#define CONVERTER_H

#include "table.h"

class converter {
	table*	symbol_table;
public:
	inline converter(table* t):
		symbol_table(t) {}
	inline ~converter() {}
	inline table*	get_table() {return symbol_table;}
	string substitute(ast*, ast*, symbol*, symbol*); //substitute symbol by symbol
	string substitute(ast*, ast*, symbol*, ast*); //substitute symbol by ast
	ast*	process_to_formula(ast*);
	ast*	copy(ast*);	

	inline ast*	add(ast* a1, ast* a2) { 
		ast* result = new ast(symbol_table->locate_symbol("+")); 
		result -> add_child(a1);
		result -> add_child(a2);
		return result;
	}

	inline ast*	sub(ast* a1, ast* a2) { 
		ast* result = new ast(symbol_table->locate_symbol("-")); 
		result -> add_child(a1);
		result -> add_child(a2);
		return result;
	}

	inline ast*	mul(ast* a1, ast* a2) { 
		ast* result = new ast(symbol_table->locate_symbol("*")); 
		result -> add_child(a1);
		result -> add_child(a2);
		return result;
	}
	
	inline ast*	div(ast* a1, ast* a2) { 
		ast* result = new ast(symbol_table->locate_symbol("/")); 
		result -> add_child(a1);
		result -> add_child(a2);
		return result;
	}

	inline ast*	sqrt(ast* a1) { 
		ast* result = new ast(symbol_table->locate_symbol("sqrt")); 
		result -> add_child(a1);
		return result;
	}

	inline ast*	sin(ast* a1) { 
		ast* result = new ast(symbol_table->locate_symbol("sin")); 
		result -> add_child(a1);
		return result;
	}	

	inline ast*	cos(ast* a1) { 
		ast* result = new ast(symbol_table->locate_symbol("cos")); 
		result -> add_child(a1);
		return result;
	}

	inline ast*	tan(ast* a1) { 
		ast* result = new ast(symbol_table->locate_symbol("tan")); 
		result -> add_child(a1);
		return result;
	}	

	inline ast*	pow(ast* a1, ast* a2) { 
		ast* result = new ast(symbol_table->locate_symbol("^")); 
		result -> add_child(a1);
		result -> add_child(a2);
		return result;
	}

	inline ast* gt(ast* a1, ast* a2) {
		ast* result = new ast(symbol_table->locate_symbol(">"));
		result -> add_child(a1);
		result -> add_child(a2);
		return result;
	} 

	inline ast* lt(ast* a1, ast* a2) {
		ast* result = new ast(symbol_table->locate_symbol("<"));
		result -> add_child(a1);
		result -> add_child(a2);
		return result;
	} 


	inline ast* geq(ast* a1, ast* a2) {
		ast* result = new ast(symbol_table->locate_symbol(">="));
		result -> add_child(a1);
		result -> add_child(a2);
		return result;
	} 

	inline ast* leq(ast* a1, ast* a2) {
		ast* result = new ast(symbol_table->locate_symbol("<="));
		result -> add_child(a1);
		result -> add_child(a2);
		return result;
	} 

	inline ast* eq(ast* a1, ast* a2) {
		ast* result = new ast(symbol_table->locate_symbol("="));
		result -> add_child(a1);
		result -> add_child(a2);
		return result;
	} 

	inline ast*	lnot(ast* a1) { 
		ast* result = new ast(symbol_table->locate_symbol("not")); 
		result -> add_child(a1);
		return result;
	}

	inline ast* land(ast* a1, ast* a2) {
		ast* result = new ast(symbol_table->locate_symbol("and"));
		result -> add_child(a1);
		result -> add_child(a2);
		return result;
	} 

	inline ast* lor(ast* a1, ast* a2) {
		ast* result = new ast(symbol_table->locate_symbol("or"));
		result -> add_child(a1);
		result -> add_child(a2);
		return result;
	} 

	inline ast* limplies(ast* a1, ast* a2) {
		ast* result = new ast(symbol_table->locate_symbol("implies"));
		result -> add_child(a1);
		result -> add_child(a2);
		return result;
	} 

	inline ast* num(string s) {
		symbol* new_num = symbol_table->locate_symbol(s);
		if (new_num == NULL){ 
			new_num = new symbol(s, constant, 0);
			symbol_table -> add(new_num);
		}
		ast* a = new ast(new_num);
		return a;
	}

	inline ast* var(string s) {
		symbol* new_var = symbol_table->locate_symbol(s);
		if (new_var == NULL) {
			new_var = new symbol(s, variable, 0);
			symbol_table -> add(new_var);
		}
		ast* a = new ast(new_var);
		return a;
	}

	inline ast* param(string s) {
		symbol* new_param = symbol_table->locate_symbol(s);
		if (new_param == NULL) {
			new_param = new symbol(s, parameter, 0);
			symbol_table -> add(new_param);
		}
		ast* a = new ast(new_param);
		return a;
	}





};


#endif