#include "operator.h"
#include <algorithm>
#include <functional>
#include <iostream>
#include <fstream>
#include <sstream>

namespace ExprEval 
{
    namespace Operator
    {
        bool equals(const CustomOperator& opr1, const CustomOperator& opr2){
            return opr1.get_symbol() == opr2.get_symbol();
        }
    } // namespace Operator
    
    namespace Operator
    {
        void BaseSpecification::write(const std::string& file_path){
            auto table = custom_operator_table;
            std::ofstream file(file_path);

            if(!file){
                throw Engine::Exception(Engine::Error::File, "Cannot open the specification file!");
            }

            for(size_t i=0; i<table->size(); ++i){
                const auto& operator_ = table->at(i);
                file << operator_.symbol << "," << operator_.variables.size() << ",";
                for(const auto& var: operator_.variables){
                    file << var << ",";
                }
                file << operator_.expression << std::endl;
            }

            file.close();
        }

        void BaseSpecification::read(const std::string& file_path){
            auto table = custom_operator_table;
            std::ifstream file(file_path);

            if(!file){
                throw Engine::Exception(Engine::Error::File, "Cannot open the specification file!");
            }

            std::string line;
            std::string token;
            std::stringstream stream;
            std::string symbol;
            std::vector<std::string> variables;
            std::string expression;
            while(std::getline(file, line)){
                unsigned char count = 0;
                stream.clear();
                stream << line;
                while(std::getline(stream, token, ',')){
                    ++count;
                    if(count == 1){
                        symbol = token;
                    }
                    else if(count == 2){
                        variables.resize(atol(token.c_str()));
                    }
                    else if(count > 2 && count <= variables.size() + 2){
                        variables[count-3] = token;
                    }
                    else{
                        expression = token;
                    }
                }
                add_custom_operator(symbol, variables, expression);
            }

            file.close();
        }

        void CustomOperator::replace(const std::string& var, const std::string& token){
            while(1){
                size_t index = result.find(var, 0);
                if(index == std::string::npos) break;
                result.replace(result.begin()+index, result.begin()+index+var.size(), token);
            }
        }

        std::string CustomOperator::convert(const std::vector<std::string>& args){
            result = expression;
            for(size_t i=0; i<variables.size(); ++i){
                replace(variables[i], args[i]);
            }
            return result;
        }

