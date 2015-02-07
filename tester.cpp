#include <iostream>
#include "tester.h"
#include "power.h"

using namespace std;

tester::tester(table* st):
	symbol_table(st), converter(st) {}

void tester::powertest(){
	//double b[5][5];
	//double g[5][5];
	power_grid	grid(symbol_table, 3);
//	grid.add_line(1,2);
	grid.add_line(0,1);
	grid.add_line(1,2);

//	ast* f1 = grid.est();
	ast* f1 = land(grid.mf(),grid.attack());
	f1 = land(f1, grid.monitor(0.5));
	f1 = land(f1, grid.esth());
	f1 = land(f1, grid.unsafe(5));

	cout<<f1->print_smt2(true)<<endl;	
	map<symbol*, symbol*>	sol;
	get_dreal_solutions(f1,sol,true);
//	cout<< grid.p(1) -> print_infix() <<endl ;
//	cout<< grid.q(1) -> print_infix() <<endl ;
}


void tester::powertest2(){
	//double b[5][5];
	//double g[5][5];
	power_grid	grid(symbol_table, 20);
	grid.add_line(1,2);
	grid.add_line(0,1);
	grid.add_line(0,2);
	grid.add_line(5,7);
	grid.add_line(9,4);
	grid.add_line(6,3);
	grid.add_line(2,8);

	ast* f1 = land(grid.mf(),grid.attack());
	f1 = land(f1, grid.monitor(0.5));
	f1 = land(f1, grid.esth());
	f1 = land(f1, grid.unsafe(5));

	cout<<f1->print_smt2(true)<<endl;	
	map<symbol*, symbol*>	sol;
	get_dreal_solutions(f1,sol,true);
//	cout<< grid.p(1) -> print_infix() <<endl ;
//	cout<< grid.q(1) -> print_infix() <<endl ;
}

void tester::powertest3(){
	//double b[5][5];
	//double g[5][5];
	power_grid	grid(symbol_table, 100);
	grid.add_line(1,2);
	grid.add_line(0,1);
	grid.add_line(0,2);
	grid.add_line(5,7);
	grid.add_line(9,4);
	grid.add_line(6,3);
	grid.add_line(2,8);
	grid.add_line(5,10);
	grid.add_line(10,70);

	ast* f1 = land(grid.mf(),grid.est());

	cout<<f1->print_smt2(true)<<endl;
	
	map<symbol*, symbol*>	sol;
	get_dreal_solutions(f1,sol,true);
//	cout<< grid.p(1) -> print_infix() <<endl ;
//	cout<< grid.q(1) -> print_infix() <<endl ;
}


ast* tester::test_ast1() {

	symbol* var_x = new symbol("x", variable, 0);
	symbol* c1 = new symbol("2.1312", constant, 0);
	symbol* var_y = new symbol("y", variable, 0);
	symbol* par_a = new symbol("a", parameter, 0);

	symbol_table -> add(var_x);
	symbol_table -> add(var_y);
	symbol_table -> add(c1);

	ast* test_ast1 = new ast(symbol_table->locate_symbol("and"));
	ast* a_e2 = new ast(symbol_table->locate_symbol("="));
	ast* a_x1 = new ast(var_x);
	ast* a_y1 = new ast(var_y);
	ast* a_x2 = new ast(par_a);
	ast* a_x3 = new ast(c1);

	ast* a_e1 = eq(a_x1, a_y1);

	test_ast1 -> add_child(a_e1);
	test_ast1 -> add_child(a_e2);

	a_e2 -> add_child(a_x2);
	a_e2 -> add_child(a_x3);

	return test_ast1;
}

