#include <iostream>
#include <string>

#include "include/expreval.h"

using namespace std;

int main(){
    ExprEval::Expression expr;
    string str;

    while(1){
        cout<<"Give it to me: ";
        // getline(cin, str);
        cin>>str;
        if(str[0] == 'q') break;
        else if(str[0] == '>'){
            ExprEval::Operator::CustomOperator custom_operator;
            size_t n_arg;

            cout<<" > Symbol: ";
            cin>>custom_operator.symbol;
            cout<<" > # Args: ";
            cin>>n_arg;
            for(size_t i=0; i<n_arg; ++i){
                cout<<" > Variable: ";
                string arg;
                cin>>arg;
                custom_operator.arg_positions.push_back(i+1);
                custom_operator.variables.push_back(arg);
            }
            cout<<" > Expression: ";
            cin>>custom_operator.expression;

            ExprEval::Operator::add_custom_operator(custom_operator);
            cout<<"= = = = = = = = = = = = = =\n";
            continue;
        } else if(str[0] == '<'){
            string symbol;
            cout<<" < Symbol: ";
            cin>>symbol;
            ExprEval::Operator::remove_custom_operator(symbol);
            cout<<"= = = = = = = = = = = = = =\n";
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