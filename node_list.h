
#pragma once

#include "node.h"

#include <iostream>

namespace ExprEval
{
    namespace Engine
    {
        class NodeList{
            private:
            // Node *m_head = nullptr, *m_tail = nullptr;
            std::vector<Node> m_nodes;
            // size_t m_index = 0;
            size_t m_beg, m_end;

            public:
            ~NodeList(){
                // Node* current = m_head->next;
                // while(current){
                //     delete m_head;
                //     m_head = current;
                //     current = m_head->next;
                // }
            }

            void add(Node node){
                // if(m_index == 0){
                //     m_head = node;
                //     m_head->prev = nullptr;
                //     m_head->next = nullptr;
                //     m_tail = m_head;
                // }
                // ++m_index;

                // m_tail->next = node;
                // node->prev = m_tail;

                // m_tail = node;
                m_nodes.push_back(node);
            }
            void insert(Node* node, size_t index, bool head=true);
            void remove(size_t index, bool head=true);

            inline Node get(size_t index) const{
                // Node* current = m_head;
                // for(size_t i=0; i<index; ++i){
                //     current = current->next;
                // }
                // return current;
                return m_nodes[index];
            }
            inline size_t size() const{ return m_nodes.size(); }

            double calculate(size_t index){
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

            void print(){
                for(size_t i=0; i<m_nodes.size(); ++i){
                    Node* node = &(m_nodes[i]);
                    std::string type = "expr";
                    if(node->type == ExprEval::NodeType::Number){
                        type = "num";
                    } else if(node->type == ExprEval::NodeType::Operator){
                        type = "opr";
                    }
                    std::cout<<"["<<type<<"]"<<"{";
                    if(node->type == ExprEval::NodeType::Number){
                        std::cout<<node->number;
                    } else if(node->type == ExprEval::NodeType::Operator){
                        std::cout<<node->symbol;
                    } else{
                        std::cout<<node->expression;
                    }
                    std::cout<<"} --> ";
                }
            }

            private:
            double calc(size_t index, size_t direction=0){
                // return 0;
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
        };
    } // namespace Engine
    
}
