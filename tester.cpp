#include <iostream>
#include "tester.h"

using namespace std;

tester::tester(table* st):
	symbol_table(st), converter(st) {}

ast* tester::test_ast1() {

	symbol* var_x = new symbol("x", variable, 0);
	symbol* c1 = new symbol("2.1312", constant, 0);
	symbol* var_y = new symbol("y", variable, 0);
	symbol* par_a = new symbol("a", parameter, 0);

	symbol_table -> add(var_x);
	symbol_table -> add(var_y);
	symbol_table -> add(c1);

	ast* test_ast1 = new ast(symbol_table->locate_symbol("and"));
	ast* a_e2 = new ast(symbol_table->locate_symbol("="));
	ast* a_x1 = new ast(var_x);
	ast* a_y1 = new ast(var_y);
	ast* a_x2 = new ast(par_a);
	ast* a_x3 = new ast(c1);

	ast* a_e1 = eq(a_x1, a_y1);

	test_ast1 -> add_child(a_e1);
	test_ast1 -> add_child(a_e2);

	a_e2 -> add_child(a_x2);
	a_e2 -> add_child(a_x3);

	return test_ast1;
}

ast* tester::test_ast2() { 

//the four labels of functions
	symbol* lf[5]; //just to make the index clear
	lf[1] = new symbol("f1", label, 1);
	lf[2] = new symbol("f2", label, 1);
	lf[3] = new symbol("f3", label, 1);
	lf[4] = new symbol("f4", label, 1);

	ast* m = num("1.0");
	ast* M = num("2.0");
	ast* L = num("1.0");
	ast* g = num("9.8");
	ast* c2 = num("2");
	ast* c0 = num("0");


//the four variables
	ast* x1 = var("x");
	x1 -> set_bounds(-10, 10);

	ast* x2 = var("xd");
	x2 -> set_bounds(-10, 10);

	ast* x3 = var("theta");
	x3 -> set_bounds(-10, 10);

	ast* x4 = var("thetad");
	x4 -> set_bounds(-10, 10);

	ast* u = param("u");
	u -> set_bounds(-10, 10);

//define the functions
	ast* f[5]; 

	//f1
	f[1] = x2;

	//f2
	ast* term21 = mul(mul(mul(m,L),sin(x3)),pow(x4,c2));
	ast* term22 = mul(m, mul(g, mul( cos(x3), sin(x3))));
	ast* term23 = add(mul(m, pow(sin(x3), c2)), M);
	f[2] = div(add(add(term21,term22),u),term23);

	//f3
	f[3] = x4;

	//f4
	ast* term41 = mul(mul(mul(mul(m,L),sin(x3)),cos(x3)),pow(x4,c2));
	ast* term42 = mul(mul(add(m,M),g),sin(x3));
	ast* term43 = mul(cos(x3),u);
	ast* term44 = mul(sub(c0,L),add(mul(m,pow(sin(x3),c2)),M));
	f[4] = div(add(add(term41,term42),term43),term44);

	ast* formula1 = land(land(eq(f[3],c0),land(eq(f[1],c0),eq(f[2],c0))),eq(f[4],c0));
	ast* formula2 = dup(formula1);
	return formula2;
}

void tester::testall() {
	//cout<< test_ast1()->print_prefix()<<endl;
	//cout<<test_ast2()->print_tree();
	cout<< test_ast2()->print_smt2(true)<<endl;
} 
