#ifndef NODE_H
#define NODE_H

namespace BT {
    template<typename T>
    class Node {
    public: 
        Node(Node<T>* next, Node<T>* prev): _finished(false) {
            _next = next; 
            _prev = prev; 
        }

        ~Node() {
            delete _next; 
        }

        Node<T>* GetNext() {
            return _next;
        }

        Node<T>* GetLast() {
            return _prev; 
        }

        bool IsFinished() {
            return _finished;
        }

        virtual T Run() = 0;

    protected: 
        Node<T>* _next; 
        Node<T>* _prev; 
        bool _finished; 
    }; 
}

#endif