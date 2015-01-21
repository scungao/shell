#include <iostream>
#include "tester.h"

using namespace std;

tester::tester(converter* c):
	local_converter(c), symbol_table(c->get_table()) {}

ast* tester::test_ast1() {

	symbol* var_x = new symbol("x", variable, 0);
	symbol_table -> add(var_x);

	//cout<<symbol_table->locate_symbol("x")->get_name();

	symbol* var_y = new symbol("y", variable, 0);
	symbol_table -> add(var_y);

	symbol* c1 = new symbol("2.1312", constant, 0);
	symbol_table -> add(c1);

	//cout<<symbol_table->locate_symbol("y")->get_name();

	ast* test_ast1 = new ast(symbol_table->locate_symbol("and"));

	ast* a_e1 = new ast(symbol_table->locate_symbol("="));
	test_ast1 -> add_child(a_e1);

	ast* a_x1 = new ast(var_x);
	ast* a_y1 = new ast(var_y);

	a_e1 -> add_child(a_x1);
	a_e1 -> add_child(a_y1);

	ast* a_e2 = new ast(symbol_table->locate_symbol("="));
	ast* a_x2 = new ast(var_x);
	ast* a_x3 = new ast(c1);

	test_ast1 -> add_child(a_e2);
	a_e2 -> add_child(a_x2);
	a_e2 -> add_child(a_x3);

	return test_ast1;
}


void tester::test_printer() {
	cout<< test_ast1() -> print_prefix()<<endl;
} 
