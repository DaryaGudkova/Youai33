#ifndef LAB3SEM3_SEQUENCE_H
#define LAB3SEM3_SEQUENCE_H
#pragma once

#include <stdexcept>
#define INDEX_OUT_OF_RANGE_MESSAGE "index out of range"

template <class T>
class Sequence
{
public:
    int size = 0;
public:

    Sequence() = default;

    virtual T GetFirst() const = 0;
    virtual T GetLast() const = 0;
    virtual T Get(const int index) const = 0;
    virtual int GetSize() const { return this->size; }
    virtual Sequence<T>* GetSubsequence(const int start_index, const int end_index) const = 0;
    virtual void Append(const T &value) = 0;
    virtual void Prepend(const T &value) = 0;
    //virtual void Swap(const T& i, const T& j) = 0;
    virtual void Set(const T& data, int index) = 0;
    virtual void Insert(const T &value, const int index) {};
    virtual Sequence<T>* Concat(const Sequence<T>& seq) const = 0;
    virtual bool operator==(const Sequence<T>& seq) {
        if (this->size != seq.size) return false;

        for (int i = 0; i < this->size; i++) {
            if (this->Get(i) != seq.Get(i)) return false;
        }
        return true;
    }
    virtual bool operator==(const Sequence<T>* seq) {
        if (this->size != seq->size) return false;

        for (int i = 0; i < this->size; i++) {
            if (this->Get(i) != seq->Get(i)) return false;
        }
        return true;
    }
    ~Sequence() = default;

    T& operator [] (const int index) const
    {

        if (index < 0 || index >= this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);

        return this->Get(index);

    }
};
#endif //LAB3SEM3_SEQUENCE_H
