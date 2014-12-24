#include "ast.h"


ast::ast(symbol s)
	:	root(s), terminal(true), 
		degree(0), height(0), leaves(NULL) 
{
	try{
		flatname = s.get_name();
	}
	catch(exception& e){
		cerr<<"AST: error on base. "<<e.what()<<endl;
	}
}

ast::ast(symbol s, ast** l_array, unsigned d)
	:	root(s), terminal(false), degree(d), leaves(l_array)
{
	try{
		flatname = s.get_name();
	}
	catch(exception& e){
		cerr<<"AST: error on n-ary induction. "
			<<e.what()<<endl;
	}
	flatname += "(";
	height = 0;
	for (int i=0; i<d; i++) {
		if ( l_array[i]->height > height ) 
			height = l_array[i]->height;
		flatname += l_array[i]->flatname;
		flatname += ",";
	}
	flatname.pop_back(); //delete trailing ","
	flatname += ")";
	height += 1;

}

ast::ast(symbol s, ast* l)
	:	root(s), terminal(false), degree(1) 
{
	try{
		flatname = s.get_name();
	}
	catch(exception& e){
		cerr<<"AST: error on unary induction. "
			<<e.what()<<endl;
	}

	ast*	l_array[1];
	l_array[0] = l;
	leaves = l_array;

	flatname += "(";
	flatname += l_array[0]->flatname;
	flatname += ")";

	height = (l_array[0]->height)+1;
}


ast::ast(symbol s, ast* l1, ast* l2)
	:	root(s), terminal(false), degree(2) 
{
	try{
		flatname = s.get_name();
	}
	catch(exception& e){
		cerr<<"AST: error on binary induction. "
			<<e.what()<<endl;
	}

	ast*	l_array[2];
	l_array[0] = l1;
	l_array[1] = l2;
	leaves = l_array;

	flatname += "(";
	height = 0;
	for (int i=0; i<2; i++) {
		if ( l_array[i]->height > height ) 
			height = l_array[i]->height;
		flatname += l_array[i]->flatname;
		flatname += ",";
	}
	flatname.pop_back(); //delete trailing ","
	flatname += ")";
	height += 1;
}

ast::ast(symbol s, ast* l1, ast* l2, ast* l3)
	:	root(s), terminal(false), degree(3) 
{
	try{
		flatname = s.get_name();
	}
	catch(exception& e){
		cerr<<"AST: error on ternary induction. "
			<<e.what()<<endl;
	}

	ast*	l_array[3];
	l_array[0] = l1;
	l_array[1] = l2;
	l_array[2] = l3;

	leaves = l_array;

	flatname += "(";
	height = 0;
	for (int i=0; i<3; i++) {
		if ( l_array[i]->height > height ) 
			height = l_array[i]->height;
		flatname += l_array[i]->flatname;
		flatname += ",";
	}
	flatname.pop_back(); //delete trailing ","
	flatname += ")";
	height += 1;
}

ast::~ast() 
{
}