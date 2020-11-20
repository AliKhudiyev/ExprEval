#include "expression.h"

namespace ExprEval
{
    double Expression::evaluate(const std::string& expression){
        // std::cout<<" === Expr: "<<expression<<"\n";
        NodeList list;
        Tokenizer tokenizer(expression);
        Node node;
        while(1)
        {
            try
            {
                node = tokenizer.get();
            }
            catch(const Exception& e)
            {
                // std::cerr << e.what() << '\n';
                throw e;
            }
            
            if(node.type == NodeType::Empty) break;

            if(node.type == NodeType::Expression){
                double ans = evaluate(node.expression);
                // std::cout<<" >>> tmp ans: "<<ans<<'\n';
                node.set(ans);
            }
            // std::cout<<" | type: "<<node.type<<"\n";
            list.add(node);
        };
        // list.print();
        // std::cout<<"| "<<list.size()<<std::endl;
        return eval(&list);
    }

    double Expression::evaluate(){
        return evaluate(m_expression);
    }

    double Expression::eval(NodeList* list) const{
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

            // list->print();
            // std::cout<<"| size: "<<list->size()<<'\n';
            size_t i = 0;
            auto custom_table = Operator::get_custom_table();
            for(; i<list->size(); ++i){
                Node curr_node = list->get(i);
                Node* current_node = &curr_node;
                // std::cout<<" > type: "<<current_node->type<<'\n';
                if(current_node->type == NodeType::Operator){
                    int current_priority = Operator::get_priority(current_node->symbol);
                    if(current_priority == -1){
                        auto custom_specification = Operator::get_custom_specification(current_node->symbol);
                        if(custom_specification){
                            // std::cout<<" |> set to operator ["<<current_priority<<"]{"<<current_node->symbol<<"}\n";
                            priority = 3;
                            opr_index_in_list = i;
                            break;
                        }
                    }
                    else if(priority > current_priority){
                        // std::cout<<" |> set to operator ["<<current_priority<<"]{"<<current_node->symbol<<"}\n";
                        priority = current_priority;
                        opr_index_in_list = i;
                        symbol = current_node->symbol;
                        node = current_node;
                        specification = Operator::get_specification(current_node->symbol);
                    }
                }
            }
            // std::cout<<"Found priority: "<<priority<<'\n';
            if(priority == 100){            
                result = list->calculate(0);
                break;
            }
            try
            {
                double ans;
                list->calculate(opr_index_in_list);
                result = ans;
            }
            catch(const Engine::Exception& e)
            {
                // std::cerr << e.what() << '\n';
                throw e;
            }
            // std::cout<<"ans: "<<ans<<'\n';
        }
        // std::cout<<"Eval done!\n";
        return result;
    }
}