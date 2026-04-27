#include "liststack.h"
#include <iostream>

ListStack::ListStack() : _head(nullptr), _tail(nullptr), _size(0) {}

ListStack::~ListStack()
{
	while (!isEmpty())
       	{
		pop();
	}
}

ListStack::ListStack(const ListStack& other) : _head(nullptr), _tail(nullptr), _size(0) 
{
	Node* current = other._head;
	while (current) 
	{
		push(current->data);
		current = current->next;
	}
}

ListStack& ListStack::operator=(const ListStack& other)
{
	if (this != &other)
       	{
		while (!isEmpty())
	       	{
			pop();
		}
		
		Node* current = other._head;
		while (current)
	       	{
			push(current->data);
			current = current->next;
		}
	}
	return *this;
}

void ListStack::push(const ValueType& value) 
{
	Node* newNode = new Node(value);
	
	if (isEmpty())
       	{
		_head = newNode;
		_tail = newNode;
	}
	else
       	{
		newNode->prev = _tail;
		_tail->next = newNode;
		_tail = newNode;
	}
	_size++;
}

void ListStack::pop() 
{
	if (isEmpty()) return;
	
	Node* temp = _tail;
	if (_head == _tail) 
	{
		_head = nullptr;
		_tail = nullptr;
	}
	else 
	{
		_tail = _tail->prev;
		_tail->next = nullptr;
	}
	
	delete temp;
	_size--;
}

const ValueType& ListStack::top() const
{
	return _tail->data;
}

bool ListStack::isEmpty() const
{
	return _size == 0;
}

size_t ListStack::size() const
{
	return _size;
}
