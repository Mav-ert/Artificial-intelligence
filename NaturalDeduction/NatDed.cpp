#include "parser.hpp"
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
Expr* ModusPonens(Expr* s1, Expr* s2) {
	string t = " ";
	Expr* def = new Expr(t);
	if (Eq(s1->sub[1], s2)) {
		Expr* ret(s1->sub[s1->sub.size() - 1]);
		return ret;
	}
	return def;
}
Expr* ImplicationElimination(Expr* a, Expr* b) {
	string t = " ";
	Expr* def = new Expr(t);
	
	return def;
}
Expr* AndElimination(Expr* a) {
	return a->sub.at(1);
}
Expr* AndElimination(Expr* a,int b) {
	return a->sub.at(b);
}
Expr* AndIntroduction(Expr* a, Expr* b) {
	string as = a->toString();
	string bs = b->toString();
	as = "(and " + as + " " + bs + ")";
	Expr * ret = parse(as);
	return ret;
}
Expr* OrIntroduction(Expr* a, Expr* b) {
	string as = a->toString();
	string bs = b->toString();
	as = "(or " + as + " " + bs + ")";
	Expr* ret = parse(as);
	return ret;
}
Expr* DNE(Expr* a) {
	return(a->sub[1]->sub[1]);
}
Expr* Resolution(Expr* a, Expr* b) {
	string s = "";
	if (b->sub.at(0)->toString() == "not") {
		if (Eq(b->sub.at(1), a->sub.at(1))) {
			Expr* ret(a->sub.at(2));
			return ret;
		}
		else {
			Expr* ret(a->sub.at(1));
			return ret;
		}
	}
	
	if (a->sub.size() >= b->sub.size()) {
		for (int i = 1;i < a->sub.size();i++) {
			for (int j = 1;j < b->sub.size();j++) {
				if (Eq(a->sub[i], b->sub[j])) {
					s = s + a->sub.at(i)->toString();
				}
			}
		}
	}else if (a->sub.size() < b->sub.size()) {
		for (int i = 1;i < b->sub.size();i++) {
			for (int j = 1;j < a->sub.size();j++) {
				if (Eq(b->sub[i], a->sub[j])) {
					s = s + b->sub.at(i)->toString();
				}
			}
		}
	}
	Expr* ret = parse(s);
	return ret;
}
Expr* DeMorgan(Expr* a) {
	string s =  "";
	string g = a->sub[1]->sub[1]->toString();
	string h = a->sub[1]->sub[2]->toString();
	if (a->sub[1]->sub[0]->toString() == "or") {
		s = "(and (not";
	}
	
	else if(a->sub[1]->sub[0]->toString() == "and") {
		s = "(or (not";
	}
	Expr* ret = parse(s + " " + g + ") (not " + h + "))");
	return ret;
}	