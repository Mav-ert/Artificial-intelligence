
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

#include "parser.hpp"
#include "NatDed.hpp"

int main() {
	vector<Expr*> kb = load_kb("sammys.kb");
	kb.push_back(ModusPonens(kb[4], kb[29]));
	kb.push_back(ModusPonens(kb[14], kb[32]));
	kb.push_back(Resolution(kb[33],kb[34]));
	kb.push_back(ModusPonens(kb[24], kb[35]));
	kb.push_back(ModusPonens(kb[0], kb[27]));
	kb.push_back(AndElimination(kb[36], 2));
	kb.push_back(Resolution(kb[37], kb[38])); // edit resolution
	kb.push_back(ModusPonens(kb[3], kb[28]));
	kb.push_back(ModusPonens(kb[20], kb[39]));
	kb.push_back(AndElimination(kb[41]));
	kb.push_back(Resolution(kb[40], kb[42]));
	show_kb(kb);
	return 0;
}