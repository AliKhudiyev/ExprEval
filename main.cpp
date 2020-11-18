#include <iostream>
#include <string>

#include "expreval.h"

using namespace std;

int main(){
    ExprEval::Expression expr;
    string str;

    while(1){
        cin>>str;
        // cout<<" = "<<expr.evaluate(str)<<endl;
        ExprEval::Engine::Node* node;
        ExprEval::NodeList list;
        cout<<" = "<<expr.evaluate(str)<<endl;
    }

    return 0;
}