void tester::test_ast2() { 

//the four labels of functions
	symbol* lf[5]; //just to make the index clear
	lf[1] = new symbol("f1", label, 1);
	lf[2] = new symbol("f2", label, 1);
	lf[3] = new symbol("f3", label, 1);
	lf[4] = new symbol("f4", label, 1);

	ast* m = num("1.0");
	ast* M = num("2.0");
	ast* L = num("1.0");
	ast* g = num("9.8");
	ast* c2 = num("2");
	ast* c0 = num("0");

	vector<ast*> x;

//the four variables
	ast* x1 = var("x");
	x1 -> set_bounds(-10, 10);

	ast* x2 = var("xd");
	x2 -> set_bounds(-10, 10);

	ast* x3 = var("theta");
	x3 -> set_bounds(-4, 4);

	ast* x4 = var("thetad");
	x4 -> set_bounds(-10, 10);

	ast* u = param("u");
	u -> set_bounds(-10, 10);

	x.push_back(x1);
	x.push_back(x2);
	x.push_back(x3);
	x.push_back(x4);


//define the functions
	vector<ast*> f; 

	//f1
	 f.push_back(x2);

	//f2
	ast* term21 = mul(mul(mul(m,L),sin(x3)),pow(x4,c2));
	ast* term22 = mul(m, mul(g, mul( cos(x3), sin(x3))));
	ast* term23 = add(mul(m, pow(sin(x3), c2)), M);
	f.push_back( div(add(add(term21,term22),u),term23) );

	//f3
	f.push_back( x4 );

	//f4
	ast* term41 = mul(mul(mul(mul(m,L),sin(x3)),cos(x3)),pow(x4,c2));
	ast* term42 = mul(mul(add(m,M),g),sin(x3));
	ast* term43 = mul(cos(x3),u);
	ast* term44 = mul(sub(c0,L),add(mul(m,pow(sin(x3),c2)),M));
	f.push_back( div(add(add(term41,term42),term43),term44) );

	ast* formula1 = land(land(eq(f[2],c0),land(eq(f[0],c0),eq(f[1],c0))),eq(f[3],c0));



	ast* formula2 = dup(formula1);
	ast* formula3 = substitute(formula1, symbol_table->locate_symbol("thetad"), 
							symbol_table->locate_symbol("0"));
	ast* formula41 = substitute(x2, x3, m);
	ast* formula4 = add(x2, mul(x3, div(x1, x2)));
//	ast* formula4 = copy_replace(formula1, symbol_table->locate_symbol("xd"), 
//							symbol_table->locate_symbol("1"));

	cout<< formula1 -> print_smt2(true) <<endl;
//	cout<< formula2 -> print_smt2(true) << endl;
	cout<< formula3 -> print_smt2(true) <<endl;
//	cout<< substitute(x2, x2, m) -> print_smt2(true) <<endl;
//	cout<< formula4 -> print_smt2(true) <<endl;

	map<symbol*, symbol*> sol;

	get_dreal_solutions(formula1, sol, true);

	for (map<symbol*, symbol*>::iterator it = sol.begin(); it!=sol.end(); it++)
		formula1 = substitute(formula1, it->first, it->second);

	cout<<"original: "<<formula1 -> print_smt2(true)<<endl;
	simplify(formula1);

	cout<<"simplified: "<<formula1 -> print_smt2(false)<<endl;

	ast* formula5 = partial(formula4, symbol_table->locate_symbol("xd"));
	cout<<"derivative of: "<<formula4 -> print_prefix()<<" is "
		<<formula5 -> print_prefix()<<endl;

	ast* formula6 = div(x2, x3);
	cout << partial(formula6, x2)->print_prefix()<<endl;

	cout<<formula5 -> print_smt2(true)<<endl;

	ast* formula7 = mul(sin(x2),cos(x2));
	cout<< partial(formula7, x2)->print_prefix()<<endl;

	ast* v = x[2];
	ast* lcondition = lyapunov(f, x, v);

	cout<<lcondition->print_smt2(true)<<endl;

	vector<ast*> p;
	p.push_back(u);

	if (cegis(lcondition, x, p, sol, 0.1))
		cout<<"cegis succeeded"<<endl;
	else
		cout<<"cegies found no solution"<<endl;
}

