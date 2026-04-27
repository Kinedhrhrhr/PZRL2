#pragma once
#include <cstddef>
#include "StackImplementation.h"

using ValueType = double;

class VectorStack : public IStackImplementation {
        private:
		ValueType* _data = nullptr;
		size_t _size = 0;
		size_t _capacity = 0;
		float _multiplicativeCoef = 2.0f;
	public:
		VectorStack() = default;
		VectorStack(const ValueType* rawArray, const size_t size, float coef = 2.0f);
		explicit VectorStack(const VectorStack& other);
		VectorStack& operator=(const VectorStack& other);
                ~VectorStack();

                void push(const ValueType& value) override;
                void pop() override;
                const ValueType& top() const override;
                bool isEmpty() const override;
                size_t size() const override;
};
