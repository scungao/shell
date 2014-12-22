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
	inline symbol	getroot() 		{ return root; }
	inline ast**	getleaves() 	{ return leaves; }
	inline unsigned	getdegree()		{ return degree; }
	inline unsigned	getheight()		{ return height; }
	inline bool		isterminal() 	{ return terminal; }
	inline string	getflatname()	{ return flatname; }

	inline void	setterminal()	{ terminal = true; }
};

#endif
