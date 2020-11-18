
#pragma once

#include <vector>
#include <string>

namespace ExprEval 
{
    namespace Operator
    {
        struct Specification{
            std::string symbol;
            size_t n_arg;
            std::vector<int> arg_positions;
            std::vector<std::string> pre_operators;
            std::vector<std::string> post_operators;
            int priority;
        };

        enum Type{
            Nop = 0,
            Addition,
            Subtraction
        };

        static std::vector<Operator::Specification>* specification_table = nullptr;

        const std::vector<Operator::Specification>* get_spec_table(){
            if(!specification_table){
                specification_table = new std::vector<Operator::Specification>;

                Operator::Specification spec_add;
                spec_add.symbol = "+";
                spec_add.priority = 1;
                spec_add.n_arg = 2;
                spec_add.arg_positions.push_back(-1);
                spec_add.arg_positions.push_back(1);
                // spec_add.pre_operators.push_back("");
                // spec_add.post_operators.push_back("");

                specification_table->push_back(spec_add);
            }
            return specification_table;
        }

        Operator::Specification* get_specification(const std::string& symbol){
            auto table = specification_table;
            for(size_t i=0; i<table->size(); ++i){
                if(table->at(i).symbol == symbol) return &(table->at(i));
            }
            return nullptr;
        }
        int get_priority(const std::string& symbol){
            auto table = specification_table;
            for(size_t i=0; i<table->size(); ++i){
                if(table->at(i).symbol == symbol) return table->at(i).priority;
            }
            return -1;
        }

        double round(double* args, size_t count=1);
        double floor(double* args, size_t count=1);
        double ceil(double* args, size_t count=1);

        double add(double* args, size_t count=2){ return args[0] + args[1]; }
        double subtract(double* args, size_t count=2);
        double multiply(double* args, size_t count=2);
        double divide(double* args, size_t count=2);
        double pow(double* args, size_t count=2);
        double mod(double* args, size_t count=2);

        double log(double** args, size_t count=2);

        double sin(double* args, size_t count=1);
        double cos(double* args, size_t count=1);
        double tan(double* args, size_t count=1);
        double cot(double* args, size_t count=1);
        double sinh(double* args, size_t count=1);
        double cosh(double* args, size_t count=1);
        double tanh(double* args, size_t count=1);
        double coth(double* args, size_t count=1);
        double arcsinh(double* args, size_t count=1);
        double arccosh(double* args, size_t count=1);
        double arctanh(double* args, size_t count=1);
        double arccoth(double* args, size_t count=1);

        double calculate(size_t index, double* args, size_t count);
    } // namespace Operator
}