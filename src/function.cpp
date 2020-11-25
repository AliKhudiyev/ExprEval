#include "function.h"

namespace ExprEval
{
    unsigned int Function::n = 0;
    ExprEval::Expression Function::expression;


    void Function::set(const std::initializer_list<std::string>& variables, const std::string& expression){
        remove();
        m_expression = expression;
        m_symbol = "f_" + std::to_string(Function::n++);
        m_variables.clear();

        for(auto it=variables.begin(); it!=variables.end(); ++it){
            size_t index = 0;

            while((index = m_expression.find(*it, index)) != std::string::npos){
                m_expression.replace(index, it->size(), "(" + (*it) + ")");
                // printf("replacing from %zu... | %s\n", index, m_expression.c_str());
                index += it->size() + 3;
            }
            m_variables.push_back(*it);
        }
        // printf("final expr: %s\n", m_expression.c_str());
        Operator::add_custom_operator(m_symbol, m_variables, m_expression);
    }

    void Function::set(const std::vector<std::string>& variables, const std::string& expression){
        remove();
        m_expression = expression;
        m_symbol = "f_" + std::to_string(Function::n++);
        m_variables.clear();
        
        for(auto it=variables.begin(); it!=variables.end(); ++it){
            size_t index = 0;

            while((index = m_expression.find(*it, index)) != std::string::npos){
                m_expression.replace(index, it->size(), "(" + (*it) + ")");
                // printf("replacing from %zu... | %s\n", index, m_expression.c_str());
                index += it->size() + 3;
            }
            m_variables.push_back(*it);
        }
        // printf("final expr: %s\n", m_expression.c_str());
        Operator::add_custom_operator(m_symbol, m_variables, m_expression);
    }
    
    std::string Function::get(const std::initializer_list<double>& arguments) const{
        std::string expr = m_symbol + "(";

        for(auto it=arguments.begin(); it!=arguments.end(); ++it){
            expr += std::to_string(*it);
            if(it + 1 != arguments.end()) expr += ",";
        }
        expr += ")";

        return expr;
    }

    std::string Function::get(const std::initializer_list<std::string>& arguments) const{
        std::string expr = m_symbol + "(";

        for(auto it=arguments.begin(); it!=arguments.end(); ++it){
            expr += *it;
            if(it + 1 != arguments.end()) expr += ",";
        }
        expr += ")";

        return expr;
    }

    std::string Function::get(const std::vector<std::string>& arguments) const{
        std::string expr = m_symbol + "(";

        for(auto it=arguments.begin(); it!=arguments.end(); ++it){
            expr += *it;
            if(it + 1 != arguments.end()) expr += ",";
        }
        expr += ")";

        return expr;
    }

    double Function::operator()(const std::initializer_list<double>& arguments) const{
        if(m_symbol.empty()) throw Engine::Exception(Error::Expr_Logic, "Trying to calculate undefined function");
        
        std::string expr = m_symbol + "(";
        for(auto it=arguments.begin(); it<arguments.end(); ++it){
            expr += std::to_string(*it);
            if(it + 1 < arguments.end()) expr += ", ";
        }
        expr += ")";

        double result = 0;
        try
        {
            result = Function::expression.evaluate(expr);
        }
        catch(const Engine::Exception& e)
        {
            throw e;
        }
        
        return result;
    }

    double Function::operator()(const std::vector<double>& arguments) const{
        if(m_symbol.empty()) throw Engine::Exception(Error::Expr_Logic, "Trying to calculate undefined function");
        
        std::string expr = m_symbol + "(";
        for(auto it=arguments.begin(); it<arguments.end(); ++it){
            expr += std::to_string(*it);
            if(it + 1 < arguments.end()) expr += ", ";
        }
        expr += ")";

        double result = 0;
        try
        {
            result = Function::expression.evaluate(expr);
        }
        catch(const Engine::Exception& e)
        {
            throw e;
        }
        
        return result;
    }

    void Function::remove(){
        if(Operator::remove_custom_operator(m_symbol)) --Function::n;
    }
} // namespace ExprEval
