
#pragma once

#include "node.h"

namespace ExprEval
{
    using namespace Engine;

    class Tokenizer{
        private:
        std::string m_expression;
        mutable size_t m_index;

        public:
        Tokenizer(): 
            m_index(0) 
            {
                Operator::get_spec_table();
            }
        Tokenizer(const std::string& expression): 
            m_expression(expression), m_index(0)
            {
                Operator::get_spec_table();
            }
        
        inline void set(const std::string& expression){
            m_expression = expression;
            m_index = 0;
        }
        Node* get() const{
            while(m_index < m_expression.size()){
                Node* node = new Node;
                if(m_expression[m_index] == '+'){
                    node->set("+", false);
                    ++m_index;
                    return node;
                }
                else if(m_expression[m_index] == '-'){
                    node->set("-", false);
                    ++m_index;
                    return node;
                }
                else{
                    std::string number;
                    size_t beg = m_index;
                    while(m_index < m_expression.size() && (is_digit(m_expression[m_index]) || m_expression[m_index] == '.')){
                        number.push_back(m_expression[m_index]);
                        ++m_index;
                    }
                    node->set(strtod(m_expression.substr(beg, m_index-beg).c_str(), nullptr));
                    return node;
                }
            }

            return nullptr;
        }

        private:
        bool is_digit(char c) const{
            return (c >= 48 && c <= 57);
        }
    };
} // namespace ExprEval
