#ifndef SEQUENCENODE_H
#define SEQUENCENODE_H

#include <vector>
#include "Behaviors/Nodes/Node.h"

namespace BT {
    
    /**
     * @brief A Node that runs its nodes in the order they were added. 
     * runs nodes 1 at a time. 
     * 
     * @tparam T the return type of the data 
     */
    template<typename T>
    class SequenceNode : public Node<T> {
    public: 
        SequenceNode(Node<T>* next, Node<T>* prev) : Node(next, prev), _nodeIdx(0) {

        }


        void AddNode(Node<T>* node) {
            if (_currentNode == nullptr) {
                _currentNode = node; 
            }
            _nodes.push_back(node);
        }

        /**
         * @brief Runs the nodes found in _nodes 1 at a time in the order 
         * they were added. 
         * 
         * @return T the type of data structure we are returning. 
         */
        T Run() override {
            if (_currentNode == nullptr) {
                return T{};
            }


            
            T ret = _currentNode->Run(); 

            if(_currentNode->IsFinished() && _nodeIdx == _nodes.size() - 1) {
                _finished = true ;
                return ret; 
            }

            if(_currentNode->IsFinished()) {
                _nodeIdx++; 
                _currentNode = _nodes[_nodeIdx];
            }



            return ret; 
        }

    private: 
        std::vector<Node<T>*> _nodes; 
        Node<T>* _currentNode; 
        int _nodeIdx; 

    };
}


#endif