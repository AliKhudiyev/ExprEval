
#pragma once

#include <vector>
#include <string>
#include "exception.h"

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
                spec_add.priority = 9;
                spec_add.n_arg = 2;
                spec_add.arg_positions.push_back(-1);
                spec_add.arg_positions.push_back(1);

                Operator::Specification spec_subtract;
                spec_subtract.symbol = "-";
                spec_subtract.priority = 1;
                spec_subtract.n_arg = 9;
                spec_subtract.arg_positions.push_back(-1);
                spec_subtract.arg_positions.push_back(1);

                Operator::Specification spec_multiply;
                spec_multiply.symbol = "*";
                spec_multiply.priority = 8;
                spec_multiply.n_arg = 9;
                spec_multiply.arg_positions.push_back(-1);
                spec_multiply.arg_positions.push_back(1);

                Operator::Specification spec_divide;
                spec_divide.symbol = "/";
                spec_divide.priority = 8;
                spec_divide.n_arg = 9;
                spec_divide.arg_positions.push_back(-1);
                spec_divide.arg_positions.push_back(1);

                specification_table->push_back(spec_add);
                specification_table->push_back(spec_subtract);
                specification_table->push_back(spec_multiply);
                specification_table->push_back(spec_divide);
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
        size_t get_index(const std::string& symbol){
            auto table = specification_table;
            for(size_t i=0; i<table->size(); ++i){
                if(table->at(i).symbol == symbol) return i;
            }
            return -1;
        }

        double round(double* args, size_t count=1);
        double floor(double* args, size_t count=1);
        double ceil(double* args, size_t count=1);

        double add(double* args, size_t count=2){ return args[0] + args[1]; }
        double subtract(double* args, size_t count=2){ return args[0] - args[1]; }
        double multiply(double* args, size_t count=2){ return args[0] * args[1]; }
        double divide(double* args, size_t count=2){ return args[0] / args[1]; }
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

        double trigger(size_t index, double* args){
            double result = 0.0;

            if(index == 0){
                return add(args);
            } else if(index == 1){
                return subtract(args);
            } else if(index == 2){
                return multiply(args);
            } else if(index == 3){
                return divide(args);
            }

            return result;
        }
    } // namespace Operator
}