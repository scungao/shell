#ifndef AST_H
#define AST_H

#include "symbol.h"
#include <string>

class ast {
public:
	ast(symbol); // terminal leaf
 	ast(symbol, ast**, unsigned); //root, leaves, degree

 	//common shorthands
	ast(symbol, ast*); //unary tree
	ast(symbol, ast*, ast*); //binary tree
	ast(symbol, ast*, ast*, ast*); //ternary tree

	~ast();

private:
	bool	terminal;
	symbol	root;
	ast**	leaves; //array of pointers to ASTs
	unsigned	degree;
	unsigned	height;
	string	flatname; //flattened string of the whole tree

public:
	inline symbol	get_root()	{ return root; }
	inline ast**	get_leaves()	{ return leaves; }
	inline unsigned	get_degree()	{ return degree; }
	inline unsigned	get_height()	{ return height; }
	inline bool		is_terminal()	{ return terminal; }
	inline string	get_flatname()	{ return flatname; }

	inline void	setterminal()	{ terminal = true; }
};

#endif
