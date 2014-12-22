#include <iostream>
#include <string>
#include "ast.h"

using namespace std;

inline void test(string s) {
	symbol 	x(s);
	ast		t(x);
	ast*	tp = &t;
	ast*	tpp[1];
	
	tpp[0] = tp;	

	ast		t2(x, tpp, 1);
	ast 	t3(x, &t2);
	ast		t4(x, &t3, &t2);

	cout<<"t2: "<<t2.getflatname()<<endl
		<<"degree: "<<t2.getdegree()<<endl
		<<"height: "<<t2.getheight()<<endl;

	cout<<"t3: "<<t3.getflatname()<<endl
		<<"degree: "<<t3.getdegree()<<endl
		<<"height: "<<t3.getheight()<<endl;
	
	cout<<"t4: "<<t4.getflatname()<<endl
		<<"degree: "<<t4.getdegree()<<endl
		<<"height: "<<t4.getheight()<<endl;
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
	while(true)	{
		cout<<"cal$ ";
		getline(cin, command);
		if (command.compare("quit") == 0) {
			reply("You took a normal exit.");
			break;
		}
		else if (command.find("symbol ") == 0) {
			//seperate types?...
		}
		else if (command.find("function ") == 0
				|| command.find("formula ") ==0
				|| command.find("process ") == 0) {
			command = open2end(command);
		}
		//event handlers 
		test(command);
		reply(command);
	}
	return 0;
}