#pragma once
#include <iostream>

namespace names
{
    struct Node
    {
        double data;
        Node* next;
        Node(double val, Node* ptr = nullptr);
    };

    class ForwardList
    {
    private:
        Node* head;
        size_t S;

    public:
        ForwardList();
        ~ForwardList();

        void push_front(double x);
        void pop_front();
        double& front();
        const double& front() const;
        size_t size() const;
        bool empty() const;
        void display() const;
        void erase(double x);
        void clear();

        Node* get_node(size_t index) const;
        std::pair<Node*, size_t> find_cycle();
    };
}
