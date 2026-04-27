#pragma once
#include <cstddef>
#include "StackImplementation.h"

class ListStack : public IStackImplementation 
{
	private:
		struct Node 
		{
			ValueType data;
			Node* next;
			Node* prev;
			Node(const ValueType& val) : data(val), next(nullptr), prev(nullptr) {}
		};
		Node* _head = nullptr;
		Node* _tail = nullptr;
		size_t _size = 0;
	
	public:
		ListStack();
		~ListStack();
		ListStack(const ListStack& other);
		ListStack& operator=(const ListStack& other);

		void push(const ValueType& value) override;
		void pop() override;
		const ValueType& top() const override;
		bool isEmpty() const override;
		size_t size() const override;
};
