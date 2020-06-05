#include "LinkedList.h"

#include <cassert>
#include <bits/exception.h>
#include <stdexcept>

LinkedList::Node::Node(const ValueType& value, Node* next)
{
	this->value = value;
	this->next = next;
}

LinkedList::Node::~Node()
{
	// ничего не удаляем, т.к. агрегация
}

void LinkedList::Node::insertNext(const ValueType& value)
{
	Node* newNode = new Node(value, this->next);
	this->next = newNode;
}

void LinkedList::Node::removeNext()
{
    if (this->next == nullptr) return;
	Node* removeNode = this->next;
	Node* newNext = removeNode->next;
	delete removeNode;
	this->next = newNext;
}

LinkedList::LinkedList() : _head(nullptr), _size(0){}

LinkedList::LinkedList(const LinkedList& copyList)
{
    if (this == &copyList) return;
    _size = copyList._size;
    if (_size == 0 || copyList._head == nullptr) {
        _size = 0;
        _head = nullptr;
        return;
    }

    _head = new Node(copyList._head->value);

    Node* currentNode = _head;
    Node* currentCopyNode = copyList._head;

    while (currentCopyNode->next) {
        currentCopyNode = currentCopyNode->next;
        currentNode->next = new Node(currentCopyNode->value);
        currentNode = currentNode->next;
    }
}

LinkedList& LinkedList::operator=(const LinkedList& copyList)
{
    if (this == &copyList) {
        return *this;
    }
    LinkedList bufList(copyList);
    this->_size = bufList._size;
    this->_head = new Node(bufList._head->value);
    Node* cur = _head;
    Node* curCopy = bufList._head;

    while (curCopy->next != nullptr)
    {
        cur->next = new Node(curCopy->next->value);
        cur = cur->next;
        curCopy = curCopy->next;
    }

    return *this;
}

LinkedList::LinkedList(LinkedList&& moveList) noexcept
{
	this->_size = moveList._size;
	this->_head = moveList._head;

	moveList._size = 0;
	moveList._head = nullptr;
}

LinkedList& LinkedList::operator=(LinkedList&& moveList) noexcept
{
	if (this == &moveList) {
		return *this;
	}
	forceNodeDelete(_head);
	this->_size = moveList._size;
	this->_head = moveList._head;

	moveList._size = 0;
	moveList._head = nullptr;

	return *this;
}

LinkedList::~LinkedList()
{
	forceNodeDelete(_head);
}

ValueType& LinkedList::operator[](const size_t pos) const
{
	return getNode(pos)->value;
}

LinkedList::Node* LinkedList::getNode(const size_t pos) const
{
    if (pos < 0 || pos >= this->_size) {
        throw std::out_of_range("Invalid index");
    }

	Node* bufNode = this->_head;
	for (int i = 0; i < pos; ++i) {
		bufNode = bufNode->next;
	}

	return bufNode;
}

void LinkedList::insert(const size_t pos, const ValueType& value)
{
    if ((pos < 0) || (pos > this->_size)) {
        throw std::out_of_range("Invalid index");
    }
	if (pos == 0) {
		pushFront(value);
	}
	else {
		Node* bufNode = this->_head;
		for (size_t i = 0; i < pos-1; ++i) {
			bufNode = bufNode->next;
		}
		bufNode->insertNext(value);
		++_size;
	}
}

void LinkedList::insertAfterNode(Node* node, const ValueType& value)
{
    if (node == nullptr) return;
	node->insertNext(value);
	++_size;
}

void LinkedList::pushBack(const ValueType& value)
{
	if (_size == 0) {
		pushFront(value);
		return;
	}
	insert(_size, value);
}

void LinkedList::pushFront(const ValueType& value)
{
	_head = new Node(value, _head);
	++_size;
}

void LinkedList::remove(const size_t pos)
{
    if ((pos < 0) || (pos >= this->_size)) {
        throw std::out_of_range("Invalid index");
    }
    if (pos != 0) {
        Node* temp = _head;
        for (size_t i = 0; i < pos - 1; i++)
            temp = temp->next;

        Node* newNode = temp->next;
        temp->next = temp->next->next;
        delete newNode;
        --_size;
    }
    else
        removeFront();
}

void LinkedList::removeNextNode(Node* node)
{
    if (node == nullptr) {
            throw std::out_of_range("Invalid index");
    }
    if(node->next->next == nullptr){
        removeBack();
        return;
    }
    else {
        Node* target = node->next;
        node->next = node->next->next;
        delete target;
        --_size;
    }

    
}

long long int LinkedList::findIndex(const ValueType& value) const
{
    Node* current = _head;
    long long int counter = 0;
    while(current->value != value){
        current = current->next;
        ++counter;
        if(current == nullptr){
            counter = -1;
            break;
        }
    }
	return counter;
}

LinkedList::Node* LinkedList::findNode(const ValueType& value) const
{
    Node* current = _head;
    while(current->value != value){
        current = current->next;
        if(current == nullptr){
            break;
        }
    }
	return current;
}

void LinkedList::reverse()
{
    Node* current = _head, *next, *prev = nullptr;
    while(current != nullptr)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    _head = prev;
}

LinkedList LinkedList::reverse() const
{
    LinkedList list(*this);
    list.reverse();
    list._size = _size;

    return list;
}

LinkedList LinkedList::getReverseList() const
{
    LinkedList list(*this);
	list.reverse();
	return list;
}

size_t LinkedList::size() const
{
	return _size;
}

void LinkedList::forceNodeDelete(Node* node)
{
	if (node == nullptr) {
		return;
	}
    try {
        Node* nextDeleteNode = node->next;
        delete node;
        forceNodeDelete(nextDeleteNode);
    }
	catch (const std::exception & ex){
        ex.what();
        return;
	}
}

void LinkedList::removeFront() {
    if (_head == nullptr)
        return;

    Node* temp = _head;
    _head = _head->next;
    delete temp;
    --_size;
}

void LinkedList::removeBack() {
    remove(_size - 1);
}
