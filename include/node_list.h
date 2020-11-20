
#pragma once

#include "node.h"

#include <iostream>

namespace ExprEval
{
    namespace Engine
    {
        class NodeList{
            private:
            std::vector<Node> m_nodes;
            size_t m_beg, m_end;
            Node m_cache;

            public:
            NodeList(){
                m_cache.type == NodeType::Empty;
            }

            void add(Node node){
                m_nodes.push_back(node);
            }

            inline Node get(size_t index) const{
                return m_nodes[index];
            }
            inline size_t size() const{ return m_nodes.size(); }

            double calculate(size_t index);
            void print() const;

            private:
            double calc(size_t index, size_t direction=0);
        };
    } // namespace Engine
    
}
