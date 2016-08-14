// parser

#include "hpp.hpp"
#define YYERR "\n\n"<<yylineno<<":"<<msg<<"["<<yytext<<"]\n\n"
void yyerror(string msg) { cout<<YYERR; cerr<<YYERR; exit(-1); }
int main() { yyparse(); dump(); return 0; }

// object system

Sym::Sym(string V) { val=V; }
void Sym::push(Sym*o) { nest.push_back(o); }

string Sym::head() { return "<"+val+">"; }
string Sym::pad(int n) { string S; for (int i=0;i<n;i++) S+='\t'; return S; }
string Sym::dump(int depth) { string S = "\n"+pad(depth)+head();
	for (auto it=nest.begin(),e=nest.end();it!=e;it++)
		S += (*it)->dump(depth+1);
	return S; }

// virtual machine

int		M[Msz];		// memory
int		Ip=0;		// instruction pointer
int		Sp=Msz;		// stack pointer

int		R[Rsz];		// registers

float	F[Fsz];		// \ FPU stack
int		Fp=0;		// /

void dump() {
	cout << "R["<<Rsz<<"]:" << endl;
	for (int r=0;r<Rsz;r++) cout << 'R'<<r << ":" << R[r] << '\t'; cout<<"\n\n";
	cout << "F["<<Fsz<<"]:" << endl;
	for (int f=0;f<Fsz;f++) {
		if (f==Fp) cout<<'^';
		cout << 'F'<<f << ":" << F[f] << '\t';
	} cout<<"\n\n";
	cout << "S["<<(Msz-Sp)<<"]:" << endl;
	cout << "M["<<Msz<<"]:" << endl;
	for (int m=0;m<Msz;m++) {
		if (m%0x10==0) cout<< endl << m <<":\t";
		cout << M[m] << '\t';
	} cout<<"\n\n";
}