void tester::pwf() {//pendulum with friction
	vector<ast*> x;
	vector<ast*> f;

	ast* m = num("1.0");
//	ast* m = var("m");
	ast* M = num("2.0");
	ast* L = num("1.0");
//	ast* L = var("L");
	ast* g = num("9.8");
//	ast* g = var("g");		
	ast* c2 = num("2");
	ast* c0 = num("0");
	ast* k = num("1.5");
//	ast* k = var("k");

	x.push_back(var("x1"));
	x[0]->set_bounds(-1,1);

	x.push_back(var("x2"));
	x[1]->set_bounds(-1,1);

	f.push_back(x[1]); //f1

	ast* f2part1 = sub(num("0"),mul(div(g,L),sin(x[0])));
	ast* f2part2 = mul(div(k,m),x[1]);
	f.push_back(sub(f2part1,f2part2));//f2

	vector<ast*> p;

	p.push_back(var("a"));
	p[0] -> set_bounds(6,100);

	p.push_back(var("b"));
	p[1] -> set_bounds(5, 200);

	ast* v; //energy function
	v = add(mul(p[0],pow(x[1],num(2))), mul(p[1],sub(num("1"),cos(x[0]))));
//	v = add(mul(p[0],pow(x[1],num(2))), mul(p[1],pow(sub(num("1"),cos(x[0])),num("3"))));


	ast* lcondition = lyapunov(f, x, v);

	map<symbol*, symbol*> sol;

	if (cegis(lcondition, x, p, sol, 0.1)) {
		cout<<"cegis succeeded"<<endl;
	}
	else
		cout<<"cegies found no solution"<<endl;


}


void tester::simple() {
	vector<ast*> x;
	vector<ast*> f;
	vector<ast*> p;
	ast* v;

	x.push_back(var("x"));
	x[0]->set_bounds(-1,1);

	p.push_back(var("a"));
	p[0]->set_bounds(0, 10);

	p.push_back(var("b"));
	p[1]->set_bounds(-5,10);

	f.push_back(sub(
					add(pow(x[0],num("3")),pow(x[0],num("2"))), 
					mul(p[0],x[0])
					)
				);

	v = add(p[1], pow(x[0],num("4")));

	ast* lcondition = lyapunov(f, x, v);

	map<symbol*, symbol*> sol;

	if (cegis(lcondition, x, p, sol, 0.1)) {
		cout<<"cegis succeeded"<<endl;
	}
	else
		cout<<"cegies found no solution"<<endl;


}


