#pragma once
#ifndef CLIONPROJECTS_MYVECTOR_H
#define CLIONPROJECTS_MYVECTOR_H
#include <cstdlib>
#include <cmath>
#include <cstring>

// стратегия изменения capacity
enum class ResizeStrategy {
    Additive,
    Multiplicative
};

enum class SortedStrategy {
    Rise,
    DeRise
};

// тип значений в векторе
// потом будет заменен на шаблон
using ValueType = double;

class Iterator {

public:
    Iterator() { ptr = nullptr; };

    Iterator(ValueType *p) : ptr(p) {};

    Iterator(const Iterator &it) : ptr(it.ptr) {};

    Iterator operator+(int n) { return Iterator(ptr + n); }

    Iterator operator-(int n) { return Iterator(ptr - n); }

    Iterator operator++() { return ++ptr; }

    Iterator operator--() { return --ptr; }

    Iterator operator++(int) { return ptr++; }

    Iterator operator--(int) { return ptr--; }

    bool operator!=(const Iterator &it) const { return ptr != it.ptr; }

    bool operator==(const Iterator &it) const { return ptr == it.ptr; }

    ValueType &operator*() { return *ptr; }

private:
    ValueType *ptr;
};

class MyVector
{
public:

    MyVector (size_t size = 0, ResizeStrategy = ResizeStrategy::Multiplicative, float coef = 1.5f);
    MyVector (size_t size, ValueType value, ResizeStrategy = ResizeStrategy::Multiplicative, float coef = 1.5f);

    MyVector (const MyVector& copy);
    MyVector& operator= (const MyVector& copy);

    ~MyVector();

    // для умненьких — реализовать конструктор и оператор для перемещения

    size_t capacity() const;
    size_t size() const;
    float loadFactor();
    float loadFactor(size_t size);
    // доступ к элементу,
    // должен работать за O(1)
    ValueType& operator[](const size_t i) const;

    // добавить в конец,
    // должен работать за amort(O(1))
    void pushBack(const ValueType& value);
    // вставить,
    // должен работать за O(n)
    void insert(const size_t i, const ValueType& value);	// версия для одного значения
    void insert(const size_t i, const MyVector& value);		// версия для вектора

    // удалить с конца,
    // должен работать за amort(O(1))
    void popBack();
    // удалить
    // должен работать за O(n)
    void erase(const size_t i);
    void erase(const size_t i, const size_t len);			// удалить len элементов начиная с i

    // найти элемент,
    // должен работать за O(n)
    // если isBegin == true, найти индекс первого элемента, равного value, иначе последнего
    // если искомого элемента нет, вернуть -1
    long long int find(const ValueType& value, bool isBegin = true) const;

    Iterator begin() { return Iterator(_data); };
    Iterator end() { return Iterator(_data + _size); };

    // зарезервировать память (принудительно задать capacity)
    void reserve(const size_t capacity);

    // изменить размер
    // если новый размер больше текущего, то новые элементы забиваются дефолтными значениями
    // если меньше - обрезаем вектор
    void resize(const size_t size, const ValueType = 0.0);

    MyVector sortedSquares(const MyVector& vec, SortedStrategy strategy);
    // очистка вектора, без изменения capacity
    void clear();

private:
    ValueType* _data;
    size_t _size;
    size_t _capacity;
    ResizeStrategy _strategy;
    float _coef;

};

#endif //CLIONPROJECTS_MYVECTOR_H
