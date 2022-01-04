#ifndef INTERFACE_CPP_MATRIX_H
#define INTERFACE_CPP_MATRIX_H

#pragma once

#include "Sequence.h"
#include <cmath>
#include "LinkedListSequence.h"

using namespace std;

template <class T> class Matrix
{
private:

    Sequence<Sequence<T>*>* elements;
    int rows = 0;
    int columns = 0;

public:
    Matrix()
    {
        this->elements = new ListSequence<ListSequence<T>*>;
        this->rows = 0;
        this->columns = 0;
    }

    Matrix(const Matrix<T>& matrix)
    {
        this->elements = new ListSequence<ListSequence<T>*>(matrix.elements);
        this->rows = matrix.rows;
        this->columns = matrix.columns;
    }

    Matrix(const int rows, const int columns)
    {
        if (rows < 0)
        {
            throw out_of_range("Negative size!");
        }
        if (columns < 0)
        {
            throw out_of_range("Negative size!");
        }
        if (rows == 0 || columns == 0)
        {
            this->rows = 0;
            this->columns = 0;
        } else
        {
            this->rows = rows;
            this->columns = columns;
        }
        this->elements = (Sequence<Sequence<T>*>*) new ListSequence<ListSequence<T>*>;
        for (int i = 0; i < rows; i++)
        {
            this->elements->Append(new ListSequence<T>(this->columns));
        }
    }

    ~Matrix(){
        delete this->elements;
        this->columns = 0;
        this->rows = 0;
    }

    Matrix operator+(const Matrix<T>& matr)
    {
        if (this->rows != matr.rows)
        {
            throw invalid_argument("Wrong number!");
        }
        if (this->columns != matr.columns)
        {
            throw invalid_argument("Wrong number!");
        }
        Matrix result(this->rows, this->columns);
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < this->columns; j++)
            {
                result->Set(this->get(i, j) + matr->get(i, j), i);
            }
        }
        return result;
    }
    Matrix operator=(const Matrix<T>& matr)
    {
        this->rows = matr.rows;
        this->columns = matr.columns;
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < this->columns; j++)
            {
                this->elements->set(matr.elements->get(i, j), i, j);
            }
        }
    }

    int GetRows()
    {
        return this->rows;
    }

    int GetColumns()
    {
        return this->columns;
    }

    T Get(const int i, const int j)
    {
        if (i < 0 || i >= this->rows || j < 0 || j >= this->columns) throw std::out_of_range("Index out of range!");

        return elements->Get(i)->Get(j);
    }

    void Set(T element, int i, int j)
    {
        if (i < 0 || i >= this->rows || j < 0 || j >= this->columns) throw std::out_of_range("Index out of range!");

        this->elements->Get(i)->Set(j, element);
    }

    Matrix operator*(const Matrix<T>& matr)
    {
        if (this->columns != matr.rows)
        {
            throw invalid_argument("Wrong number!");
        }
        Matrix result(this->columns, matr.columns);
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < matr.columns; j++)
            {
                T sum = 0;
                for (int k = 0; k < this->columns; k++)
                {
                    sum = sum + (T)(this->Get(i, k)) + (T)(matr.get(k, j));
                }
                result.Set(sum, i, j);
            }
        }
        return result;
    }

};
#endif //INTERFACE_CPP_MATRIX_H
