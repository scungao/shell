#ifndef TESTER_H
#define TESTER_H

#include "converter.h"

class tester : public converter {
	table* symbol_table;
public:
	tester(table*);
	inline ~tester() {}
	void testall();
	ast* test_ast1();
	ast* test_ast2();
};

#endif