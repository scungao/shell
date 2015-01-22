#ifndef AST_H
#define AST_H

#include "symbol.h"
#include <string>
#include <vector>
#include <set>

//ast type
enum a_type {
	term,
	formula,
	statement,
	process
};

//this ast is more general than the usual one
class ast {
	bool	terminal;
	a_type	head_type;
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
	inline void set_head_type(a_type a) {head_type = a;}
	inline a_type get_head_type() { return head_type; }
	inline symbol*	get_head_symbol()	{ return head_symbol; }
	inline string	get_head_name()	
		{ return head_symbol->get_name(); }
	inline void 	set_head_symbol(symbol* s) 
		{ head_symbol = s; } 
	inline ast* 	get_child(int i)	{ return children[i]; }
	void		add_child(ast*);
	inline int	get_degree()	{ return children.size(); }
	//inline void set_degree(int d) { degree=d; }
	inline int	get_height()	{ return height; }
	inline void set_height(int h) { height=h; }
	inline bool		is_terminal()	{ return terminal; }
	inline string	get_flatname()	{ return flatname; }
	inline void		set_terminal()	{ terminal = true; }
	inline double	get_period()	{ return period; }
	inline void 	set_period(double p)	{ period = p; }
	inline void	add_variable(symbol* v) { variables.insert(v); }
	inline void	add_parameter(symbol* p) { variables.insert(p); }
	inline set<symbol*>* get_variables_set() { return &variables; }
	inline set<symbol*>* get_parameters_set() { return &parameters; }
	inline void set_parent(ast* a) { parent = a; }
	inline ast* get_parent() { return parent;}
	inline void set_upper(double a) {head_symbol->set_upper(a);}
	inline void set_lower(double a) {head_symbol->set_lower(a);}
	inline void set_bounds(double a, double b) {
		head_symbol->set_upper(b); head_symbol->set_lower(a);
	}
	void normalize();

	string print_tree();
	string print_prefix();
	string print_smt2(bool);

};

#endif
