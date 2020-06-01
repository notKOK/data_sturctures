#include "LinkedList.h"

#include <cassert>

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
	Node* removeNode = this->next;
	Node* newNext = removeNode->next;
	delete removeNode;
	this->next = newNext;
}

LinkedList::LinkedList() : _head(nullptr), _size(0){}

LinkedList::LinkedList(const LinkedList& copyList)
{
    _size = copyList._size;
    if (_size == 0) {
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
	this->_head = bufList._head;

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
    assert(!(pos < 0 || pos >= this->_size));

	Node* bufNode = this->_head;
	for (int i = 0; i < pos; ++i) {
		bufNode = bufNode->next;
	}

	return bufNode;
}

void LinkedList::insert(const size_t pos, const ValueType& value)
{
    assert(!(pos < 0 || pos > this->_size));

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
    assert(node == nullptr);
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
    assert(pos >= _size || pos < 0);
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
    assert(node == nullptr);
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
    Node* prev = nullptr;
    Node* next = nullptr;
    Node* curr = list._head;

    while (curr != nullptr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    list._head = prev;
    list._size = _size;

    return list;
}

LinkedList LinkedList::getReverseList() const
{
	reverse();
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

	Node* nextDeleteNode = node->next;
	delete node;
	forceNodeDelete(nextDeleteNode);
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
