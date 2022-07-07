#include <iostream>
#include <unordered_map>
#include "parser.hpp"
#include <vector>
#include "DPLL.h"
using namespace std;
template<typename K, typename V>
void print_map(std::unordered_map<K, V> const& m)
{
	for (auto const& pair : m) {
		cout << "{" << pair.first << ": " << pair.second << "}";
	}
}
void getSymbols(set<string>& a, Expr* b) {
	if (b->kind == ATOM) {
		a.insert(b->sym);
	}
	else {
		for (int i = 1; i < b->sub.size();i++) {
			getSymbols(a, b->sub[i]);
		}
	}
}
pbool operator!(pbool a) {
	switch (a)
	{
	case TRUE:
		return FALSE;
	case FALSE:
		return TRUE;
	case MAYBE:
		return MAYBE;
	default:
		return ERROR;
	}
}
pbool operator&(pbool a, pbool b) {
	return !(!a | !b);
}
pbool operator|(pbool a, pbool b) {
	if (a == ERROR || b == ERROR) {
		return ERROR;
	}else if (a == TRUE || b == TRUE) {
		return TRUE;
	}
	else if (a == FALSE && b == FALSE) {
		return FALSE;
	}
	return MAYBE;
}
pbool convert(bool a) {
	return a ? TRUE : FALSE;
}
bool operator==(const Expr& a, const Expr& b) {
	if (a.kind != b.kind) {
		return false;
	}
	if (a.kind == ATOM) {
		return a.sym == b.sym;
	}
	else {
		if (a.sub.size() != b.sub.size()) {
			return false;
		}
		for (int i = 0;i < a.sub.size();i++) {
			if (!(*a.sub[i] == *b.sub[i])) {
				return false;
			}
		}
	}
	return true;
}
pbool evaluate(Expr* clause,const MODEL& model) {
	if (clause->kind == ATOM) {
		if (model.count(clause->sym)) {
			return convert(model.at(clause->sym));
		}
		else {
			return MAYBE;
		}
	}
	else {
		if (clause->sub[0]->sym == "not") {
			return !evaluate(clause->sub[1],model);
		}else if(clause->sub[0]->sym == "or") {
			pbool ret = FALSE;
			for (int i = 1; i < clause->sub.size(); i++) {
				ret = ret | evaluate(clause->sub[i], model);
			}
			return ret;
		}
	}
	cout << " We got there and its bad" << endl;
	return ERROR;
}
vector<Expr*> find_units(Expr* clause, const MODEL& md) {
	if (evaluate(clause, md) !=MAYBE) {
		return vector<Expr*>();
	}
	if (clause->kind == ATOM) {
		return vector<Expr*>{clause};
	}
	else {
		if (clause->sub[0]->sym == "not") {
			return vector<Expr*>{clause};
		}
		else if (clause->sub[0]->sym == "or") {
			vector<Expr*> all;
			for (int i = 1; i < clause->sub.size(); i++) {
				vector<Expr*> units = find_units(clause->sub[i], md);
				for (Expr* unit : units) {
					for (Expr* a : all) {
						if (*unit == *a) {
							goto unit_loop;
						}
					}
					all.push_back(unit);
				unit_loop:;
				}
				
			}
			return all;
		}
	}
}
bool DPLL(vector<Expr*> clauses, set<string>::const_iterator next_symbol, MODEL& model,bool unit,int counter) {
	counter++;
	pbool check = TRUE;
	print_map(model);
	int countTrue=0;
	for (Expr* clause : clauses) {
		pbool sat = evaluate(clause, model);
		if (sat == TRUE) {
			countTrue++;
		}
		check = check & sat;
	}
	if (check == TRUE) {
		cout << "\nsuccess" << endl;
		return true;
	}
	else if(check == FALSE){
		return false;
	}
	else if (check == ERROR) {
		cout << "oof. An error occured, try to do better next time." << endl;
		return false;
	}
	if (unit) {
		bool found = false;
		for (int i = 0;i < clauses.size();i++) {
			
			vector<Expr*> a = find_units(clauses[i],model);
			if (a.size()==1) {
				found = true;
				if (a[0]->kind == ATOM) {
					model[a[0]->sym] = true;
				}
				else {
					model[a[0]->sub[1]->sym] = false;
				}
			}
		}
		if (found) {
			return DPLL(clauses, next_symbol, model, unit, counter);
		}
	}
	while (model.count(*next_symbol)) {
		++next_symbol;
	}
	string symbol = *next_symbol;
	cout << "\n number satisfied: " << countTrue << "\n calls to DPLL:" << counter << endl;
	next_symbol++;
	MODEL model1;
	model1 = model;
	model1[symbol] = true;
	if (DPLL(clauses,next_symbol, model1, unit,counter)) {
		model = model1;
		return true;
	}

	model1 = model;
	model1[symbol] = false;
	if (DPLL(clauses, next_symbol, model1, unit,counter)) {
		model = model1;
		return true;
	}
	return false;
}

int main(int argc, char* argv[])
{
	string filename = "";
	bool unit = true;
	
	filename = argv[2];
	cout<<filename<<endl;
	if (argc == 3) {
		unit = false;
	}

	MODEL m;
	set<string> s;
	cout << "loading kb in " << filename <<endl;
	vector<Expr*> kb6 = load_kb(filename);
	for (Expr* expr : kb6) {
		getSymbols(s, expr);
	}
	bool a = DPLL(kb6, s.begin(), m, unit,0);
	print_map(m);
	if (unit) {
		cout << "\nwith unit clause heuristic" ;
	}
	else {
		cout << "\nwithout unit clause heuristic";
	}
	if (a) {
		cout << "\n number satisfied: " << kb6.size()<<endl;
	}
	else {
		cout << "\n not satisfiable" << endl;
	}
	
	return 1;
}