#include "node_list.h"
#include <iostream>

namespace ExprEval
{
    namespace Engine
    {
        double NodeList::calculate(size_t index){
            // std::cout<<"Index: "<<index<<'\n';
            m_beg = index;
            m_end = index + 1;
            double ans;
            try
            {
                ans = calc(index);
            }
            catch(const Exception& e)
            {
                // std::cerr << e.what() << '\n';
                throw e;
            }
            
            // std::cout<<"beg: "<<m_beg<<", end: "<<m_end<<'\n';
            m_nodes.erase(m_nodes.begin()+m_beg, m_nodes.begin()+m_end);

            Node node;
            node.set(ans);
            m_nodes.insert(m_nodes.begin()+m_beg, node);

            return ans;
        }

        void NodeList::print() const{
            for(size_t i=0; i<m_nodes.size(); ++i){
                const Node* node = &(m_nodes[i]);
                std::string type = "expr";
                if(node->type == NodeType::Number){
                    type = "num";
                } else if(node->type == NodeType::Operator){
                    type = "opr";
                }
                std::cout<<"["<<type<<"]"<<"{";
                if(node->type == NodeType::Number){
                    std::cout<<node->number;
                } else if(node->type == NodeType::Operator){
                    std::cout<<node->symbol;
                } else{
                    std::cout<<node->expression;
                }
                std::cout<<"} --> ";
            }
        }

        double NodeList::calc(size_t index, size_t direction){
            Node node = m_nodes[index];

            if(node.type == NodeType::Number){
                return node.number;
            } else if(node.type == NodeType::Operator){
                double result = 0.0;
                Operator::Specification* specification = Operator::get_specification(node.symbol);

                auto positions = specification->arg_positions;
                double args[10];
                for(size_t i=0; i<specification->n_arg; ++i){
                    // TO DO
                    if(positions[i] < 0){
                        if(direction == 1)
                            throw Exception(Error::Expr_Logic, "node @ " + std::to_string(index));

                        m_beg = index - 1;
                        args[i] = calc(index-1, -1);
                        // m_nodes.erase(m_nodes.begin()+index-1);
                    } else if(positions[i] > 0){
                        if(direction == -1)
                            throw Exception(Error::Expr_Logic, "node @ " + std::to_string(index));
                        
                        m_end = index + 2;
                        args[i] = calc(index+1, 1);
                        // m_nodes.erase(m_nodes.begin()+index+1);
                    }
                    // printf("> arg: %lf\n", args[i]);
                }
                result = Operator::trigger(Operator::get_index(node.symbol), args);

                return result;
            } else{
                // TO DO
                return 0;
            }
        }
    }
}