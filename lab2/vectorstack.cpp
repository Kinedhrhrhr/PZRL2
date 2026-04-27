#include "vectorstack.h"
#include <iostream>
#include <stdexcept>

VectorStack::VectorStack(const ValueType* rawArray, const size_t size, float coef) {
	_size = size;
	_capacity = size;
	_multiplicativeCoef = coef;

        if (_capacity > 0) {
                _data = new ValueType[_capacity];
                for (size_t i = 0; i < _size; ++i) {
                        _data[i] = rawArray[i];
                }
        }
        else {
                _data = nullptr;
        }
}

VectorStack::VectorStack(const VectorStack& other) {
        *this = other;
}

VectorStack& VectorStack::operator=(const VectorStack& other) {
        if (this != &other) {
                delete[] _data;
                _size = other._size;
                _capacity = _size;
                _multiplicativeCoef = other._multiplicativeCoef;

                if (_size > 0) {
                        _data = new ValueType[_size];
                        for (size_t i = 0; i < _size; ++i) {
                                _data[i] = other._data[i];
                        }
                }
                else {
                        _data = nullptr;

                }
        }
        return *this;
}

VectorStack::~VectorStack()
{
        delete[] _data;
}

void VectorStack::push(const ValueType& value)
{
	if (_size == _capacity)
       	{
                size_t newCapacity = (_capacity == 0) ? (size_t)_multiplicativeCoef : (size_t)(_capacity * _multiplicativeCoef);

                ValueType* newData = new ValueType[newCapacity];
                for (size_t i = 0; i < _size; ++i)
	       	{
                        newData[i] = _data[i];
                }
                delete[] _data;
                _data = newData;
                _capacity = newCapacity;
        }
        _data[_size] = value;
        _size++;
}

void VectorStack::pop() 
{
	if (_size == 0)
       	{
                throw std::out_of_range("Vector is empty");
        }
        _size--;
}

const ValueType& VectorStack::top() const 
{
	if (isEmpty()) 
	{
		throw std::out_of_range("Vector is empty");
	}
	return _data[_size - 1];
}

bool VectorStack::isEmpty() const 
{
	return _size == 0;
}

size_t VectorStack::size() const
{
	return _size;
}
