#pragma once

#include"StackImplementation.h"
#include "LinkedList.h"

// вариант с использованием ранее написанного списка и множественного наследования
// если бы список не был реализован, то было бы наследование только от интерфейса
// множественное наследование можно заменить на композицию
class ListStack : public StackImplementation, public LinkedList
{ ;
    public:
    ListStack() {}

    ListStack(const ListStack& copyList);

    void push(const ValueType& value) override;

    void pop() override;

    const ValueType& top() const;

    bool isEmpty() const override;

    size_t size() const override;

    ~ListStack() override = default;

};
