
#pragma once

#include "expression.h"
#include <initializer_list>

namespace ExprEval
{
    class Function{
        private:
        std::string m_expression, m_symbol;
        std::vector<std::string> m_variables;
        bool m_initialized = false;

        static ExprEval::Expression expression;
        static unsigned int n;

        public:
        Function() = default;
        Function(const std::initializer_list<std::string>& variables, const std::string& expression){   
            set(variables, expression);
        }
        Function(const std::vector<std::string>& variables, const std::string& expression){
            set(variables, expression);
        }
        ~Function(){
            --Function::n;
        }
        
        void set(const std::initializer_list<std::string>& variables, const std::string& expression);
        void set(const std::vector<std::string>& variables, const std::string& expression);
        inline std::string get() const{ return m_symbol; }
        std::string get(const std::initializer_list<double>& arguments) const;
        std::string get(const std::initializer_list<std::string>& arguments) const;
        std::string get(const std::vector<std::string>& arguments) const;

        double operator()(const std::initializer_list<double>& arguments) const;
        double operator()(const std::vector<double>& arguments) const;
    
        private:
        void remove();
    };
} // namespace ExprEval
