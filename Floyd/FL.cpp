#include "FL.h"
#include <iostream>
namespace names
{
    Node::Node(double val, Node* ptr) : data(val), next(ptr) {}

    ForwardList::ForwardList() : head(nullptr), S(0) {}

    ForwardList::~ForwardList()
    {
        clear();
    }

    void ForwardList::push_front(double x)
    {
        Node* newNode = new Node(x, head);
        head = newNode;
        S += 1;
    }

    void ForwardList::pop_front()
    {
        if (empty())
        {
            std::cout << "Список пуст." << std::endl;
            return;
        }
        Node* temp = head;
        head = head->next;
        delete temp;
        S -= 1;
    }

    double& ForwardList::front()
    {
        if (empty())
        {
            std::cout << "Список пуст." << std::endl;
        }
        return head->data;
    }

    const double& ForwardList::front() const
    {
        if (empty())
        {
            std::cout << "Список пуст." << std::endl;
        }
        return head->data;
    }

    size_t ForwardList::size() const
    {
        return S;
    }

    bool ForwardList::empty() const
    {
        return head == nullptr;
    }
    void ForwardList::display() const
    {
            if (empty())
            {
                std::cout << "Список пуст." << std::endl;
                return;
            }
            Node* A = head;
            std::cout << "Список: ";
            int count = 0;
            while (A != nullptr && count < 15)
            {
                std::cout << A->data << " ";
                A = A->next;
                count++;
            }
            if (A != nullptr) {std::cout << "...";}
            std::cout << std::endl;
    }

    void ForwardList::erase(double x)
    {
        while (head != nullptr && head->data == x) {
            Node* temp = head;
            head = head->next;
            delete temp;
            S -= 1;
        }

        if (head == nullptr)
        {
            std::cout << "Теперь список пуст." << std::endl;
            return;
        }

        Node* A = head;
        while (A->next != nullptr)
        {
            if (A->next->data == x)
            {
                Node* temp = A->next;
                A->next = temp->next;
                delete temp;
                S -= 1;
            }
            else
            {
                A = A->next;
            }
        }
    }

    void ForwardList::clear()
    {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        S = 0;
    }

    Node* ForwardList::get_node(size_t index) const
    {
        if (head == nullptr || index >= S)
            return nullptr;

        Node* current = head;
        for (size_t i = 0; i < index; ++i)
            current = current->next;

        return current;
    }

    std::pair<Node*, size_t> ForwardList::find_cycle()
    {
        if (head == nullptr)
            return std::pair<Node*, size_t>(nullptr, 0);

        Node* tortoise = head;
        Node* hare = head;

        while (hare != nullptr && hare->next != nullptr)
        {
            tortoise = tortoise->next;
            hare = hare->next->next;

            if (tortoise == hare)
            {
                tortoise = head;
                while (tortoise != hare)
                {
                    tortoise = tortoise->next;
                    hare = hare->next;
                }

                Node* cycle_start = tortoise;
                size_t cycle_length = 1;
                Node* current = cycle_start->next;

                while (current != cycle_start)
                {
                    cycle_length++;
                    current = current->next;
                }

                return std::pair<Node*, size_t>(cycle_start, cycle_length);
            }
        }

        return std::pair<Node*, size_t>(nullptr, 0);
    }
}
