#include "converter.h"

ast* copy(ast* source) {
	ast* result = new ast();
	result -> set_head_symbol(source->get_head_symbol());
	result -> set_head_type(source->get_head_type());
	result -> set_parent(source->get_parent());
	result -> set_height(source->get_height());
	set<symbol*>::iterator it;
	for (it = source->get_variables_set()->begin(); 
		 	it!=source->get_variables_set()->end(); it++) {
		result -> add_variable(*it);
	}
	for (it = source->get_parameters_set()->begin(); 
		 	it!=source->get_parameters_set()->end(); it++) {
		result -> add_parameter(*it);
	}
	result -> set_period(source->get_period());
	for (int i=0; i< source->get_degree(); i++)
		result -> add_child(copy(source->get_child(i)));
	return result;
}


ast* converter::process_to_formula(ast* source) {
	return NULL;
	//if sequence
	//if ite, you need to substitue the variables
	//if assignment
}