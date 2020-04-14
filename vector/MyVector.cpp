#include "MyVector.h"
#include <iostream>

MyVector::MyVector(size_t size, ValueType value, ResizeStrategy strategy, float coef) {
    this->_size = size;
    this->_strategy = strategy;
    this->_coef = coef;

    if(_size == 0) {
        this->_capacity = 1;
    } else
        this->_capacity = std::ceil(_size*_coef);

    _data = new ValueType[_capacity];

    for (size_t i = 0; i < _size; ++i) {
        _data[i] = value;
    }
}

MyVector::MyVector(size_t size, ResizeStrategy strategy, float coef) {
    this->_size = size;
    this->_strategy = strategy;
    this->_coef = coef;
    this->_capacity = 1;

    this->_data = new ValueType[_capacity];
}


MyVector::~MyVector() {
    delete[] _data;
    _data = nullptr;
}

size_t MyVector::capacity() const {
    return _capacity;
}

size_t MyVector::size() const {
    return size_t(_size);
}

float MyVector::loadFactor() {
    return float(_size)/_capacity;
}

float MyVector::loadFactor(size_t size) {
    return float(size)/_capacity;
}

ValueType &MyVector::operator[](const size_t i) const {
    if(_size < i){
        std::cout << "i > size" << std::endl;
        return _data[0];
    } else
    return _data[i];
}

MyVector::MyVector(const MyVector &copy) {
    _size = copy._size;
    _capacity = copy._capacity;
    _strategy = copy._strategy;
    _coef = copy._coef;
    _data = new ValueType[_capacity];
    memcpy(_data, copy._data,sizeof(ValueType )* _size);
}

void MyVector::resize(const size_t size, const ValueType _default) {
    float loadF = loadFactor(size);

    if(loadF > 1) {
        _capacity = size;
        _capacity *= 2;

        ValueType* tempdata = new ValueType[_capacity];
        memcpy(tempdata, _data, size * sizeof(ValueType));
        delete[] _data;
        _data = tempdata;

        for(size_t i = _size; i < size; ++i){
            _data[i] = _default;
        }
        _size = size;
    }
    else if(loadF < 0.25) {
        _capacity = 0.5 * _capacity;
        ValueType* tempdata = new ValueType[_capacity];
        memcpy(tempdata, _data, size * sizeof(ValueType));
        delete[] _data;
        _data = tempdata;
        _size = size;
    }
    else {
        for(size_t i = _size; i < size; ++i){
            _data[i] = _default;
        }
        _size = size;
    }
}

void MyVector::reserve(const size_t capacity) {
    if(_size < capacity) {
        ValueType *tempdata = new ValueType[capacity];
        memcpy(tempdata, _data, _size * sizeof(ValueType));
        delete[] _data;
        _data = tempdata;
        _capacity = capacity;
    }
    else if(_size > capacity) {
        ValueType *tempdata = new ValueType[capacity];
        memcpy(tempdata, _data, capacity * sizeof(ValueType));
        _size = capacity;
        delete[] _data;
        _data = tempdata;
        _capacity = capacity;
    }
}

void MyVector::insert(const size_t i, const ValueType &value) {
    if(i > _size) {
        std::cout << "i > size";
        return;
    }
    if(_size == _capacity) {
        reserve(_capacity * 2);
        for(size_t j = _size; j > i; --j){
            _data[j] = _data[j - 1];
        }
    }
    else {
        for(size_t j = _size; j > i; --j){
            _data[j] = _data[j - 1];
    }
    }
    _data[i] = value;
    _size++;
}

void MyVector::insert(const size_t i, const MyVector &value) {
    for(size_t j = value.size(); j > 0; --j) {
        this->insert(i, value[j]);
    }
}

MyVector &MyVector::operator=(const MyVector &copy) {
    this->_size = copy._size;
    this->_capacity = copy._capacity;
    this->_strategy = copy._strategy;
    this->_coef = copy._coef;
    _data = new ValueType[_size];
    memcpy(this->_data, copy._data, sizeof(ValueType) * _size);
    return *this;
}

void MyVector::pushBack(const ValueType &value) {
    this->insert(_size, value);
}

void MyVector::popBack() {
    ValueType* tempdata = new ValueType[_capacity];
    memcpy(tempdata, _data, sizeof(ValueType)* (_size - 1));
    delete[] _data;
    _data = tempdata;
    --_size;
}

void MyVector::clear() {
    delete[] _data;
    _data= new ValueType[_capacity];
    _size = 0;
}

void MyVector::erase(const size_t i) {
    for(size_t j = i; j < _size - 1; ++j){
        _data[j] = _data[j + 1];
    }
    this->popBack();
}

void MyVector::erase(const size_t i, const size_t len) {
    for(size_t j = 0; j < len; ++j){
        this->erase(i);
    }
}

long long int MyVector::find(const ValueType &value, bool isBegin) const {
    if (isBegin) {
        for (size_t i = 0; i < _size; ++i)
            if (_data[i] == value)
                return i;
    }
    else {
        for (size_t i = _size - 1; i > 0; --i)
            if (_data[i] == value)
                return i;
    }
    return -1;
}

MyVector MyVector::sortedSquares(const MyVector &vec, SortedStrategy strategy) {
    for(size_t i = 0; i < vec.size(); ++i){
        vec[i] *= vec[i];
    }
    switch(strategy){
        case (SortedStrategy::Rise):
            for(size_t j = 1; j < vec.size(); ++j)
            {
                for (size_t i = 0; i < vec.size() - j; ++i) {
                    if (vec[i] > vec[i + 1]) {
                        std::swap(vec[i], vec[i + 1]);
                    }
                }
            }
            break;
        case (SortedStrategy::DeRise):
            for(size_t j = 1; j < vec.size(); ++j)
            {
                for (size_t i = 0; i < vec.size() - j; ++i) {
                    if (vec[i] < vec[i + 1]) {
                        std::swap(vec[i], vec[i + 1]);
                    }
                }
            }
            break;
    }
    return MyVector();
}
