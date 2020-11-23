
#pragma once

#include "expression.h"
#include <initializer_list>

namespace ExprEval
{
    class Function{
        private:
        std::string m_expression, m_symbol;
        std::vector<std::string> m_variables;

        static ExprEval::Expression expression;
        static unsigned int n;

        public:
        Function(const std::initializer_list<std::string>& variables, const std::string& expression): 
            m_expression(expression), m_symbol("f_") 
            {   
                m_symbol += std::to_string(Function::n++);
                for(auto it=variables.begin(); it!=variables.end(); ++it){
                    size_t index = 0;

                    while((index = m_expression.find(*it, index)) != std::string::npos){
                        m_expression.replace(index, it->size(), "(" + (*it) + ")");
                        // printf("replacing from %zu... | %s\n", index, m_expression.c_str());
                        index += it->size() + 3;
                    }
                    m_variables.push_back(*it);
                }
                printf("final expr: %s\n", m_expression.c_str());
                Operator::add_custom_operator(m_symbol, m_variables, m_expression);
            }
        ~Function(){
            --Function::n;
        }
        
        inline std::string get() const{ return m_symbol; }
        double operator()(const std::initializer_list<double>& arguments) const;
    };
} // namespace ExprEval
