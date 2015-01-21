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
/*inverted pendulum	
A = [0      1              0           0;
     0 -(I+m*l^2)*b/p  (m^2*g*l^2)/p   0;
     0      0              0           1;
     0 -(m*l*b)/p       m*g*l*(M+m)/p  0];
B = [     0;
     (I+m*l^2)/p;
          0;
        m*l/p];
*/

//the four labels of functions
	symbol* lf[4];
	lf[0] = new symbol("f1", label, 1);
	lf[1] = new symbol("f2", label, 1);
	lf[2] = new symbol("f3", label, 1);
	lf[3] = new symbol("f4", label, 1);

//the four variables
	symbol*	vars[4];
	vars[0] = new symbol("x", variable, 0);
	vars[1] = new symbol("dx", variable, 0);
	vars[2] = new symbol("theta", variable, 0);
	vars[3] = new symbol("thetad", variable, 0);

//define the functions
	ast* f[4];
	ast* x[4];

	for(int i=0; i<4; i++) {
		f[i] = new ast(lf[i]);
		x[i] = new ast(vars[i]);
	}

	return NULL;
}



void tester::test_printer() {
	cout<< test_ast1()->print_prefix()<<endl;
} 
