#include "MyVector.h"
#include <cmath>
#include <iostream>
static int iv = 1;
MyVector::MyVector(size_t size, ValueType value, ResizeStrategy strategy, float coef) {
    this->_size = size;
    this->_strategy = strategy;
    this->_coef = coef;
    _capacity = 1;
    this->id = iv;
    iv++;

    if(_size != 0) {
        _capacity = recount_capacity(_size, strategy);
    }
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
    this->_capacity = recount_capacity(_size, strategy);

    this->id = iv;
    iv++;

    this->_data = new ValueType[_capacity];
    for(int i = 0; i < _size; i++){
        _data[i] = ValueType();
    }
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
    try{
        return _data[i];
    }
    catch (const std::exception & ex) {
        std::cout << ex.what() << std::endl;
        std::cout << "  i <= _size  " << std::endl;
    }
}

MyVector::MyVector(const MyVector &copy) {
    if(copy._data == nullptr) return;
    _size = copy._size;
    _capacity = copy._capacity;
    _strategy = copy._strategy;
    _coef = copy._coef;
    _data = new ValueType[_capacity];
    memcpy(_data, copy._data,sizeof(ValueType )* _size);
    this->id = iv;
    iv++;
}

void MyVector::resize(const size_t size, const ValueType _default) {
    float loadF = loadFactor(size);
    _capacity = recount_capacity(size, _strategy);

    if(loadF > 1) {
        ValueType* tempdata = new ValueType[_capacity];
        memcpy(tempdata, _data, _size * sizeof(ValueType));
        delete[] _data;
        _data = tempdata;

        for(size_t i = _size; i < size; ++i){
            _data[i] = _default;
        }
    }
    else if(loadF < 1/(_coef * _coef)) {
        ValueType* tempdata = new ValueType[_capacity];
        memcpy(tempdata, _data, size * sizeof(ValueType));
        delete[] _data;
        _data = tempdata;
    }
    else {
        for(size_t i = _size; i < size; ++i){
            _data[i] = _default;
        }
    }
    _size = size;
}

void MyVector::reserve(const size_t capacity) {
    try {
        if (_size <= capacity) {
            ValueType *tempdata = new ValueType[capacity];
            memcpy(tempdata, _data, _size * (sizeof(ValueType)));
            delete[] _data;
            _data = tempdata;
            _capacity = capacity;
        } else if (_size >= capacity) {
            ValueType *tempdata = new ValueType[capacity];
            memcpy(tempdata, _data, capacity * sizeof(ValueType));
            _size = capacity;
            delete[] _data;
            _data = tempdata;
            _capacity = capacity;
        }
    }
    catch (const std::exception & ex) {
        std::cout << ex.what() << std::endl;
        std::cout << "  reserve dead  " << std::endl;
    }
}

