#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <queue>
#include "parser.hpp"
#include <string>
#define MAX_ITERS 10000
void getSymbol(vector<string>& a, Expr* b) {
	if (b->kind == ATOM) {
		a.push_back(b->sym);
	}
	else {
		for (int i = 1; i < b->sub.size();i++) {
			getSymbol(a, b->sub[i]);
		}
	}
}
void getSymbols(vector<string>& a, Expr* b, bool flag) {
	if (b->kind == ATOM){
		if (flag) {
			a.push_back("(not " + b->sym + ")");
		}
		else {
			a.push_back(b->sym);
		}
	}
	else {
		if (b->sub[0]->sym == "not") {
			flag = true;
		}
		else {
			flag = false;
		}
		for (int i = 1; i < b->sub.size();i++) {
			getSymbols(a, b->sub[i], flag);
		}
	}
}
bool resolvable(Expr* clause1, Expr* clause2) {
	vector<string> c1literals;
	vector<string> c2literals;
	vector<string> ret;
	bool flag = false;
	getSymbols(c1literals, clause1, flag);
	getSymbols(c2literals, clause2, flag);
	for (int i = 0;i < c1literals.size();i++) {
		for (int j = 0;j < c2literals.size();j++) {
			if (c1literals[i] == "(not " + c2literals[j] + ")") {
				ret.push_back(c2literals[j]);
			}
			else if (c2literals[j] == "(not " + c1literals[i] + ")") {
				ret.push_back(c1literals[i]);
			}
		}
	}
	return ret.size() > 0 ? true : false;
}
vector<string> matching_propositions(Expr* clause1, Expr* clause2){
	vector<string> c1literals;
	vector<string> c2literals;
	vector<string> ret; 
	bool flag = false;
	getSymbols(c1literals, clause1,flag);
	getSymbols(c2literals, clause2,flag);
	for (int i = 0;i < c1literals.size();i++) {
		for (int j = 0;j < c2literals.size();j++) {
			if (c1literals[i] == "(not " + c2literals[j] + ")") {
				ret.push_back(c2literals[j]); 
			}
			else if (c2literals[j] == "(not " + c1literals[i] + ")") {
				ret.push_back(c1literals[i]);
			}
		}
	}/*
	for (int i = 0;i < ret.size();i++) {
		cout << ret[i] << endl;
	}*/
	return ret;
}

Expr* resolve(Expr* clause1, Expr* clause2, string Prop) {
	Expr* ret;
	string retstring = "(or ";
	vector<string> c1literals;
	vector<string> c2literals;
	bool flag = false;
	getSymbols(c1literals, clause1, flag);
	getSymbols(c2literals, clause2, flag);
	c1literals.insert(c1literals.end(), c2literals.begin(), c2literals.end());

	set<string> s(c1literals.begin(), c1literals.end());
	vector<string> v(s.begin(), s.end());
	for (int i = 0; i < v.size();i++) {
        if(v[i]==" "||v[i]==""){
            continue;
        }
		if (v[i].find(Prop) == string::npos) {
			if (i == v.size() - 1) {
				retstring+=v[i];
			}
			else {
				retstring += v[i] + " ";
			}
			
		}
	}
	retstring += ")";
	//cout << "resolving " << retstring << endl;
	ret = parse(retstring);
	return ret;
}

bool validateClause(Expr* clause) {
	vector<string> syms;
	bool flag = false;
	vector<string> ret;
	getSymbols(syms, clause, flag);
	for (int i = 0;i < syms.size();i++) {
		for (int j = 0;j < syms.size();j++) {
            if(syms[i]==" "||syms[i]==""){
                continue;
            }
			if (syms[i] == "(not " + syms[j] + ")") {
				return false;
			}
			else if (syms[j] == "(not " + syms[i] + ")") {
				return false;
			}
		}
	}
	return true;
}



class ResPair { 
public:
	Expr* i;
	Expr* j;
	int score;
	ResPair(Expr* a, Expr* b) {
		i = a; 
		j = b; 
		score = 0;
	} 
	ResPair(Expr* a, Expr* b,int _score) {
		i = a;
		j = b;
		score = _score;
	}
	void show(){
		cout << "Respair" << i->toString() << "   " << j->toString() << "     " << score << endl;
	}
};
int scorepair(ResPair* a) {
	vector<string> litsi;
	vector<string> litsj;
	bool flag = false;
	getSymbols(litsi, a->i, flag);
	getSymbols(litsj, a->j, flag);

	litsi.insert(litsi.end(), litsj.begin(), litsj.end());
	//return litsi.size();
	//removing duplicates
	set<string> s(litsi.begin(), litsi.end());
	return s.size();
}

struct comp_pairs {//haha
	bool operator()(ResPair* a, ResPair* b) {
		return a->score > b->score;
	}
};

bool inkb(Expr* a,vector<Expr*>& kb) {
	for (Expr* i : kb) {
		if (i->toString() == a->toString()) {
			return true;
		}
	}
	return false; 
}

Expr * negates(Expr* a) {
	vector<string> sym;
	if (a->toString().find("not") != std::string::npos) {
		getSymbol(sym, a);
		return parse("(or "+sym[0]+")");
	}
	return parse("(or (not " + a->toString() + "))");
}


bool resolution(vector<Expr*> kb, Expr* query) {
	kb.push_back(negates(query));
	//kb.push_back(query);
	priority_queue<ResPair*, vector<ResPair*>, comp_pairs> pq;
	for (int i = 0;i < kb.size();i++) {
		for (int j = i+1;j < kb.size();j++) {
			ResPair* pair = new ResPair(kb[i], kb[j]);
			if (resolvable(kb[i], kb[j])) {
				pair->score = scorepair(pair);
				//pair->show();
				pq.push(pair);
			}
		}
	}
	int iter = 0;
	while (!pq.empty() && iter < MAX_ITERS) {
		cout << "iter: " << iter << " clauses: " << kb.size() << endl;
		ResPair* check = pq.top();
		pq.pop();
		cout << "resolving ";
		check->show();
		vector<string> Props = matching_propositions(check->i, check->j);

		for (string p : Props) {
			Expr* resolvent = resolve(check->i, check->j, p);
			if ((resolvent->toString() == "(or)") || (resolvent->toString() == "") ||(resolvent->sub.size() == 0)) {
				cout <<" Resolvent: (or)"<<endl<< "success" << endl;
				cout << iter << endl;
				//show_kb(kb);
				return true;
			}
			if ((validateClause(resolvent) == false) || inkb(resolvent, kb)) {
				continue;
			}
			for (Expr* i : kb) {
				if (resolvable(i, resolvent)) {
					ResPair* np = new ResPair(i, resolvent);
					np->score = scorepair(np);
					pq.push(np);
				}
			}
			cout << "Resolvent: " << resolvent->toString() << endl<<endl;

			kb.push_back(resolvent);

		}
		iter++;
    }
	//show_kb(kb);
	cout << "failure" << endl;
	cout << iter << " "<<pq.size()<< endl;
	return false;
}

//int main() {
int main(int argc, char* argv[]){
	string filename = "";
	
	filename = argv[2];
	cout<<filename<<endl;
	cout << "loading kb in " << filename <<endl;
	vector<Expr*> kb6 = load_kb(filename);

	string q = argv[3];
    cout<<q;
	Expr* query= parse(q);
	resolution(kb6,query);
	return 0;
}