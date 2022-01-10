#ifndef INTERFACE_CPP_SORTS_H
#define INTERFACE_CPP_SORTS_H
#include "Sequence.h"


#pragma once
template<typename T>
class Sorts{
public:
    static void Swapper(Sequence<T> *seq, int i, int j) {
        T temp = seq->Get(i);
        seq->Set(i, seq->Get(j));
        seq->Set(j, temp);
    }

    static void BubbleSort(Sequence<T> *seq, int (*cmp)(T, T)) { //O(n^2)
        int size = seq->GetSize();
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (cmp((seq->Get(j)), (seq->Get(j + 1)))) {
                    Swapper(seq, j, j + 1);
                }
            }
        }
    }

    static Sequence<T>* BubbleSortClone(Sequence<T> *seq, int (*cmp)(T, T)) { //O(n^2)
        auto * newSeq = seq->Clone();
        for (int i = 0; i < newSeq->GetSize(); i++) {
            for (int j = 0; j < newSeq->GetSize() - i - 1; j++) {
                if (cmp((newSeq->Get(j)), (newSeq->Get(j + 1)))) {
                    Swapper(newSeq, j, j + 1);
                }
            }
        }
        return newSeq;
    }

    static Sequence<T>* BubbleShakerSortClone(Sequence<T> *seq, int(*cmp)(T, T)) { ////O(n^2)
        auto * newSeq = seq->Clone();
        int LeftSize = 1;
        int RightSize = newSeq->GetSize() - 1;
        while (LeftSize <= RightSize) {
            for (int i = LeftSize; i <= RightSize; i++) {
                if (cmp(newSeq->Get(i - 1), newSeq->Get(i))) {
                    Swapper(newSeq, i, i - 1);
                }
            }
            RightSize--;
            for (int i = RightSize; i >= LeftSize; i--) {
                if (cmp(newSeq->Get(i - 1), newSeq->Get(i))) {
                    Swapper(newSeq, i, i - 1);
                }
            }
            LeftSize++;
        }
        return newSeq;
    }

    static void BubbleShakerSort(Sequence<T> *seq, int(*cmp)(T, T)) { ////O(n^2)
        int LeftSize = 1;
        int RightSize = seq->GetSize() - 1;
        while (LeftSize <= RightSize) {
            for (int i = LeftSize; i <= RightSize; i++) {
                if (cmp(seq->Get(i - 1), seq->Get(i))) {
                    Swapper(seq, i, i - 1);
                }
            }
            RightSize--;
            for (int i = RightSize; i >= LeftSize; i--) {
                if (cmp(seq->Get(i - 1), seq->Get(i))) {
                    Swapper(seq, i, i - 1);
                }
            }
            LeftSize++;
        }
    }

    static Sequence<T>* InsertionSortClone(Sequence<T> *seq, int (*cmp)(T, T)) { //O(n^2)
        auto *newSeq = seq->Clone();
        for (int i = 1; i < newSeq->GetSize(); i++) {
            for (int j = i; j > 0 && cmp(newSeq->Get(j - 1), newSeq->Get(j)); j--) {
                Swapper(newSeq, j, j - 1);
            }
        }
        return newSeq;
    }

    static void InsertionSort(Sequence<T> *seq, int (*cmp)(T, T)) { //O(n^2)
        for (int i = 1; i < seq->GetSize(); i++) {
            for (int j = i; j > 0 && cmp(seq->Get(j - 1), seq->Get(j)); j--) {
                Swapper(seq, j, j - 1);
            }
        }
    }

    static Sequence<T>* SelectionSortClone(Sequence<T> *seq, int (*cmp)(T, T)) { //O(n^2)
        auto *newSeq = seq->Clone();
        T temp;
        for (int i = 0; i < newSeq->GetSize() - 1; i++) {
            int i_smallest = i;
            for (int j = i + 1; j < newSeq->GetSize(); j++) {
                if (cmp(newSeq->Get(i_smallest), newSeq->Get(j)))
                    i_smallest = j;
            }
            Swapper(newSeq, i, i_smallest);
        }
        return newSeq;
    }

    static void SelectionSort(Sequence<T> *seq, int (*cmp)(T, T)) { //O(n^2)
        T temp;
        for (int i = 0; i < seq->GetSize() - 1; i++) {
            int i_smallest = i;
            for (int j = i + 1; j < seq->GetSize(); j++) {
                if (cmp(seq->Get(i_smallest), seq->Get(j)))
                    i_smallest = j;
            }
            Swapper(seq, i, i_smallest);
        }
    }

    static Sequence<T>* QuickSortClone(Sequence<T>* seq, int first, int last, int (*cmp)(T, T)) { // O(nlogn)
        auto *newSeq = seq->Clone();
        QuickSort(newSeq, first, last, cmp);
        return newSeq;
    }

    static void QuickSort(Sequence<T>* seq, int first, int last, int (*cmp)(T, T)) { // O(nlogn)
        if (seq->GetSize() == 0){
            return;
        }
        T mid;
        int i = first;
        int j = last;
        mid = seq->Get((i+j)/2);
        do {
            while(cmp(mid, seq->Get(i))) {
                i++;
            }
            while(cmp(seq->Get(j), mid)) {
                j--;
            }
            if (i <= j) {
                Swapper(seq, i, j);
                i++;
                j--;
            }
        } while (i < j);

        if(first < j) {
            QuickSort(seq, first, j, cmp);
        }
        if (i < last) {
            QuickSort(seq, i, last, cmp);
        }
    }
};



const int SIZE = (1 << 17);
int a[100100]; // исходный массив
int tree[2 * SIZE];
int n; // кол-во элементов в исходном массиве

void build_sum_tree(int v, int L, int R)
{
    if (L == R - 1) // Условие выхода
    {
        if (L < n) // Поскольку мы объявляем большую размерность, необходимо следить за границей
        {
            tree[v] = a[L];
        }
        return; // Присвоили, возвращаемся
    }
    int M = (L + R) / 2; // Выбираем середину отрезка [L..R]
    build_sum_tree(2 * v + 1, L, M); // Запускаем сумму для левого потомка
    build_sum_tree(2 * v + 2, M, R); // И для правого
    tree[v] = tree[2 * v + 1] + tree[2 * v + 2]; // Обновляем текущую вершину
}
// Usage:
// build_sum_tree(0, 0, SIZE); Строим дерево от нулевой вершины с границей от 0 до SIZE (можно n)
int t[];
void build (int a[], int v, int tl, int tr) {
    if (tl == tr)
        t[v] = a[tl];
    else {
        int tm = (tl + tr) / 2;
        build (a, v*2, tl, tm);
        build (a, v*2+1, tm+1, tr);
        t[v] = t[v*2] + t[v*2+1];
    }
}

#endif //INTERFACE_CPP_SORTS_H