void MyVector::insert(const size_t i, const ValueType &value) {
    if(i > _size) {
        std::cout << "i > size";
        return;
    }
    if(_size == _capacity) {
        _capacity = recount_capacity(_size + 1, _strategy);
        reserve(_capacity);
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
    if(i > _size) return;

    size_t allsize = value._size + _size;
    _capacity = recount_capacity(allsize, _strategy);
    ValueType* tempdata= new ValueType[_capacity];

    for(size_t j = 0; j < i; ++j){
        tempdata[j] = _data[j];
    }
    size_t delta = value._size + i;
    for(size_t j = i; j < delta; ++j){
        tempdata[j] = value[j - i];
    }
    for(size_t j = delta; j < allsize; ++j){
        tempdata[j] = _data[j - value._size];
    }
    delete[] _data;
    _data = tempdata;
    _size = allsize;
}

MyVector &MyVector::operator=(const MyVector &copy) {
    if((&copy == this) || (copy._data == nullptr)) return *this;
    this->_size = copy._size;
    this->_capacity = copy._capacity;
    this->_strategy = copy._strategy;
    this->_coef = copy._coef;
    delete[] _data;
    _data = new ValueType[_size];
    memcpy(this->_data, copy._data, sizeof(ValueType) * _size);
    return *this;
}

void MyVector::pushBack(const ValueType &value) {
    this->insert(_size, value);
}

void MyVector::popBack() {
    if(_size == 0) return;
    _size--;
    size_t newcap = recount_capacity(_size, _strategy);
    reserve(newcap);
}

void MyVector::clear() {
    _size = 0;
}

void MyVector::erase(const size_t i) {
    if(i >= _size) return;
    for(size_t j = i; j < _size - 1; ++j){
        _data[j] = _data[j + 1];
    }
    this->popBack();
}

size_t MyVector::Partition(ValueType* data, size_t l, size_t r,bool* mew,  SortedStrategy sstrategy) {
    if(!mew[r]) {
        data[r] *= data[r];
        mew[r] = true;
    }
    ValueType x = data[r];
    size_t less = l;
    if(!mew[less]) {
        data[less] *= data[less];
        mew[less] = true;
    }

    switch(sstrategy){
        case(SortedStrategy::Rise):
            for (int i = l; i < r; ++i) {
                if(!mew[i]) {
                    data[i] *= data[i];
                    mew[i] = true;
                }
                if(!mew[less]) {
                    data[less] *= data[less];
                    mew[less] = true;
                }
                if (data[i] <= x) {
                    std::swap(data[i], data[less]);
                    ++less;
                }
            }
            break;
        case(SortedStrategy::DeRise):
            for (int i = l; i < r; ++i) {
                if(!mew[i]) {
                    data[i] *= data[i];
                    mew[i] = true;
                }
                if(!mew[less]) {
                    data[less] *= data[less];
                    mew[less] = true;
                }
                if (data[i] >= x) {
                    std::swap(data[i], data[less]);
                    ++less;
                }
            }
            break;
    }
    if(!mew[less]) {
        data[less] *= data[less];
        mew[less] = true;
    }
    std::swap(data[less], data[r]);
    return less;
}


void MyVector::QuickSortImpl(ValueType* data, size_t l, size_t r,bool* mew, SortedStrategy sstrategy, size_t Q) {
    if (l < r && (Q - 1 <= Q) && ((Q + 1) != 0) && (r + 1 != 0) && (r - 1 <= r)) {
        Q = Partition(data, l, r, mew, sstrategy);
        QuickSortImpl(data, l, Q - 1, mew, sstrategy);
        QuickSortImpl(data, Q + 1, r, mew, sstrategy);
    }
}

MyVector MyVector::sortedSquares(const MyVector &vec, SortedStrategy strategy) {
    if (vec.size() != 0) { //!values.empty()
        MyVector Mee = vec;
        bool *mew = new bool[Mee._size]{};
        QuickSortImpl(Mee._data, 0, Mee._size - 1,mew, strategy); //values.size()
        for(int i = 0; i < Mee._size; i++){
            if(!mew[i]) Mee._data[i] *= Mee._data[i];
        }
        return Mee;
    }
    else { return *this; }
}

void MyVector::erase(const size_t i, const size_t len) {
    size_t len_i = len + i;
    if((i >= _size) || len_i > _size) return;
    _capacity = recount_capacity(_size - len, _strategy);
    ValueType* tempdata = new ValueType[_capacity];

    for(size_t j = 0; j < i; ++j){
        tempdata[j] = _data[j];
    }
    for(size_t j = len_i; j < _size; ++j){
        tempdata[j - len] = _data[j];
    }
    delete[] _data;
    _data = tempdata;
    _size -= len;
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

size_t MyVector::recount_capacity(size_t size, ResizeStrategy strategy){
    float loadF = loadFactor(size);
    float divCoef = 1 / (_coef * _coef);
    if((loadF <= 1) && (loadF >= divCoef)){
        return _capacity;
    }
    else if(size == 0) {
        return 1;
    }

    switch(strategy){
        case ResizeStrategy::Additive:
            return ceil(size + _coef);

        case ResizeStrategy::Multiplicative:
            return ceil(size * _coef);
    }
    return _capacity;
}

size_t MyVector::idexx() {
    return id;
}