void tester::ipc() {
	ast* m = num("1.0");
	ast* M = num("2.0");
	ast* L = num("1.0");
	ast* g = num("9.8");
	ast* c2 = num("2");
	ast* c0 = num("0");

	vector<ast*> x;

//the four variables
	ast* x1 = var("x");
	x1 -> set_bounds(-1.5, 1.5);

	ast* x2 = var("xd");
	x2 -> set_bounds(-1, 1);

	ast* x3 = var("theta");
	x3 -> set_bounds(-0.5, 0.5);

	ast* x4 = var("thetad");
	x4 -> set_bounds(-1, 1);

	x.push_back(x1);
	x.push_back(x2);
	x.push_back(x3);
	x.push_back(x4);

	vector<ast*> p;

	ast* kp = var("kp");
	kp->set_bounds(0,30);

	ast* kl = var("kl");
	kl->set_bounds(0,25);

	ast* ki = var("ki");
	ki->set_bounds(0,20);


	p.push_back(kp);
	p.push_back(kl);
	p.push_back(ki);


	ast* ksi = add(div(x1,L),mul(kp,sin(x3)));
	cout<<"ksi: "<<ksi->print_infix()<<endl;

	ast* delta = div(M,m);

	ast* pksi = add(div(x2,L),mul(mul(kp,x4),cos(x3)));
	cout<<"pksi: "<<pksi->print_infix()<<endl;
	
	
	ast* itax = add(mul(ki,ksi),mul(kp,mul(sin(x3), 
							sub(cos(x3), pow(x4,num(2))) )));
	cout<<"itax: "<<itax->print_infix()<<endl;
		
	ast* deltatheta = sub(add(num(1), kl), mul(kp, pow(cos(x3),num(2))));
	cout<<"deltatheta: "<<deltatheta->print_infix()<<endl;
	

	ast* veta = sub(num(0),
			   div(add(pksi,itax),deltatheta));
	cout<<"veta: "<<veta->print_infix()<<endl;

	ast* u = add(
			sub(mul(cos(x3),sin(x3)),mul(pow(x4,num(2)),sin(x3))),
			mul(veta,add(pow(sin(x3),num(2)),delta))
			);
	simplify(u);
	cout<<"u: "<<u->print_infix()<<endl;

	ast* phix = add(
					sub(mul(kp,sub(num(1),cos(x3))),
						mul(num(0.5),mul(kp,pow(x4,num(2))))),
					mul(num(0.5),pow(div(x2,L),num(2)))
					);
	cout<<"phix: "<<phix->print_infix()<<endl;

	ast* V = add(add(mul(mul(num(0.5),ki),pow(ksi,num(2))),
				 	 mul(num(0.5),pow(pksi,num(2)))),
				 mul(kl, phix)
				);
	cout<<"V: "<<V->print_infix()<<endl;

//define the functions
	vector<ast*> f; 

	//f1
	 f.push_back(x2);

	//f2
	ast* term21 = mul(mul(mul(m,L),sin(x3)),pow(x4,c2));
	ast* term22 = mul(m, mul(g, mul(cos(x3), sin(x3))));
	ast* term23 = add(mul(m, pow(sin(x3), c2)), M);
	f.push_back( div(add(add(term21,sub(num("0"),term22)),u),term23) );
	simplify(f[1]);
	cout<<"f2: "<<f[1]->print_infix()<<endl;

	//f3
	f.push_back( x4 );

	//f4
	ast* term41 = mul(mul(mul(mul(m,L),sin(x3)),cos(x3)),pow(x4,c2));
	ast* term42 = mul(mul(add(m,M),g),sin(x3));
	ast* term43 = mul(cos(x3),u);
	ast* term44 = mul(L,add(mul(m,pow(sin(x3),c2)),M));
	f.push_back(div(add(add(sub(num("0"),term41),term42),sub(num("0"),term43)),term44) );
	simplify(f[3]);
	cout<<"f4: "<<f[3]->print_infix()<<endl;


//	ast* formula1 = land(land(eq(f[2],c0),land(eq(f[0],c0),eq(f[1],c0))),eq(f[3],c0));
//	simplify(formula1);
//	cout<<formula1->print_infix()<<endl;
//	get_dreal_solutions(formula1, sol, true);

	ast* lcondition = lyapunov(f, x, V);
//	ast* lcondition = gt(x1,num(0));

	map<symbol*, symbol*> sol;

	if (cegis(lcondition, x, p, sol, 0.1)) {
		cout<<"cegis succeeded"<<endl;
	}
	else
		cout<<"cegis found no solution"<<endl;

}


void tester::cubli() {
	vector<ast*> x;
	vector<ast*> f;
	vector<ast*> p;

	ast* phi = var("phi");
	x.push_back(phi);
	phi->set_bounds(-1,1);

	ast* p_phi = var("p_phi");
	x.push_back(p_phi);
	p_phi->set_bounds(-5,5);

	ast* p_psi = var("p_psi");
	x.push_back(p_psi);
	p_psi->set_bounds(-5,5);

}


void tester::testall() {
	//cout<< test_ast1()->print_prefix()<<endl;
	//cout<<test_ast2()->print_tree();
	//cout<< test_ast2()->print_smt2(true)<<endl;
	//test_ast2();
	//pwf();
	//simple();
	//ipc();
	powertest2();
	//powertest3();
} 
