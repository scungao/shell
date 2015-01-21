#include <iostream>
#include <sstream>
#include <string>
#include <cctype>
#include "converter.h"
#include "tester.h"
#include "parser.h"

using namespace std;

inline void reply(string s) { cout<<"\033[36m"<<s<<"."<<"\033[0m"<<"\n"; }

int main() {
	table	full_table;
	converter global_converter(&full_table);
	parser 	main_parser(&full_table);
	tester	test_suite(&full_table);

	test_suite.test_printer();

/*
	char current_char;
	string command;

	cout<<"\033[36m"<<"cda$ "<<"\033[0m";
	cin.get(current_char);

	while (current_char != EOF) {

		if (current_char != '\n')
			command += current_char;
		else {
			command.clear();
			cout<<"\033[36m"<<"cda$ "<<"\033[0m";
		}

		if ( command.compare("quit") == 0 || command.compare("exit") == 0 
				|| command.compare("bye") ==0 ) {
			break;
		}
		else if ( command.compare("variable") == 0 ) {
			reply(main_parser.collect_variable(cin, current_char));
			continue; //avoids getchar at the bottom of the loop
		}
		else if ( command.compare("constant") == 0 ) {
			reply(main_parser.collect_constant(cin, current_char));
			continue;
		}
		else if ( command.compare("process") == 0 ) {
			reply(main_parser.collect_process(cin, current_char));
			continue;
		}
		else if ( command.compare("formula") == 0 ) {
			//main_parser.collect_head(command);
			//main_parser.collect_body(cin);
			reply("");
		}
		else if ( command.compare("solve") == 0 ) {
			//main_solver.run(command);
		}		
		else if (command.find("simulate") == 0 ) {} 
		else if ( command.compare("savework") == 0) {
			//save everything to file
		}
		else if ( command.compare("ls") == 0 || command.compare("clear") == 0) {
			system(command.c_str());
		}
		else {
			//errors
		}
		cin.get(current_char);
	}

	reply("Normal exit");
*/
	return 0;
}


