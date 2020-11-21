#include "tokenizer.h"
#include "operator.h"
#include <iostream>

namespace ExprEval
{
    using namespace Engine;

    Node Tokenizer::get(){
        Node node;
        auto m_table = Operator::get_spec_table();
        auto custom_table = Operator::get_custom_table();
        // std::cout<<" >> current index: "<<m_index<<'\n';
        while(m_index < m_expression.size() || !m_cache.empty()){
            if(m_expression[m_index] == ' '){
                ++m_index;
                continue;
            }
            while(!m_cache.empty()){
                node = m_cache.back();
                m_cache.pop_back();
                return node;
            }

            if(m_expression[m_index] == '('){
                try
                {
                    tokenize();
                    node = m_cache.back();
                    m_cache.pop_back();
                }
                catch(const Engine::Exception& e)
                {
                    throw e;
                }
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
                if(m_index + length > m_expression.size()) continue;
                if(m_table->at(i).symbol.compare(m_expression.substr(m_index, length)) == 0){
                    if(opr_length < length){
                        opr_length = length;
                        opr_index = i;
                    }
                }
            }

            if(!opr_length){
                // std::cout<<"searching for user-defined symbols...\n";
                size_t custom_opr_index, custom_opr_length = 0;
                for(size_t i=0; i<custom_table->size(); ++i){
                    size_t length = custom_table->at(i).symbol.size();
                    if(m_index + length > m_expression.size()) continue;
                    if(custom_table->at(i).symbol.compare(m_expression.substr(m_index, length)) == 0){
                        if(custom_opr_length < length){
                            custom_opr_length = length;
                            custom_opr_index = i;
                        }
                    }
                }
                if(custom_opr_length){
                    // std::cout<<"custom operator index: "<<custom_opr_index<<'\n';
                    auto custom_operator = custom_table->at(custom_opr_index);
                    // std::cout<<"custom operator: "<<custom_operator.symbol<<'\n';
                    size_t new_index = m_index+custom_operator.symbol.size();
                    if(m_expression[new_index] != '('){
                        throw Exception(Error::Expr_Logic, "node @ " + std::to_string(m_index));
                    }
                    // std::cout<<"parsed symbol: "<<m_expression.substr(m_index, new_index-m_index)<<'\n';
                    node.set(m_expression.substr(m_index, new_index-m_index), false);
                    m_index = new_index;

                    return node;
                }
                else{
                    throw Exception(Error::Symbol_Not_Found, "node @ " + std::to_string(m_index));
                }
            }
            else{
                m_index += opr_length - 1;

                node.set(m_table->at(opr_index).symbol, false);
                ++m_index;
                return node;
            }
        }

        node.type = NodeType::Empty;
        return node;
    }

    bool Tokenizer::is_digit(char c) const{
        return (c >= 48 && c <= 57);
    }

    void Tokenizer::tokenize(){
        std::cout<<"sub expr: "<<m_expression.substr(m_index)<<'\n';
        Node node;
        size_t count = 1;
        size_t beg = m_index+1;
        while(count){
            if(++m_index >= m_expression.size())
                throw Exception("?");
            
            if(m_expression[m_index] == '(') ++count;
            else if(m_expression[m_index] == ')') --count;

            if(count == 1 && (m_expression[m_index] == ',')){
                Node node;
                node.set(m_expression.substr(beg, m_index-beg), true);
                m_cache.insert(m_cache.begin(), node); // Optimization needed!
                // std::cout<<" > parsed "<<m_expression.substr(beg, m_index-beg)<<"\n";
                beg = m_index + 1;
            } else if(!count){
                Node node;
                // std::cout<<" > parsed: "<<m_expression.substr(beg, m_index-beg)<<'\n';
                node.set(m_expression.substr(beg, m_index-beg), true);
                m_cache.insert(m_cache.begin(), node); // Optimization needed!
                beg = m_index + 1;
            }
        }
        if(beg + 1 == m_index){
            throw Exception(Error::Expr_Logic, "node @ " + std::to_string(m_index));
        }
        ++m_index;
    }
}