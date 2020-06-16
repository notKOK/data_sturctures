#include "ListStack.h"
#include <cstdlib>
#include <stdexcept>

ListStack::ListStack(const ListStack& copyList)  : LinkedList(copyList) {
}

void ListStack::push(const ValueType& value)
{
    this->pushFront(value);
}

void ListStack::pop()
{
    if (ListStack::size() == 0) {
        throw std::out_of_range("Invalid index");
    }
    else {
        removeFront();
    }
}

size_t ListStack::size() const
{
    return LinkedList::size();
}

const ValueType& ListStack::top() const
{
    return this->operator[](0);
}

bool ListStack::isEmpty() const
{
    return (LinkedList::size() == 0);
}