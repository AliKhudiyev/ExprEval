
#pragma once

#include "tokenizer.h"
#include "node_list.h"

namespace ExprEval
{
    class Expression{
        private:
        std::string m_expression;
        double m_result;
        bool is_calculated;

        public:
        Expression(): 
            is_calculated(false) {}
        Expression(const std::string& expression):
            m_expression(expression), is_calculated(false) {}

        inline void set(const std::string& expression){
            if(m_expression != expression){
                m_expression = expression;
                is_calculated = false;
            }
        }
        inline std::string get() const { return m_expression; }

        double evaluate(const std::string& expression);
        double evaluate();

        private:
        double eval(NodeList* list) const;
    };
}
