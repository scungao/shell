#include "converter.h"

ast* converter::dup(ast* source) {
	ast* result = new ast();
	result -> set_head_symbol(source->get_head_symbol());
	result -> set_parent(source->get_parent());
	result -> set_height(source->get_height());
	result -> set_period(source->get_period());
	for (int i=0; i< source->get_degree(); i++)
		result -> add_child(dup(source->get_child(i)));
	return result;
}

ast* converter::copy_replace(ast* source, symbol* old, symbol* neo) {
	ast* result = dup(source);
	replace(result, old, neo);
	return result;
}

ast* converter::copy_replace(ast* source, ast* old, ast* neo) {
	ast* result = dup(source);
	replace(result, old, neo);
	return result;
}

ast* converter::replace(ast* source, symbol* old, symbol* neo) {
	if (source->get_head_symbol() == old)
		source -> set_head_symbol(neo);
	for(int i=0; i<source->get_degree(); i++)
		replace(source->get_child(i), old, neo);
	return source;
}

ast* converter::replace(ast* source, ast* old, ast* neo) {
	if (source->get_head_symbol() == old->get_head_symbol())
		source = old;
	if (source!=NULL) {
		for(int i=0; i<source->get_degree(); i++)
			replace(source->get_child(i), old, neo);
	}
	return source;
}