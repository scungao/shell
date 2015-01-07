#ifndef AST_H
#define AST_H

#include "node.h"
#include <string>

//this ast is more general than the usual one
class ast {
	bool	terminal;
	node*	parent;
	ast**	children; //array of pointers to ASTs
	unsigned	degree;
	unsigned	height;
	string	flatname; //flattened string of the whole tree
public:
	ast(node*); // terminal leaf
 	ast(node*, ast**, unsigned); 
	ast(node*, ast*); //unary tree
	ast(node*, ast*, ast*); //binary tree
	ast(node*, ast*, ast*, ast*); //ternary tree
	~ast();
	inline node*	get_parent()	{ return parent; }
	inline ast**	get_children()	{ return children; }
	inline unsigned	get_degree()	{ return degree; }
	inline unsigned	get_height()	{ return height; }
	inline bool		is_terminal()	{ return terminal; }
	inline string	get_flatname()	{ return flatname; }
	inline void		set_terminal()	{ terminal = true; }
};

#endif
