
#pragma once

#include "node.h"

namespace ExprEval
{
    using namespace Engine;

    class Tokenizer{
        private:
        std::string m_expression;
        mutable size_t m_index;
        const std::vector<Operator::Specification>* m_table;

        public:
        Tokenizer(): 
            m_index(0) 
            {
                m_table = Operator::get_spec_table();
            }
        Tokenizer(const std::string& expression): 
            m_expression(expression), m_index(0)
            {
                m_table = Operator::get_spec_table();
            }
        
        inline void set(const std::string& expression){
            m_expression = expression;
            m_index = 0;
        }
        Node get() const{
            Node node;
            std::cout<<" >> current index: "<<m_index<<'\n';
            while(m_index < m_expression.size()){
                if(m_expression[m_index] == '('){
                    size_t count = 1;
                    size_t beg = m_index+1;
                    while(count){
                        if(++m_index >= m_expression.size())
                            throw Exception("?");
                        
                        if(m_expression[m_index] == '(') ++count;
                        else if(m_expression[m_index] == ')') --count;
                    }
                std::string tmp = m_expression.substr(beg, m_index-beg);
                // std::cout<<"expr: "<<tmp<<'\n';
                node.set(m_expression.substr(beg, m_index-beg), true);
                ++m_index;
                return node;
                }
                else if(is_digit(m_expression[m_index])){
                    std::string number;
                    size_t beg = m_index;
                    while(m_index < m_expression.size() && (is_digit(m_expression[m_index]) || m_expression[m_index] == '.')){
                        number.push_back(m_expression[m_index]);
                        ++m_index;
                    }
                    node.set(strtod(m_expression.substr(beg, m_index-beg).c_str(), nullptr));
                    return node;
                }
                
                size_t opr_index, opr_length = 0;
                for (size_t i=0; i<m_table->size(); ++i){
                    size_t length = m_table->at(i).symbol.size();
                    if(m_table->at(i).symbol.compare(m_expression.substr(m_index, length)) == 0){
                        if(opr_length < length){
                            opr_length = length;
                            opr_index = i;
                        }
                    }
                }

                if(!opr_length) 
                    throw Exception(Error::Symbol_Not_Found, "node @ " + std::to_string(m_index));
                
                node.set(m_table->at(opr_index).symbol, false);
                ++m_index;
                return node;
                
            }

            node.type = NodeType::Empty;
            return node;
        }

        private:
        bool is_digit(char c) const{
            return (c >= 48 && c <= 57);
        }
    };
} // namespace ExprEval
