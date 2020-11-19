
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
            m_index(0) {}
        Tokenizer(const std::string& expression): 
            m_expression(expression), m_index(0) {}
        
        inline void set(const std::string& expression){
            m_expression = expression;
            m_index = 0;
        }
        Node get() const;

        private:
        bool is_digit(char c) const;
    };
} // namespace ExprEval
