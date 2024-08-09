#ifndef CONDITIONAL_NODE_H 
#define CONDITIONAL_NODE_H 

#include "Behaviors/Nodes/Node.h"
#include "functional"
#include "utility"

using Callback = std::function<bool ()>; 
namespace BT {

    /**
     * @brief A Node that uses a condtional to decide what chain to follow. 
     * 
     * @tparam T the input state
     * @tparam U the output state 
     */
    template<typename T, typename U>
    class ConditionalNode : public Node<T,U> {
        
        private: 
            Node<T,U> *_nodeIfFalse; 

            Callback _supplier; 

        public: 

            /**
             * @brief Construct a new Conditional Node object
             * 
             * @param next the node to run if the conditonal is true 
             * @param prev the previous node in the chain 
             * @param fallback the node to run if the conditional is false 
             * @param func the conditional to check every tick
             */
            ConditionalNode(Node<T,U> next, Node<T,U> prev, Node<T,U> fallback,
                Callback func): Node<T,U>(next, prev), _supplier(std::move(func)) {
                    _nodeIfFalse = fallback;
            }

            U Run(T inputs) override {
                // TODO maybe find a better to do this 

                /* Conditional node is never finished, it just checks the 
                   predicate and runs the respective nodes 
                */

                U ret; 
                if (_supplier()) {
                    ret = this->_next->Run(inputs); 
                } else {
                    ret = _nodeIfFalse->Run(inputs); 
                }


                return ret;
            }        

    };

};




#endif 