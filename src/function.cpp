#include "function.h"

namespace ExprEval
{
    unsigned int Function::n = 0;
    ExprEval::Expression Function::expression;

    double Function::operator()(const std::initializer_list<double>& arguments) const{
        std::string expr = m_symbol + "(";
        for(auto it=arguments.begin(); it<arguments.end(); ++it){
            expr += std::to_string(*it);
            if(it + 1 < arguments.end()) expr += ", ";
        }
        expr += ")";

        printf(" expr: %s\n", expr.c_str());
        double result = 0;
        try
        {
            result = Function::expression.evaluate(expr);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
        return result;
    }
} // namespace ExprEval
