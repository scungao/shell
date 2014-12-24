#include "parser.h"

parser::parser() : symbol_list_string("") {
	//add basic symbol list
}
parser::~parser() {}

void parser::add_symbol(symbol s) {
	for (int i =0; i<symbol_list.size(); i++) {
		string old_name = symbol_list[i].get_name();
		string new_name = s.get_name();
		//cout<<"old"<<old_name<<"new"<<new_name;
		if ( new_name.compare(old_name) ==0 ) {
			cout<<"symbol "<< new_name
				<<" has been declared before"<<endl;
			return;
		}
	}
	symbol_list.push_back(s);
	symbol_list_string += s.get_name();
}

//ast* parser::parse(string s) {}
