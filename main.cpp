#include <iostream>
#include <string>
#include "parser.h"
#include "ast.h"

using namespace std;

inline void test(string s) {
	symbol* 	x = new symbol(s);
	ast*		t = new ast(*x);
	ast*		tpp[1];
	tpp[0] = t;	

	ast*	t2 = new ast(*x, tpp, 1);
	ast* 	t3 = new ast(*x, t2);
	ast*	t4 = new ast(*x, t3, t2);

	cout<<"t2: "<<t2 -> get_flatname()<<endl
		<<"degree: "<<t2 -> get_degree()<<endl
		<<"height: "<<t2 -> get_height()<<endl;

	cout<<"t3: "<<t3 -> get_flatname()<<endl
		<<"degree: "<<t3 -> get_degree()<<endl
		<<"height: "<<t3 -> get_height()<<endl;
	
	cout<<"t4: "<<t4 -> get_flatname()<<endl
		<<"degree: "<<t4 -> get_degree()<<endl
		<<"height: "<<t4 -> get_height()<<endl;
}

inline void reply(string s) {
	//"\033[36m" makes it light blue
	cout<<"\033[36m"<<s<<"\033[0m"<<"\n";
}

inline string open2end(string s) {
	string buffer = s;
	buffer += "{";
		while(s.compare("end") != 0) {
			cout << "     ";
			getline(cin, s);
			if (s.compare("end") != 0) {
				buffer += s;
				buffer += ";";
			}
		}
	buffer += "}";
	return buffer;
}

int main() {

	string command;
	parser global_parser;

	while(true)	{
		cout<<"cal$ ";
		getline(cin, command);
		if ( command.compare("quit") == 0 ) {
			reply("You took a normal exit.");
			break;
		}
		else if ( command.find("symbol ") == 0 ) {
			string symbol_name = command.substr(7);
			symbol s(symbol_name);
			global_parser.add_symbol(s);
		}
		else if ( command.find("function ") == 0 ) {

		}
		else if ( command.find("formula ") == 0 ){

		}
		else if ( command.find("process ") == 0 ) {
			command = open2end(command);
		}
		else if ( command.find("solve ") == 0 ) {

		}
		else if ( command.find("implement ") == 0) {

		}
		else if ( command.find("simulate ") == 0){
			
		}
		else { 

		}

		//event handlers 
		test(command);
		cout<<global_parser.symbol_list_size()<<endl;
		reply(command);
	}

	return 0;
}