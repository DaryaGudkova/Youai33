#ifndef LAB3SEM3_ARRAYSEQUENCE_H
#define LAB3SEM3_ARRAYSEQUENCE_H
#pragma once
#include "Sequence.h"
#include "DynamicArray.h"
#include <stdexcept>

#define INDEX_OUT_OF_RANGE_MESSAGE "index out of range"
#define NEGATIVE_SIZE_MESSAGE "size is negative"
#define ZERO_SIZE_MESSAGE "size is 0"


template <typename T> class ArraySequence : public Sequence<T> {
protected:
    DynamicArray<T>* array;


public:


    ArraySequence() : Sequence<T>() {
        this->array = new DynamicArray<T>();
        this->size = 0;
    }

    ArraySequence(int size) : Sequence<T>() {
        this->array = new DynamicArray<T>(size);
        this->size = size;
    }

    ArraySequence(DynamicArray<T>* array) {
        this->array = array;
        this->size = array->GetSize();
    }

    ArraySequence(T* items, int size) : Sequence<T>() {
        this->array = new DynamicArray<T>(items, size);
        this->size = size;
    }

    ArraySequence(const ArraySequence<T>& arr) {
        this->array = new DynamicArray<T>(*arr.array);
        this->size = arr.size;
    }

    T GetFirst() const override {
        return this->array->Get(0);
    }

    T GetLast() const override {
        return this->array->Get(this->size - 1);
    }

    T Get(int index) const override {
        return this->array->Get(index);
    }

    int GetSize() const override
    {
        return this->array->GetSize();
    }

    ArraySequence<T>* GetSubsequence(int startindex, int endindex) const override {
        if (startindex < 0 || startindex >= this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);
        if (endindex < 0 || endindex > this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);
        if (startindex > endindex) throw std::logic_error("endindex must be not less than startindex");

        int size = endindex - startindex;
        T* NewArray = new T[size];
        for (int i = 0; i < size; i++)
            NewArray[i] = this->array->Get(i + startindex);
        ArraySequence<T>* NewSequence = new ArraySequence<T>(NewArray, size);
        return NewSequence;
    }

    ArraySequence<T>* Concat(const Sequence<T>& list) const override {
        ArraySequence<T>* newSequence = new ArraySequence<T>(this->size + list.GetSize());
        for (int i = 0; i < this->size; i++)
            newSequence->Set(this->Get(i), i);
        for (int i = 0; i < list.GetSize(); i++)
            newSequence->Set(list.Get(i), this->size + i);
        return newSequence;
    }

    void Append(const T& item) override {
        this->array->Resize(this->size + 1);
        this->array->Set(item, this->size);
        this->size++;
    }

    void Prepend(const T& item) override {
        this->array->Resize(this->size + 1);
        T t1 = this->array->Get(0);
        T t2;
        for (int i = 0; i < this->size; i++) {
            t2 = t1;
            t1 = this->array->Get(i + 1);
            this->array->Set(t2, i + 1);
        }
        this->array->Set(item, 0);

        this->size++;
    }

    void Insert(const T &item, int index) override {
        if (index < 0 || index > this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);
        this->array->Resize(this->size + 1);
        T t1 = this->array->Get(index);
        T t2;
        for (int i = index; i < this->size; i++) {
            t2 = t1;
            t1 = this->array->Get(i + 1);
            this->array->Set(t2, i + 1);
        }
        this->array->Set(item, index);
        this->size++;
    }

    void Set(const T& item, int index) override {

        if (index < 0 || index > this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);
        this->array->Set(item, index);
    }

    void Swap(T& i, T& j){
        T tmp = i;
        i = j;
        j = tmp;
    }
    T& operator[] (const int index) const
    {

        if (index < 0 || index >= this->size) throw throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);

        return this->Get(index);

    }

    ~ArraySequence() {
        delete this->array;
        this->size = 0;
    }

};

#endif //LAB3SEM3_ARRAYSEQUENCE_H
