#include <iostream>
#include "parser.h"

parser::parser(dictionary* d): symbol_table(d) {

}
parser::~parser() {}

string parser::collect_variable(istream& stream, char& cc) {
	string 	name;
	s_type	symbol_type;
	d_type	domain_type;
	symbol*	new_var;	
	string	buffer;
	vector<string>	fields;
	stringstream message; //return message

	do { //collect the fields
		stream.get(cc);
		if ((isalnum(cc)||ispunct(cc))
			 && cc!=',' && cc!='[' && cc!= ']')
			buffer += cc;
		else {
			if (!buffer.empty())
				fields.push_back(buffer);
			buffer.clear();
		}
	} while (cc != '\n');

	if (fields.size() < 2) 
		return "Syntax: variable name type [lb, ub].";

	name = fields[0];
	symbol_type = variable;
	if (fields[1].compare("real") == 0 || fields[1].compare("float") == 0) {
		domain_type = real;
		buffer = "real";
	}	
	else if (fields[1].compare("int") == 0 || fields[1].compare("integer") == 0) {
		domain_type = integer;
		buffer = "integer";
	}
	else if (fields[1].compare("boolean") == 0 || fields[1].compare("bool") == 0) {
		domain_type = boolean;
		buffer = "boolean";
	}
	else
		return "Types: real, int/integer, or bool/boolean.";

	new_var = symbol_table -> locate_symbol(name);
	if ( new_var != NULL ) { //variable has been declared
		new_var -> set_stype(symbol_type);
		new_var -> set_dtype(domain_type);
		message << "Symbol redeclared: ";
	}
	else {
		new_var = new symbol(name, symbol_type, 0); //0 is arity
		symbol_table -> add(new_var);
		message << "New variable: ";
	}	
	message << name << " of type " << buffer;

	if (fields.size() == 2) return message.str();
//	for (int i = 0; i<fields.size(); i++) cout<<" "<<fields[i];
	if (fields.size() == 4) {
		new_var -> set_upper(stod(fields[3]));
		new_var -> set_lower(stod(fields[2]));
		//todo: make sure interval is well-defined
		message << " in range ["<< new_var -> get_lower()
				<< ", " << new_var -> get_upper() <<"]"; 
		return message.str();
	}
	else 
		return "Syntax: variable name type [lb, ub].";
}

string parser::collect_constant(istream& stream, char& cc) {
	return "Todo: constant declaration.";
}

string parser::collect_process(istream& stream, char& cc) {
	string 	name;
	s_type	symbol_type;
	symbol*	new_process;	
	string	buffer;
	vector<string>	fields;
	stringstream	message; //return message
	ast*	root;

	//get head: "process name (dt: 0.1; states: x, y; params: a, b)"
	do {
		stream.get(cc);
		if ( (isalnum(cc)||ispunct(cc)) && cc!=':' && cc!=',' 
						 && cc!= '(' && cc!= ')' && cc!= ';' && cc!= '=')//need symbol table now
			buffer += cc;
		else if (cc == ';') {
			if (!buffer.empty())
				fields.push_back(buffer);
			buffer.clear();
			fields.push_back(";");
		}
		else if (cc == ':' ) {
			if (!buffer.empty())
				fields.push_back(buffer);
			buffer.clear();
			fields.push_back(":");
		}
		else {
			if (!buffer.empty())
				fields.push_back(buffer);
			buffer.clear();
		}
	} while (cc != '\n');
	//fields should be like: name dt 0.1 ; x y ; a

	//for (int i=0; i<fields.size(); i++) cout<<i<<fields[i];//test

	//add in symbol list
	name = fields[0];
	symbol_type = process;
	new_process = symbol_table -> locate_symbol(name);
	if ( new_process != NULL ) { //variable has been declared
		new_process -> set_stype(symbol_type);
		new_process -> set_dtype(undef);
		message << "Symbol redeclared: ";
	}
	else {
		new_process = new symbol(name, symbol_type, 1);//1 is arity 
		symbol_table -> add(new_process);
		message << "New process: ";
	}	
	message << name;

	root = new ast(new_process);
	symbol_table -> add_ast(new_process, root);

	//processing elements in head
	vector<int>	semicolons;
	vector<int> colons;
	for(int i=0; i<fields.size(); i++) {
		if (fields[i].compare(";") == 0) semicolons.push_back(i);
		if (fields[i].compare(":") == 0) colons.push_back(i);		
	}

	//put period, vars, pars into storage
	if (semicolons.size() == 0 && colons.size() == 1) { //only state vars 
		for(int i= colons[0]+1 ; i<fields.size() ; i++) { //after name, before ;
			symbol* var_addr = symbol_table->locate_symbol(fields[i]);
			if (var_addr!=NULL && var_addr->get_stype() == variable)
				root->add_variable(var_addr);
			else 
				return "You have used an undeclared variable. Process not declared.";
		}
	} 
	else if (semicolons.size() == 1 && colons.size() == 2) { //state vars and parameters or period
		string after_first_colon = fields[colons[0]+1];
		if (isdigit(after_first_colon[0])) { //period and state vars
			root -> set_period(stod(after_first_colon));
			for(int i= colons[1]+1 ; i<fields.size() ; i++) { //after name, before ;
				symbol* var_addr = symbol_table->locate_symbol(fields[i]);
				if (var_addr!=NULL && var_addr->get_stype() == variable)
					root->add_variable(var_addr);
				else 
					return "You have used an undeclared variable. Process not declared.";
			}
		}
		else { //state vars and parameters
			for(int i= colons[0]+1 ; i<semicolons[0] ; i++) { //after name, before ;
				symbol* var_addr = symbol_table->locate_symbol(fields[i]);
				if (var_addr!=NULL && var_addr->get_stype() == variable)
					root->add_variable(var_addr);
				else 
					return "You have used an undeclared variable. Process not declared.";
			}
			for(int i= colons[1]+1 ; i<fields.size() ; i++) { //after name, before ;
				symbol* param_addr = symbol_table->locate_symbol(fields[i]);
				if (param_addr!=NULL && param_addr->get_stype() == variable)
					root->add_parameter(param_addr);
				else 
					return "You have used an undeclared parameter. Process not declared.";
			}
		}	
	}
	else if (semicolons.size() == 2 && colons.size() == 3) {//time;states;paras
		string after_first_colon = fields[colons[0]+1];
		root -> set_period(stod(after_first_colon));
		for(int i= colons[1]+1 ; i<semicolons[1] ; i++) { //after name, before ;
			symbol* var_addr = symbol_table->locate_symbol(fields[i]);
			if (var_addr!=NULL && var_addr->get_stype() == variable)
				root->add_variable(var_addr);
			else 
				return "You have used an undeclared variable. Process not declared.";
		}
		for(int i= colons[2]+1 ; i<fields.size() ; i++) { //after name, before ;
			symbol* param_addr = symbol_table->locate_symbol(fields[i]);
			if (param_addr!=NULL && param_addr->get_stype() == variable)
				root->add_parameter(param_addr);
			else 
				return "You have used an undeclared parameter. Process not declared.";
		}
	}
	else {
		return "Syntax example: process plant (dt = 0.1; states: x,y; params: z)";
	}


	//collect period and variable info

	return message.str();
}

string parser::collect_body(istream& stream, char& cc) {
	int level = 1;
	//get body
	do {
		level -= 1; 
	} while (level > 0);

	return "parsed";
}




