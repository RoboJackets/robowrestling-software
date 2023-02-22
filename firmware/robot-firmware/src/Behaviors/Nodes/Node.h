#ifndef NODE_H
#define NODE_H

namespace BT {
    template<typename T, typename U> // T is inputs, U is outputs
    class Node {
    public: 
        Node(Node<T, U>* next, Node<T, U>* prev): _finished(false) {
            _next = next; 
            _prev = prev; 
        }

        ~Node() {
            delete _next; 
        }

        Node<T, U>* GetNext() {
            return _next;
        }

        Node<T, U>* GetLast() {
            return _prev; 
        }

        bool IsFinished() {
            return _finished;
        }

        virtual U Run(T inputs) = 0;

    protected: 
        Node<T, U>* _next; 
        Node<T, U>* _prev; 
        bool _finished; 
    }; 
}

#endif