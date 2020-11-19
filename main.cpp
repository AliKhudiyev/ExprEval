#include <iostream>
#include <string>

#include "expreval.h"

using namespace std;

int main(){
    ExprEval::Expression expr;
    string str;

    while(1){
        cin>>str;
        
        try
        {
            cout<<" = "<<expr.evaluate(str)<<endl;
        }
        catch(const ExprEval::Engine::Exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    return 0;
}