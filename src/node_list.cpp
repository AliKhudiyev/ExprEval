#include "expression.h"
#include "node_list.h"
#include <iostream>
#include <sstream>

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
            if(m_cache.type == NodeType::Expression){
                // std::cout<<"replacing with "<<m_cache.expression<<'\n';
                // std::cout<<" from ["<<m_beg<<", "<<m_end<<"), size: "<<m_nodes.size()<<'\n';
                m_nodes.erase(m_nodes.begin()+m_beg, m_nodes.begin()+m_end);
                m_cache.type = NodeType::Empty;

                ExprEval::Expression subexpr;
                ans = subexpr.evaluate(m_cache.expression);

                Node node;
                node.set(ans);
                m_nodes.insert(m_nodes.begin()+m_beg, node);
                // std::cout<<"replacing with the number: "<<ans<<'\n';
            } else{
                m_nodes.erase(m_nodes.begin()+m_beg, m_nodes.begin()+m_end);
                
                Node node;
                node.set(ans);
                m_nodes.insert(m_nodes.begin()+m_beg, node);
            }
            // std::cout<<"final ans: "<<ans<<'\n';
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
            bool is_standard_opr = true;

            if(node.type == NodeType::Number){
                return node.number;
            } else if(node.type == NodeType::Operator){
                // std::cout<<"node symbol: "<<node.symbol<<'\n';
                double result = 0.0;
                Operator::BaseSpecification* specification = Operator::get_specification(node.symbol);
                if(!specification){
                    is_standard_opr = false;
                    // printf("standard opr\n");
                    if(!(specification = Operator::get_custom_specification(node.symbol))){
                        // printf("throwing...\n");
                        throw Exception(Error::Symbol_Not_Found, "node @ " + std::to_string(index));
                    }
                }

                auto positions = specification->get_arg_positons();
                double args[10];
                // std::cout<<"index: "<<index<<", list size: "<<size()<<'\n';
                for(size_t i=0; i<specification->get_n_arg(); ++i){
                    if(positions[i] < 0){
                        if(direction == 1){
                            throw Exception(Error::Expr_Logic, "node @ " + std::to_string(index));
                        }

                        if(index >= -positions[i]){
                            m_beg -= 1;
                            args[i] = calc(index+positions[i], -1);
                        } else{
                            args[i] = 0;
                        }
                    } else if(positions[i] > 0){
                        if(direction == -1)
                            throw Exception(Error::Expr_Logic, "node @ " + std::to_string(index));
                        
                        m_end += 1;
                        args[i] = calc(index+positions[i], 1);
                    }
                    // printf("> arg: %lf\n", args[i]);
                }

                if(is_standard_opr){
                    // printf("going with the standart opr...\n");
                    result = Operator::trigger(Operator::get_index(node.symbol), args);
                    m_cache.type = NodeType::Empty;
                } else{
                    std::vector<std::string> args_vec;
                    for(size_t i=0; i<specification->get_n_arg(); ++i){
                        std::ostringstream tmp;
                        tmp<<args[i];
                        args_vec.push_back(tmp.str());
                    }
                    m_cache.set(specification->convert(args_vec));
                    // std::cout<<"cache: "<<m_cache.expression<<'\n';
                }

                return result;
            } else{
                // TO DO
                return 0;
            }
        }
    }
}