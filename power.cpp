#include "power.h"
#include <assert.h>

power_grid::power_grid(table* t, int n) 
	: converter(t), size(n) {

	b.resize(size);
	g.resize(size);
	zp.resize(size);
	zq.resize(size);
	zph.resize(size);
	zqh.resize(size);
	sigma2.resize(size);

	for (int i = 0; i<size; i++) {
		string v = "v";
		string theta = "theta";
		string v_hat = "vhat";
		string t_hat = "thehat";

		v += to_string(i);
		theta += to_string(i);
		v_hat += to_string(i);
		t_hat += to_string(i);
	//	cout<<v<<" "<<theta;
	
		ast* a1 = var(v);
		ast* a2 = var(theta);
		ast* a3 = var(v_hat);
		ast* a4 = var(t_hat);

		volts.push_back(a1);
		phasors.push_back(a2);
		vhat.push_back(a3);
		thehat.push_back(a4);

		x.push_back(a1);
		x.push_back(a1);
		xhat.push_back(a3);
		xhat.push_back(a4);

		b[i].resize(size,0.0);
		g[i].resize(size,0.0);
		sigma2[i].resize(size,0.00001);

		for (int j =0; j<size; j++) {
			string zpn = "zp_";
			string zqn = "zq_";
			string zphn = "zph_";
			string zqhn = "zqh_";

			zpn += to_string(i);
			zqn += to_string(i);
			zpn += "_";
			zqn += "_";
			zpn += to_string(j);
			zqn += to_string(j);

			zphn += to_string(i);
			zqhn += to_string(i);
			zphn += "_";
			zqhn += "_";
			zphn += to_string(j);
			zqhn += to_string(j);

			zp[i].push_back(var(zpn));
			zq[i].push_back(var(zqn));
			zph[i].push_back(var(zphn));
			zqh[i].push_back(var(zqhn));
		}

	}	
}

void power_grid::add_line(int i, int j) {
	map<int, set<int>*>::iterator it;
	set<int>* nb;

	it = neighbors.find(i);
	if (it!= neighbors.end())
		it->second->insert(j);
	else {
		nb = new set<int>;
		nb -> insert(j);
		neighbors.insert(pair<int,set<int>*>(i,nb));
	}
//undirected
	it = neighbors.find(j);
	if (it!= neighbors.end())
		it->second->insert(i);
	else {
		nb = new set<int>;
		nb -> insert(i);
		neighbors.insert(pair<int,set<int>*>(j,nb));
	}
}

ast* power_grid::p(int i, vector<ast*>& v, vector<ast*>& t) {
	ast* result;
	result = num("0");
	for(set<int>::iterator it = neighbors[i]->begin();
								it != neighbors[i]->end(); it++) 
	{
		int j = *it ;
		result = add(
					result,
					mul(v[j],
						sub(sub(num("0"), 
					 	 	 	mul( num(g[i][j]),cos(sub(t[i], t[j])))
								),
							mul(num(b[i][j]), sin(sub(t[i], t[j])))
				 			)
				 		)
					);
	}
	result = mul(v[i], result);
	simplify(result);
	return result;
}


ast* power_grid::q(int i,vector<ast*>& v, vector<ast*>& t) {
	ast* result;
	result = num("0");

	for(set<int>::iterator it = neighbors[i]->begin();
								it != neighbors[i]->end(); it++) 
	{
		int j = *it ;
		result = add(result, 
					 mul(v[j],
					 	 sub( 
							mul(num(b[i][j]), cos(sub(t[i], t[j]))),
							mul(num(g[i][j]),sin(sub(t[i], t[j])))
							)
						)
					);
	}
	result = mul(v[i], result);
	simplify(result);
	return result;
}

ast* power_grid::p(int i, int j, vector<ast*>& v, vector<ast*>& t) {
	ast* result;
	result = mul(pow(volts[i],num("2")),num(g[i][j]));
	result = sub(result,mul(v[i],mul(v[j],
				mul(num(g[i][j]),cos(sub(t[i],t[j]))))));
	result = sub(result, mul(v[i],mul(v[j],
				mul(num(b[i][j]),sin(sub(t[i],t[j]))))));
	return result;
}


ast* power_grid::q(int i, int j, vector<ast*>& v, vector<ast*>& t) {
	ast* result;
	result = sub(num("0"),mul(pow(v[i],num("2")),num(g[i][j])));
	result = sub(result,mul(v[i],mul(v[j],
				mul(num(b[i][j]),cos(sub(t[i],t[j]))))));
	result = sub(result, mul(v[i],mul(v[j],
				mul(num(g[i][j]),sin(sub(t[i],t[j]))))));
	return result;
}

ast* power_grid::est() { 
	ast* result = num("0");
	ast* component = num("0");

	for (int i=0; i<size; i++) {
		for (int j=0; j<size; j++) {
			component = add(
							component,
							div(
								mul(
									sub(zp[i][i],p(i,vhat,thehat)),
									partial(p(i,vhat,thehat),vhat[j])
									), 
								num(sigma2[i][j])
								)
							);
			component = add(
							component,
							div(
								mul(sub(zp[i][i],p(i,vhat,thehat)),
									partial(p(i,vhat,thehat),thehat[j])
									), 
								num(sigma2[i][j])
								)
							);
		}
		for(int j = 0; j<neighbors[i]->size(); j++) {
			break;
		}
	}
	return result;
}




