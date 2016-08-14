#ifndef _H_HPP
#define _H_HPP

#include <iostream>
#include <cstdlib>
#include <cassert>
#include <vector>
#include <map>
using namespace std;

// object system

struct Sym {
	string val;
	Sym(string);
	vector<Sym*> nest; void push(Sym*);
	virtual string dump(int=0); virtual string head(); string pad(int);
};

// parser

extern int yylex();
extern int yylineno;
extern char* yytext;
#define TOC(C,X) { yylval.o = new C(yytext); return X; }
extern int yyparse();
extern void yyerror(string);
#include "ypp.tab.hpp"

// virtual machine

#define Msz 0x200
#define Rsz 0x07
#define Fsz 0x07

extern int M[Msz];		// memory
extern int Ip;			// instruction pointer
extern int Sp;			// stack pointer

extern int R[Rsz];		// registers

extern float F[Fsz];	// FPU stack
extern int Fp;

extern void dump();

#endif // _H_HPP
