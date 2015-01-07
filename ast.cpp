#include "ast.h"
#include <iostream>
#include <string>

using namespace std;

ast::ast(node* s)
	:	parent(s), terminal(true), 
		degree(0), height(0), children(NULL) 
{
	try{
		flatname = s -> get_name();
	}
	catch(exception& e){
		cout<<"AST: error on base. "<<e.what()<<endl;
	}
}

ast::ast(node* s, ast** l_array, unsigned d)
	:	parent(s), terminal(false), degree(d), children(l_array)
{		
	flatname = s->get_name();
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

ast::ast(node* s, ast* l)
	:	parent(s), terminal(false), degree(1) 
{
	flatname = s->get_name();

	ast*	l_array[1];
	l_array[0] = l;

	children = l_array;

	flatname += "(";
	flatname += l_array[0]->flatname;
	flatname += ")";

	height = (l_array[0]->height)+1;
}


ast::ast(node* s, ast* l1, ast* l2)
	:	parent(s), terminal(false), degree(2) 
{
	flatname = s->get_name();

	ast*	l_array[2];
	l_array[0] = l1;
	l_array[1] = l2;

	children = l_array;

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

ast::ast(node* s, ast* l1, ast* l2, ast* l3)
	:	parent(s), terminal(false), degree(3) 
{
	flatname = s->get_name();
	
	ast*	l_array[3];
	l_array[0] = l1;
	l_array[1] = l2;
	l_array[2] = l3;

	children = l_array;

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