#ifndef TESTER_H
#define TESTER_H

#include "converter.h"

class tester {
	table*	symbol_table;
	converter*	local_converter;
public:
	tester(converter*);
	inline ~tester() {}
	void test_printer();
	ast* test_ast1();

};

#endif