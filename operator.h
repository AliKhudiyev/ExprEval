
#pragma once

#include <vector>
#include <string>
#include <cmath>
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

        static std::vector<Operator::Specification>* specification_table = nullptr;

        const std::vector<Operator::Specification>* get_spec_table();
        Operator::Specification* get_specification(const std::string& symbol);
        int get_priority(const std::string& symbol);
        size_t get_index(const std::string& symbol);

        double _add(double* args, size_t count=2);
        double _subtract(double* args, size_t count=2);
        double _multiply(double* args, size_t count=2);
        double _divide(double* args, size_t count=2);
        double _pow(double* args, size_t count=2);
        double _mod(double* args, size_t count=2);

        double _ln(double* args, size_t count=2);
        double _log2(double* args, size_t count=2);
        double _log10(double* args, size_t count=2);

        double _sin(double* args, size_t count=1);
        double _cos(double* args, size_t count=1);
        double _tan(double* args, size_t count=1);
        double _cot(double* args, size_t count=1);
        double _sinh(double* args, size_t count=1);
        double _cosh(double* args, size_t count=1);
        double _tanh(double* args, size_t count=1);
        // double _coth(double* args, size_t count=1);
        double _arcsin(double* args, size_t count=1);
        double _arccos(double* args, size_t count=1);
        double _arctan(double* args, size_t count=1);
        // double _arccot(double* args, size_t count=1);
        double _arcsinh(double* args, size_t count=1);
        double _arccosh(double* args, size_t count=1);
        double _arctanh(double* args, size_t count=1);
        // double _arccoth(double* args, size_t count=1);

        double _round(double* args, size_t count=1);
        double _floor(double* args, size_t count=1);
        double _ceil(double* args, size_t count=1);
        double _abs(double* args, size_t count=1);
        double _gamma(double* args, size_t count=1);
        double _rand(double* args, size_t count=1);

        double _pi(double* args, size_t count=1);
        double _e(double* args, size_t count=1);

        double trigger(size_t index, double* args);
    } // namespace Operator
}