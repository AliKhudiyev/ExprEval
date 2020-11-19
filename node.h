
#pragma once

#include <string>
#include "operator.h"

namespace ExprEval
{
    namespace Engine
    {
        enum NodeType{
            Number = 0,
            Operator,
            Expression,
            Empty
        };

        struct Node{
            NodeType type;
            double number;
            std::string symbol;
            std::string expression;

            inline void set(double num){
                type = NodeType::Number;
                number = num;
            }
            inline void set(const std::string expr, bool is_expr=true){
                if(is_expr){
                    type = NodeType::Expression;
                    expression = expr;
                } else{
                    type = NodeType::Operator;
                    symbol = expr;
                }
            }
        };
    } // namespace Engine
} // namespace ExprEval