        const std::vector<Operator::Specification>* get_spec_table(){
            if(!specification_table){
                srand(time(0));
                specification_table = new std::vector<Operator::Specification>;

                Operator::Specification spec_add;
                spec_add.symbol = "+";
                spec_add.priority = 9;
                spec_add.n_arg = 2;
                spec_add.arg_positions.push_back(-1);
                spec_add.arg_positions.push_back(1);

                Operator::Specification spec_subtract;
                spec_subtract.symbol = "-";
                spec_subtract.priority = 9;
                spec_subtract.n_arg = 2;
                spec_subtract.arg_positions.push_back(-1);
                spec_subtract.arg_positions.push_back(1);

                Operator::Specification spec_multiply;
                spec_multiply.symbol = "*";
                spec_multiply.priority = 8;
                spec_multiply.n_arg = 2;
                spec_multiply.arg_positions.push_back(-1);
                spec_multiply.arg_positions.push_back(1);

                Operator::Specification spec_divide;
                spec_divide.symbol = "/";
                spec_divide.priority = 8;
                spec_divide.n_arg = 2;
                spec_divide.arg_positions.push_back(-1);
                spec_divide.arg_positions.push_back(1);

                Operator::Specification spec_pow;
                spec_pow.symbol = "^";
                spec_pow.priority = 7;
                spec_pow.n_arg = 2;
                spec_pow.arg_positions.push_back(-1);
                spec_pow.arg_positions.push_back(1);

                Operator::Specification spec_mod;
                spec_mod.symbol = "mod";
                spec_mod.priority = 7;
                spec_mod.n_arg = 2;
                spec_mod.arg_positions.push_back(-1);
                spec_mod.arg_positions.push_back(1);

                Operator::Specification spec_ln;
                spec_ln.symbol = "ln";
                spec_ln.priority = 6;
                spec_ln.n_arg = 1;
                spec_ln.arg_positions.push_back(1);

                Operator::Specification spec_log2;
                spec_log2.symbol = "log2";
                spec_log2.priority = 6;
                spec_log2.n_arg = 1;
                spec_log2.arg_positions.push_back(1);

                Operator::Specification spec_log10;
                spec_log10.symbol = "log";
                spec_log10.priority = 6;
                spec_log10.n_arg = 1;
                spec_log10.arg_positions.push_back(1);

                Operator::Specification spec_sin;
                spec_sin.symbol = "sin";
                spec_sin.priority = 6;
                spec_sin.n_arg = 1;
                spec_sin.arg_positions.push_back(1);

                Operator::Specification spec_cos;
                spec_cos.symbol = "cos";
                spec_cos.priority = 6;
                spec_cos.n_arg = 1;
                spec_cos.arg_positions.push_back(1);

                Operator::Specification spec_tan;
                spec_tan.symbol = "tan";
                spec_tan.priority = 6;
                spec_tan.n_arg = 1;
                spec_tan.arg_positions.push_back(1);

                Operator::Specification spec_cot;
                spec_cot.symbol = "cot";
                spec_cot.priority = 6;
                spec_cot.n_arg = 1;
                spec_cot.arg_positions.push_back(1);

                Operator::Specification spec_sinh;
                spec_sinh.symbol = "sinh";
                spec_sinh.priority = 6;
                spec_sinh.n_arg = 1;
                spec_sinh.arg_positions.push_back(1);

                Operator::Specification spec_cosh;
                spec_cosh.symbol = "cosh";
                spec_cosh.priority = 6;
                spec_cosh.n_arg = 1;
                spec_cosh.arg_positions.push_back(1);

                Operator::Specification spec_tanh;
                spec_tanh.symbol = "tanh";
                spec_tanh.priority = 6;
                spec_tanh.n_arg = 1;
                spec_tanh.arg_positions.push_back(1);

                Operator::Specification spec_asin;
                spec_asin.symbol = "arcsin";
                spec_asin.priority = 6;
                spec_asin.n_arg = 1;
                spec_asin.arg_positions.push_back(1);

                Operator::Specification spec_acos;
                spec_acos.symbol = "arccos";
                spec_acos.priority = 6;
                spec_acos.n_arg = 1;
                spec_acos.arg_positions.push_back(1);

                Operator::Specification spec_atan;
                spec_atan.symbol = "arctan";
                spec_atan.priority = 6;
                spec_atan.n_arg = 1;
                spec_atan.arg_positions.push_back(1);

                Operator::Specification spec_asinh;
                spec_asinh.symbol = "arcsinh";
                spec_asinh.priority = 6;
                spec_asinh.n_arg = 1;
                spec_asinh.arg_positions.push_back(1);

                Operator::Specification spec_acosh;
                spec_acosh.symbol = "arccosh";
                spec_acosh.priority = 6;
                spec_acosh.n_arg = 1;
                spec_acosh.arg_positions.push_back(1);

                Operator::Specification spec_atanh;
                spec_atanh.symbol = "arctanh";
                spec_atanh.priority = 6;
                spec_atanh.n_arg = 1;
                spec_atanh.arg_positions.push_back(1);

                Operator::Specification spec_round;
                spec_round.symbol = "round";
                spec_round.priority = 6;
                spec_round.n_arg = 1;
                spec_round.arg_positions.push_back(1);

                Operator::Specification spec_floor;
                spec_floor.symbol = "floor";
                spec_floor.priority = 6;
                spec_floor.n_arg = 1;
                spec_floor.arg_positions.push_back(1);

                Operator::Specification spec_ceil;
                spec_ceil.symbol = "ceil";
                spec_ceil.priority = 6;
                spec_ceil.n_arg = 1;
                spec_ceil.arg_positions.push_back(1);

                Operator::Specification spec_abs;
                spec_abs.symbol = "abs";
                spec_abs.priority = 6;
                spec_abs.n_arg = 1;
                spec_abs.arg_positions.push_back(1);

                Operator::Specification spec_gamma;
                spec_gamma.symbol = "gamma";
                spec_gamma.priority = 6;
                spec_gamma.n_arg = 1;
                spec_gamma.arg_positions.push_back(1);

                Operator::Specification spec_rand;
                spec_rand.symbol = "rand";
                spec_rand.priority = 6;
                spec_rand.n_arg = 0;
                spec_rand.arg_positions.push_back(1);

                /* Math constants */
                Operator::Specification spec_pi;
                spec_pi.symbol = "pi";
                spec_pi.priority = 5;
                spec_pi.n_arg = 0;

                Operator::Specification spec_e;
                spec_e.symbol = "e";
                spec_e.priority = 5;
                spec_e.n_arg = 0;

                Operator::Specification spec_true;
                spec_true.symbol = "T";
                spec_true.priority = 5;
                spec_true.n_arg = 0;

                Operator::Specification spec_false;
                spec_false.symbol = "F";
                spec_false.priority = 5;
                spec_false.n_arg = 0;
                /* = = = = = = = = */

                Operator::Specification spec_and;
                spec_and.symbol = "and";
                spec_and.priority = 6;
                spec_and.n_arg = 2;
                spec_and.arg_positions.push_back(-1);
                spec_and.arg_positions.push_back(1);

                Operator::Specification spec_or;
                spec_or.symbol = "or";
                spec_or.priority = 6;
                spec_or.n_arg = 2;
                spec_or.arg_positions.push_back(-1);
                spec_or.arg_positions.push_back(1);

                Operator::Specification spec_not;
                spec_not.symbol = "not";
                spec_not.priority = 6;
                spec_not.n_arg = 1;
                spec_not.arg_positions.push_back(1);

                Operator::Specification spec_xor;
                spec_xor.symbol = "xor";
                spec_xor.priority = 6;
                spec_xor.n_arg = 2;
                spec_xor.arg_positions.push_back(-1);
                spec_xor.arg_positions.push_back(1);

                Operator::Specification spec_shiftl;
                spec_shiftl.symbol = "shiftl";
                spec_shiftl.priority = 6;
                spec_shiftl.n_arg = 2;
                spec_shiftl.arg_positions.push_back(-1);
                spec_shiftl.arg_positions.push_back(1);

                Operator::Specification spec_shiftr;
                spec_shiftr.symbol = "shiftr";
                spec_shiftr.priority = 6;
                spec_shiftr.n_arg = 2;
                spec_shiftr.arg_positions.push_back(-1);
                spec_shiftr.arg_positions.push_back(1);

                specification_table->push_back(spec_add);
                specification_table->push_back(spec_subtract);
                specification_table->push_back(spec_multiply);
                specification_table->push_back(spec_divide);
                specification_table->push_back(spec_pow);
                specification_table->push_back(spec_mod);

                specification_table->push_back(spec_ln);
                specification_table->push_back(spec_log2);
                specification_table->push_back(spec_log10);

                specification_table->push_back(spec_sin);
                specification_table->push_back(spec_cos);
                specification_table->push_back(spec_tan);
                specification_table->push_back(spec_cot);

                specification_table->push_back(spec_sinh);
                specification_table->push_back(spec_cosh);
                specification_table->push_back(spec_tanh);
                // specification_table->push_back(spec_coth);

                specification_table->push_back(spec_asin);
                specification_table->push_back(spec_acos);
                specification_table->push_back(spec_atan);
                // specification_table->push_back(spec_acot);

                specification_table->push_back(spec_asinh);
                specification_table->push_back(spec_acosh);
                specification_table->push_back(spec_atanh);
                // specification_table->push_back(spec_acoth);

                specification_table->push_back(spec_round);
                specification_table->push_back(spec_floor);
                specification_table->push_back(spec_ceil);
                specification_table->push_back(spec_abs);
                specification_table->push_back(spec_gamma);
                specification_table->push_back(spec_rand);

                specification_table->push_back(spec_pi);
                specification_table->push_back(spec_e);
                specification_table->push_back(spec_true);
                specification_table->push_back(spec_false);

                specification_table->push_back(spec_and);
                specification_table->push_back(spec_or);
                specification_table->push_back(spec_not);
                specification_table->push_back(spec_xor);
                specification_table->push_back(spec_shiftl);
                specification_table->push_back(spec_shiftr);
            }
            return specification_table;
        }

