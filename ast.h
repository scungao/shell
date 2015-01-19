#ifndef AST_H
#define AST_H

#include "symbol.h"
#include <string>
#include <vector>
#include <set>

//this ast is more general than the usual one
class ast {
	bool	terminal;
	symbol*		head_symbol;
	ast*		parent;
	vector<ast*>		children; //array of pointers to ASTs
	int	degree; //branching degree of head_symbol
	int	height;
	string	flatname; //flattened string of the whole tree
	set<symbol*>		variables;	//variables used anywhere downwards
	set<symbol*>		parameters;	//parameters used anywhere downwards
	double	period; //for process
public:
	inline ast() {}
	ast(symbol*); // terminal leaf
	ast(symbol*, ast*); //unary tree
	ast(symbol*, ast*, ast*); //binary tree
	ast(symbol*, ast*, ast*, ast*); //ternary tree
	~ast();
	inline symbol*	get_head_symbol()	{ return head_symbol; }
	inline string	get_head_name()	
		{ return head_symbol->get_name(); }
	inline void 	set_head_symbol(symbol* s) 
		{ head_symbol = s; } 
	inline ast* 	get_child(int i)	{ return children[i]; }
	inline void		add_child(ast* a)	
		{ children.push_back(a); a->set_parent(this); degree++; }
	inline int	get_degree()	{ return degree; }
	inline int	get_height()	{ return height; }
	inline bool		is_terminal()	{ return terminal; }
	inline string	get_flatname()	{ return flatname; }
	inline void		set_terminal()	{ terminal = true; }
	inline void 	set_period(double p)	{ period = p; }
	inline void	add_variable(symbol* v) { variables.insert(v); }
	inline void	add_parameter(symbol* p) { variables.insert(p); }
	inline void set_parent(ast* a) { parent = a; }
	inline ast* get_parent()	
		{ assert(parent!=NULL); return parent;}
};

#endif
