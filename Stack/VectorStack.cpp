#include "VectorStack.h"
#include <cstdlib>
#include <stdexcept>

void VectorStack::push(const ValueType& value) {
    this->pushBack(value);
}

void VectorStack::pop() {
    if (VectorStack::size() == 0) {
        throw std::out_of_range("Invalid index");
    }
    else {
        this->popBack();
    }
}

const ValueType& VectorStack::top() const {
    return this->operator[](size() - 1);
}

bool VectorStack::isEmpty() const {
    return (MyVector::size() == 0);
}

size_t VectorStack::size() const {
    return  MyVector::size();
}