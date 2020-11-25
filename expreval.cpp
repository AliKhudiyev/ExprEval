#include <iostream>
#include <string>
#include <getopt.h>

#include "include/expreval.h"

using namespace std;

int main(int argc, char** argv){
    ExprEval::Expression expr;
    string str;

    ExprEval::Function f({"x", "y"}, "x*y/100");

    ExprEval::Function g({"x[0]", "x[1]"}, f.get({"x[0]-x[1]", "80-x[1]"}) + "+x[0]*x[1]");

    try
    {
        cout << f.get({4, 50}) << " = " << f({4, 50}) << endl;
        cout << g.get({4, 50}) << " = " << g({4, 50}) << endl;

        g.set({"x"}, "3*x+2");
        cout << g.get({4}) << " = " << g({4}) << endl;
    }
    catch(const ExprEval::Engine::Exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    while(1){
        cout<<"Give it to me: ";
        getline(cin, str);
        if(str[0] == 'q') break;
        else if(str[0] == '>'){
            ExprEval::Operator::CustomOperator custom_operator;
            size_t n_arg;

            cout<<" > Symbol: ";
            cin>>custom_operator.symbol;
            cout<<" > # Args: ";
            cin>>n_arg;
            for(size_t i=1; i<=n_arg; ++i){
                cout<<" > Variable ["<<i<<"]: ";
                string arg;
                cin>>arg;
                if(arg.back() != '_'){
                    cout<<" ! [Variable names should end with underscore(_)]\n";
                    i -= 1;
                    continue;
                }
                custom_operator.arg_positions.push_back(i);
                custom_operator.variables.push_back(arg);
            }
            cout<<" > Expression: ";
            cin>>custom_operator.expression;

            ExprEval::Operator::add_custom_operator(custom_operator);
            cout<<"= = = = = = = = = = = = = =\n";
            cin.ignore();
            continue;
        } else if(str[0] == '<'){
            string symbol;
            cout<<" < Symbol: ";
            cin>>symbol;
            ExprEval::Operator::remove_custom_operator(symbol);
            cout<<"= = = = = = = = = = = = = =\n";
            cin.ignore();
            continue;
        } else if(str[0] == '?'){
            auto custom_table = ExprEval::Operator::get_custom_table();
            for(size_t i=0; i<custom_table->size(); ++i){
                auto custom_operator = custom_table->at(i);
                auto args = custom_operator.variables;

                cout<<" - "<<custom_operator.symbol<<"(";
                for(size_t j=0; j<args.size(); ++j){
                    cout<<args[j];
                    if(j < args.size()-1) cout<<", ";
                }
                cout<<") = "<<custom_operator.expression<<endl;
            }
            cout<<"= = = = = = = = = = = = = =\n";
            continue;
        }
        
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