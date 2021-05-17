#include "parser.hpp"
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#ifndef NATDED_HPP
#define NATDED_HPP
using namespace std;
Expr* ModusPonens(Expr* s1, Expr* s2);
Expr* ImplicationElimination(Expr* s1, Expr* s2);
Expr* AndElimination(Expr* a);
Expr* AndElimination(Expr* a,int b);
Expr* AndIntroduction(Expr* a, Expr* b);
Expr* OrIntroduction(Expr* a, Expr* b);
Expr* DNE(Expr* a);
Expr* DeMorgan(Expr* a);
Expr* Resolution(Expr* a, Expr* b);
#endif
#pragma once