        const std::vector<Operator::CustomOperator>* get_custom_table(){
            if(!custom_operator_table){
                custom_operator_table = new std::vector<Operator::CustomOperator>;

                CustomOperator operator_sqrt;
                operator_sqrt.symbol = "sqrt";
                operator_sqrt.variables.push_back("var");
                operator_sqrt.arg_positions.push_back(1);
                operator_sqrt.expression = "var^0.5";

                CustomOperator operator_id;
                operator_id.symbol = "id";
                operator_id.variables.push_back("x");
                operator_id.arg_positions.push_back(1);
                operator_id.expression = "x";

                custom_operator_table->push_back(operator_sqrt);
                custom_operator_table->push_back(operator_id);
            }
            return custom_operator_table;
        }

        bool add_custom_operator(const CustomOperator& custom_operator){
            auto custom_table = get_custom_table();
            if(std::find_if(custom_table->cbegin(), custom_table->cend(), std::bind(Operator::equals, custom_operator, std::placeholders::_1)) == custom_table->cend()){
                custom_operator_table->push_back(custom_operator);
                return true;
            }
            return false;
        }

        bool add_custom_operator(const std::string& symbol, const std::vector<std::string>& variables, const std::string& expression){
            CustomOperator custom_operator;
            custom_operator.symbol = symbol;
            custom_operator.variables = variables;
            for (size_t i=0; i<variables.size(); ++i){
                custom_operator.arg_positions.push_back(i+1);
            }
            custom_operator.expression = expression;
            return add_custom_operator(custom_operator);
        }

