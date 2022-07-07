
#ifndef DPLL_HPP
#define DPLL_HPP
#include <iostream>
#include <unordered_map>
#include <set>
#include "parser.hpp"
using namespace std;
enum pbool
{
	FALSE, TRUE, MAYBE, ERROR
};
void getSymbols(set<string>& a, Expr* b);
pbool operator!(pbool);
pbool operator|(pbool,pbool);
pbool operator&(pbool, pbool);
pbool convert(bool a);
bool operator==(const Expr& a, const Expr& b);
typedef unordered_map<string, bool> MODEL;
bool DPLL(vector<Expr*> clauses,set<string>::const_iterator next_symbol, MODEL& model,bool unit,int counter);
pbool evaluate(Expr* clause,const MODEL& model);

#endif
