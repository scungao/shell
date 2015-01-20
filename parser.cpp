#include <iostream>
#include "parser.h"
#include <regex>

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
	new_process = symbol_table -> locate_symbol(name);
	if ( new_process != NULL ) { //variable has been declared
		new_process -> set_stype(label);
		new_process -> set_dtype(undef);
		message << "Symbol redeclared: ";
	}
	else {
		new_process = new symbol(name, label, 1);//1 is arity 
		symbol_table -> add(new_process);
		message << "New process: ";
	}	
	message << name;

	root = new ast(new_process);
	symbol_table -> add_ast(new_process, root); //add ast to ast table

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

	ast* child = new ast();
	root -> add_child(child);
	message<<collect_body(stream, cc, child);

	return message.str();
}

string parser::collect_body(istream& stream, char& cc, ast* head) { 
	string	buffer;
	string 	numeral;
	vector<symbol*>	token_stream;
	symbol*		token;
	symbol*		token_temp;
	bool	checked;
	stringstream	message; //return message

	do {
		stream.get(cc);

		if ( cc =='\n') continue;

		if (isdigit(cc)) {
			numeral += cc;
			while (regex_match(numeral, 
					regex("[-+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?"))) {
				stream.get(cc); 
			}//at exit, there is one new cc that's not included, so:
			numeral.pop_back();

			symbol* new_numeral = symbol_table->locate_symbol("-");
			if (new_numeral==NULL)
				new_numeral = new symbol(numeral, constant, 0);
			symbol_table -> add(new_numeral);
			token_stream.push_back(new_numeral);
			numeral.clear();
		}
		else if (cc == '-') { //minus sign case
			do {
				stream.get(cc);
			} while (cc==' '); //shouldn't have other spaces

			if (!numeral.empty()) //"-" can only be at the beginning, avoids "--"
				return "Error in numeral declaration";

			if (!isdigit(cc)) {
				token_stream.push_back(symbol_table->locate_symbol("-"));
				if (cc == '-')
					numeral += cc;
			}
			else {
				numeral += cc;
				continue;
			}
		}				

		buffer+= cc; //not that the residue cc from numeral test is taken over
		token = symbol_table->locate_symbol(buffer);

		if (token!= NULL) { //partial match, check if it's full
			stream.get(cc); //look ahead
			string temp = buffer;
			temp += cc;
			token_temp = symbol_table->locate_symbol(temp);
			if ( token_temp != NULL) { //still partial match possibly
				checked = true; //mark that it has been parsed
				buffer = temp;
				break;
			} 
			else { //matched
				checked = false;
				token_stream.push_back(token);
			}
		}
		else { //no match, check if already matched before
			if (checked) {
				assert(token_temp!=NULL);
				token_stream.push_back(token_temp);
				buffer.clear();
				buffer += cc;
			}
			//no match, and previously no match. keep going
		}
	} while (cc!='\n');

	string read_token_name = token_stream[0]->get_name();

	if ( read_token_name == "end") {	
		return "parsed";
	}
	else if ( read_token_name.compare("if")==0) {
		head -> set_head_symbol(symbol_table->locate_symbol("ite"));

		ast* child1 = parse_formula(token_stream, 1); //offset=1
		head -> add_child(child1);

		ast* child2 = new ast();
		collect_body(stream, cc, child2);
	}
	else if ( read_token_name.compare("else")==0 ) { 
		if (head->get_parent()->get_parent()
				->get_head_name().compare("ite")==0) {
			//normal case: two levels up is ite
			ast* child3 = new ast();
			//go up to the third arm of ite
			head->get_parent()->get_parent()->add_child(child3);
			collect_body(stream, cc, child3);
		}
		else {
			return "Something is wrong"; 
		}			
	}
	else { //add sequence
		if (head->get_head_symbol()->get_name().compare("seq") == 0)
			head = head -> get_parent(); //flatten sequences to one level
		else
			head -> set_head_symbol(symbol_table->locate_symbol("seq"));		

		ast* child1 = parse_assignment(token_stream, 0);
		head -> add_child(child1); //left child

		ast* child2 = new ast();
		head -> add_child(child2); //right child
		collect_body(stream, cc, child2);
	}
	//only proper if ended with end
	return "Not properly defined";
}

ast* parser::parse_assignment(vector<symbol*>& tokens, int offset) {
	ast* head = new ast();
	return head;
} 

ast* parser::parse_formula(vector<symbol*>& tokens, int offset) {
	ast* head = new ast();
	return head;
} 









