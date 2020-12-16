#include <iostream>
#include "include/expreval.h"

using namespace std;

int main(){
	ExprEval::Expression expr;
	string str;

	getline(cin, str);
	try{
		cout<<" = "<<expr.evaluate(str)<<'\n';
	} catch(const ExprEval::Engine::Exception& e){
		cerr<<e.what()<<":(\n";
	}

	return 0;
}
