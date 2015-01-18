#ifndef AST_H
#define AST_H

#include "symbol.h"
#include <string>
#include <vector>

//this ast is more general than the usual one
class ast {
	bool	terminal;
	symbol*		parent;
	ast**		children; //array of pointers to ASTs
	unsigned	degree;
	unsigned	height;
	string	flatname; //flattened string of the whole tree
	vector<symbol*>		variables;	//variables used anywhere downwards
	vector<symbol*>		parameters;	//parameters used anywhere downwards
public:
	ast(symbol*); // terminal leaf
 	ast(symbol*, ast**, unsigned); 
	ast(symbol*, ast*); //unary tree
	ast(symbol*, ast*, ast*); //binary tree
	ast(symbol*, ast*, ast*, ast*); //ternary tree
	~ast();
	inline symbol*	get_parent()	{ return parent; }
//	inline vector<ast*> *	get_children()	{ return &children; }
	inline ast* 	get_child(int i)	{ return children[i]; }
	inline unsigned	get_degree()	{ return degree; }
	inline unsigned	get_height()	{ return height; }
	inline bool		is_terminal()	{ return terminal; }
	inline string	get_flatname()	{ return flatname; }
	inline void		set_terminal()	{ terminal = true; }
};

#endif
