
#pragma once

#include "tokenizer.h"
#include "node_list.h"

namespace ExprEval
{
    class Expression{
        private:
        std::string m_expression;
        double m_result;
        bool is_calculated;
        Tokenizer m_tokenizer;

        public:
        Expression(): 
            is_calculated(false) {}
        Expression(const std::string& expression):
            m_expression(expression), is_calculated(false), m_tokenizer(Tokenizer(expression)) {}

        inline void set(const std::string& expression){
            if(m_expression != expression){
                m_expression = expression;
                is_calculated = false;
                m_tokenizer.set(expression);
            }
        }
        inline std::string get() const { return m_expression; }

        double evaluate(const std::string& expression){
            NodeList list;
            m_tokenizer.set(expression);
            Node* node;
            while((node = m_tokenizer.get()))
            {
                if(node->type == NodeType::Expression){
                    double ans = evaluate(node->expression);
                    node->set(ans);
                }
                // std::cout<<"type: "<<node->type<<"\n";
                list.add(*node);
            }
            // list.print();
            // std::cout<<"| "<<list.size()<<std::endl;
            return eval(&list);
        }
        double evaluate(){
            return evaluate(m_expression);
        }

        private:
        double eval(NodeList* list) const{
            double result = 0.0;
            auto table = Operator::get_spec_table();
            while(1){
                // Find an operator with the highest priority
                    // If no operator is found, return the final result
                // Calculate it with the relevant operand(s)
                // Replace the new result with the selected section

                size_t opr_index_in_list = 0;
                int priority = 100;
                std::string symbol;
                Node* node;
                Operator::Specification* specification = nullptr;

                list->print();
                std::cout<<"| size: "<<list->size()<<'\n';
                size_t i = 0;
                for(; i<list->size(); ++i){
                    Node curr_node = list->get(i);
                    Node* current_node = &curr_node;
                    // std::cout<<" > type: "<<current_node->type<<'\n';
                    if(current_node->type == NodeType::Operator){
                        int current_priority = Operator::get_priority(current_node->symbol);
                        if(priority > current_priority){
                            // std::cout<<" |> set to operator ["<<current_priority<<"]{"<<current_node->symbol<<"}\n";
                            priority = current_priority;
                            opr_index_in_list = i;
                            symbol = node->symbol;
                            node = current_node;
                            specification = Operator::get_specification(current_node->symbol);
                        }
                    }
                }
                // std::cout<<"Found priority: "<<priority<<'\n';
                if(priority == 100 || !specification){
                    result = list->calculate(0);
                    break;
                }
                double ans = list->calculate(opr_index_in_list);
                result = ans;
                // std::cout<<"ans: "<<ans<<'\n';
            }
            // std::cout<<"Eval done!\n";
            return result;
        }
    };
}
