
#pragma once

#include <string>
#include "operator.h"
#include <iostream>

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
            size_t operator_index; // Check this!
            std::string symbol;
            std::string expression;
            Node *prev, *next;

            Node(): 
                prev(nullptr), next(nullptr) {}

            inline void set(double num){
                type = NodeType::Number;
                number = num;
            }
            // inline void set(size_t opr_index){
            //     type = NodeType::Operator;
            //     operator_index = opr_index;
            // }
            inline void set(const std::string expr, bool is_expr=true){
                if(is_expr){
                    type = NodeType::Expression;
                    expression = expr;
                } else{
                    type = NodeType::Operator;
                    symbol = expr;
                }
            }
            
            // double calculate(){
            //     if(type == NodeType::Number){
            //         return number;
            //     } else if(type == NodeType::Operator){
            //         double result = 0.0;
            //         Operator::Specification* specification = Operator::get_specification(symbol);

            //         auto positions = specification->arg_positions;
            //         double args[10];
            //         for(size_t i=0; i<specification->n_arg; ++i){
            //             Node* argument;
            //             // TO DO
            //             if(positions[i] < 0){
            //                 argument = prev;
            //                 args[i] = argument->calculate();
            //                 // std::cout<<"prev arg: "<<args[i]<<'\n';

            //                 prev = argument->prev;
            //                 if(argument->prev){
            //                     argument->prev->next = this;
            //                     delete argument;
            //                 } else{
            //                     // argument = this;
            //                 }
            //             } else if(positions[i] > 0){
            //                 argument = next;
            //                 args[i] = argument->calculate();
            //                 // std::cout<<"next arg: "<<args[i]<<'\n';

            //                 next = argument->next;
            //                 if(argument->next){
            //                     argument->next->prev = this;
            //                     delete argument;
            //                 } else{
            //                     ;
            //                 }
            //             }
            //             // printf("> arg: %lf\n", args[i]);
            //             // delete argument;
            //             // argument->type = NodeType::Empty;
            //             // printf("> deleted\n");
            //         }
            //         result = Operator::add(args);

            //         return result;
            //     } else{
            //         // TO DO
            //         return 0;
            //     }
            // }
        };
    } // namespace Engine
    
} // namespace ExprEval


