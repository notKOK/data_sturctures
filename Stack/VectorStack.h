#pragma once
#include "StackImplementation.h"
#include "MyVector.h"


// вариант с использованием ранее написанного вектора и множественного наследования
// если бы вектор не был реализован, то было бы наследование только от интерфейса
// множественное наследование можно заменить на композицию
class VectorStack : public StackImplementation, public MyVector
{ ;
public:
    VectorStack() {}

    VectorStack(VectorStack& list) : MyVector(list) {};

    void push(const ValueType& value) override;

    void pop() override;

    const ValueType& top() const;

    bool isEmpty() const override;

    size_t size() const override;

};

