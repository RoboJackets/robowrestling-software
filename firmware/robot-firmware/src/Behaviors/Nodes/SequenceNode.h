#ifndef SEQUENCENODE_H
#define SEQUENCENODE_H

#include <vector>
#include "Behaviors/Nodes/Node.h"

namespace BT {
    
    /**
     * @brief A Node that runs its nodes in the order they were added. 
     * runs nodes 1 at a time. 
     * 
     * @tparam T the inputs type of the sensors
     * @tparam U the output type of the node
     */
    template<typename T, typename U>
    class SequenceNode : public Node<T, U> {
    public: 
        SequenceNode(Node<T, U>* next, Node<T, U>* prev) : Node(next, prev), _nodeIdx(0) {

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
         * @param inputs the sensor inputs to the robot
         * @return U the type of data structure we are returning. 
         */
        U Run(T inputs) override {
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