        bool remove_custom_operator(const std::string& custom_symbol){
            if(custom_symbol.empty()) return false;
            for(size_t i=0; i<custom_operator_table->size(); ++i){
                if(custom_symbol == custom_operator_table->at(i).symbol){
                    custom_operator_table->erase(custom_operator_table->begin()+i);
                    return true;
                }
            }
            return false;
        }

        Operator::Specification* get_specification(const std::string& symbol){
            auto table = specification_table;
            for(size_t i=0; i<table->size(); ++i){
                if(table->at(i).symbol == symbol) return &(table->at(i));
            }
            return nullptr;
        }

        Operator::CustomOperator* get_custom_specification(const std::string& symbol){
            auto table = custom_operator_table;
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

        double _add(double* args, size_t count){ return args[0] + args[1]; }
        double _subtract(double* args, size_t count){ return args[0] - args[1]; }
        double _multiply(double* args, size_t count){ return args[0] * args[1]; }
        double _divide(double* args, size_t count){ return args[0] / args[1]; }
        double _pow(double* args, size_t count){ return pow(args[0], args[1]); }
        double _mod(double* args, size_t count){ return fmod(args[0], args[1]); }

        double _ln(double* args, size_t count){ return log(args[0]); }
        double _log2(double* args, size_t count){ return log2(args[0]); }
        double _log10(double* args, size_t count){ return log10(args[0]); }

        double _sin(double* args, size_t count){ return sin(args[0]); }
        double _cos(double* args, size_t count){ return cos(args[0]); }
        double _tan(double* args, size_t count){ return tan(args[0]); }
        double _cot(double* args, size_t count){ return cos(args[0])/sin(args[0]); }
        double _sinh(double* args, size_t count){ return sinh(args[0]); }
        double _cosh(double* args, size_t count){ return cosh(args[0]); }
        double _tanh(double* args, size_t count){ return tanh(args[0]); }
        // double _coth(double* args, size_t count){ return coth(args[0]); }
        double _arcsin(double* args, size_t count){ return asin(args[0]); }
        double _arccos(double* args, size_t count){ return acos(args[0]); }
        double _arctan(double* args, size_t count){ return atan(args[0]); }
        // double _arccot(double* args, size_t count){ return acot(args[0]); }
        double _arcsinh(double* args, size_t count){ return asinh(args[0]); }
        double _arccosh(double* args, size_t count){ return acosh(args[0]); }
        double _arctanh(double* args, size_t count){ return atanh(args[0]); }
        // double _arccoth(double* args, size_t count){ return asin(args[0]); }

        double _round(double* args, size_t count){ return round(args[0]); }
        double _floor(double* args, size_t count){ return floor(args[0]); }
        double _ceil(double* args, size_t count){ return ceil(args[0]); }
        double _abs(double* args, size_t count){ return fabs(args[0]); }
        double _gamma(double* args, size_t count){ return tgamma(args[0]); }
        double _rand(double* args, size_t count){ return (double)rand()/(double)RAND_MAX; }

        double _pi(double* args, size_t count){ return M_PI; }
        double _e(double* args, size_t count){ return M_E; }
        double _true(double* args, size_t count){ return 1; }
        double _false(double* args, size_t count){ return 0; }

        double _and(double* args, size_t count){ return (int)args[0] & (int)args[1]; }
        double _or(double* args, size_t count){ return (int)args[0] | (int)args[1]; }
        double _not(double* args, size_t count){ return !(int)args[0]; }
        double _xor(double* args, size_t count){ return (int)args[0] ^ (int)args[1]; }
        double _shiftl(double* args, size_t count){ return (int)args[0] << (int)args[1]; }
        double _shiftr(double* args, size_t count){ return (int)args[0] >> (int)args[1]; }

        double trigger(size_t index, double* args){
            double result = 0.0;

            if(index == 0){
                return _add(args);
            } else if(index == 1){
                return _subtract(args);
            } else if(index == 2){
                return _multiply(args);
            } else if(index == 3){
                return _divide(args);
            } else if(index == 4){
                return _pow(args);
            } else if(index == 5){
                return _mod(args);
            } else if(index == 6){
                return _ln(args);
            } else if(index == 7){
                return _log2(args);
            } else if(index == 8){
                return _log10(args);
            } else if(index == 9){
                return _sin(args);
            } else if(index == 10){
                return _cos(args);
            } else if(index == 11){
                return _tan(args);
            } else if(index == 12){
                return _cot(args);
            } else if(index == 13){
                return _sinh(args);
            } else if(index == 14){
                return _cosh(args);
            } else if(index == 15){
                return _tanh(args);
            } else if(index == 16){
                return _arcsin(args);
            } else if(index == 17){
                return _arccos(args);
            } else if(index == 18){
                return _arctan(args);
            } else if(index == 19){
                return _arcsinh(args);
            } else if(index == 20){
                return _arccosh(args);
            } else if(index == 21){
                return _arctanh(args);
            } else if(index == 22){
                return _round(args);
            } else if(index == 23){
                return _floor(args);
            } else if(index == 24){
                return _ceil(args);
            } else if(index == 25){
                return _abs(args);
            } else if(index == 26){
                return _gamma(args);
            } else if(index == 27){
                return _rand(args);
            } else if(index == 28){ // Adding a constant
                return _pi(args);
            } else if(index == 29){ // Adding a constant
                return _e(args);
            } else if(index == 30){ // Adding a constant
                return _true(args);
            } else if(index == 31){ // Adding a constant
                return _false(args);
            } else if(index == 32){
                return _and(args);
            } else if(index == 33){
                return _or(args);
            } else if(index == 34){
                return _not(args);
            } else if(index == 35){
                return _xor(args);
            } else if(index == 36){
                return _shiftl(args);
            } else if(index == 37){
                return _shiftr(args);
            }

            return result;
        }
    }
}