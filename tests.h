#ifndef LAB3SEM3_TESTS_H
#define LAB3SEM3_TESTS_H
#pragma once
#include <cstdlib>
#include "ArraySequence.h"
#include "DynamicArray.h"
#include "LinkedList.h"
#include "LinkedListSequence.h"
#include "Graph.h"
#include <string>
#include <iostream>
#include <cassert>

void testGraph() {
    Graph<int>* gr = new Graph<int>(7, true);
    gr->changeEdge(0, 1, 13);
    gr->changeEdge(0, 2, 3);
    gr->changeEdge(0, 6, 2);
    gr->changeEdge(2, 3, 4);
    gr->changeEdge(2, 4, 3);
    gr->changeEdge(3, 1, 5);
    gr->changeEdge(4, 1, 7);
    gr->changeEdge(5, 4, 10);
    gr->changeEdge(6, 0, 1);

    assert(gr->getSize() == 7);
    assert(gr->isDirected() == true);
    assert(gr->existOfEdge(0, 1) == true);
    assert(gr->existOfEdge(0, 2) == true);
    assert(gr->existOfEdge(2, 0) == false);
    assert(gr->existOfEdge(1, 0) == false);

    assert(gr->getWeightOfEdge(6, 0) != 10);
    assert(gr->getWeightOfEdge(0, 1) == 13);

    gr->changeEdge(5, 4, 8);
    assert(gr->getWeightOfEdge(5, 4) == 8);

    assert(gr->Dijkstra(0, 1).first == 12);
    assert(gr->Dijkstra(2, 4).first == 3);
    assert(gr->Dijkstra(3, 6).first == INT_MAX);

}
void testDynamicArray() {
    int initArr1[] = { 1,2,3,4,5 };
    int initArr2[] = { 0,2,3,4,5,6 };
    int initArr3[] = { 0,2,3,4 };

    DynamicArray<int> arr1(initArr1, 5);

    assert(arr1 == DynamicArray<int>(arr1));
    assert(arr1 == DynamicArray<int>(arr1, 5));
    assert(DynamicArray<int>() == DynamicArray<int>((int*)0, 0));
    assert(arr1.Get(0) == 1);
    assert(arr1.Get(3) == 4);
    assert(arr1.Get(4) == 5);
    assert(arr1.GetSize() == 5);

    arr1.Resize(6);
    arr1.Set(0, 0);
    arr1.Set(6, 5);
    assert(arr1 == DynamicArray<int>(initArr2, 6));
    arr1.Resize(4);
    assert(arr1 == DynamicArray<int>(initArr3, 4));
}

void testLinkedList() {
    int initArr1[] = { 1,2,3,5 };
    int initArr2[] = { -1,0,1,2,3,4,5,6,7 };
    int initArr3[] = { -1 };
    int initArr35[] = { -2,0,1,2,3,4,5,0,8 };
    int initArr4[] = { 0,1,2,3,5,0 };
    int initArr5[] = { 0,1,2,3,5,0,-1 };
    int initArr6[] = { 0,1,2,3,5,0,1,2,3,5 };

    LinkedList<int> list1(initArr1, 4);

    assert(list1 == LinkedList<int>(list1));
    assert(LinkedList<int>() == LinkedList<int>((int*)0, 0));
    assert(list1.Get(0) == 1);
    assert(list1.GetFirst() == 1);
    assert(list1.Get(2) == 3);
    assert(list1.Get(3) == 5);
    assert(list1.GetLast() == 5);
    assert(list1.GetSize() == 4);

    list1.Prepend(0);
    list1.Append(6);
    list1.Insert(-1, 0);
    list1.Insert(7, 7);
    list1.Insert(4, 5);
    assert(list1 == LinkedList<int>(initArr2, 9));

    LinkedList<int>* list2 = list1.GetSublist(0, 0);
    LinkedList<int>* list3 = list1.GetSublist(0, 1);
    LinkedList<int>* list4 = list1.GetSublist(0, 9);
    assert(*list2 == LinkedList<int>());
    assert(*list3 == LinkedList<int>(initArr3, 1));
    assert(*list4 == list1);

    list1.Set(-2, 0);
    list1.Set(8, 8);
    list1.Set(0, 7);
    assert(list1 == LinkedList<int>(initArr35, 9));

    list1.Remove(0);
    list1.Remove(7);
    list1.Remove(4);
    assert(list1 == LinkedList<int>(initArr4, 6));

    LinkedList<int>* list5 = list1.Concat(LinkedList<int>());
    LinkedList<int>* list6 = list1.Concat(LinkedList<int>(initArr3, 1));
    LinkedList<int>* list7 = list1.Concat(LinkedList<int>(initArr1, 4));
    assert(*list5 == list1);
    assert(*list6 == LinkedList<int>(initArr5, 7));
    assert(*list7 == LinkedList<int>(initArr6, 10));

    delete list2;
    delete list3;
    delete list4;
    delete list5;
    delete list6;
    delete list7;
}

void testArraySequence() {
    int initArr1[] = { 1,2,3,5 };
    int initArr2[] = { -1,0,1,2,3,4,5,6,7 };
    int initArr3[] = { -1 };
    int initArr4[] = { -2,0,1,2,3,4,5,0,8 };
    int initArr5[] = { -2,0,1,2,3,4,5,0,8,-1 };
    int initArr6[] = { -2,0,1,2,3,4,5,0,8,1,2,3,5 };

    ArraySequence<int> seq1(initArr1, 4);

    assert(seq1 == ArraySequence<int>(seq1));
    assert(ArraySequence<int>() == ArraySequence<int>((int*)0, 0));
    assert(seq1.Get(0) == 1);
    assert(seq1.GetFirst() == 1);
    assert(seq1.Get(2) == 3);
    assert(seq1.Get(3) == 5);
    assert(seq1.GetLast() == 5);
    assert(seq1.GetSize() == 4);

    seq1.Prepend(0);
    seq1.Append(6);
    seq1.Insert(-1, 0);
    seq1.Insert(7, 7);
    seq1.Insert(4, 5);

    assert(seq1 == ArraySequence<int>(initArr2, 9));

    ArraySequence<int>* seq2 = seq1.GetSubsequence(0, 0);
    ArraySequence<int>* seq3 = seq1.GetSubsequence(0, 1);
    ArraySequence<int>* seq4 = seq1.GetSubsequence(0, 9);
    assert(*seq2 == ArraySequence<int>());
    assert(*seq3 == ArraySequence<int>(initArr3, 1));
    assert(*seq4 == seq1);

    seq1.Set(-2, 0);
    seq1.Set(8, 8);
    seq1.Set(0, 7);
    assert(seq1 == ArraySequence<int>(initArr4, 9));
    ArraySequence<int>* seq5 = seq1.Concat(ArraySequence<int>());
    ArraySequence<int>* seq6 = seq1.Concat(ArraySequence<int>(initArr3, 1));
    ArraySequence<int>* seq7 = seq1.Concat(ArraySequence<int>(initArr1, 4));
    assert(*seq5 == seq1);
    assert(*seq6 == ArraySequence<int>(initArr5, 10));
    assert(*seq7 == ArraySequence<int>(initArr6, 13));

    delete seq2;
    delete seq3;
    delete seq4;
    delete seq5;
    delete seq6;
    delete seq7;
}

void testListSequence() {
    int initArr1[] = { 1,2,3,5 };
    int initArr2[] = { -1,0,1,2,3,4,5,6,7 };
    int initArr3[] = { -1 };
    int initArr4[] = { -2,0,1,2,3,4,5,0,8 };
    int initArr5[] = { -2,0,1,2,3,4,5,0,8,-1 };
    int initArr6[] = { -2,0,1,2,3,4,5,0,8,1,2,3,5 };

    ListSequence<int> seq1(initArr1, 4);

    assert(seq1 == ListSequence<int>(seq1));
    assert(ListSequence<int>() == ListSequence<int>((int*)0, 0));
    assert(seq1.Get(0) == 1);
    assert(seq1.GetFirst() == 1);
    assert(seq1.Get(2) == 3);
    assert(seq1.Get(3) == 5);
    assert(seq1.GetLast() == 5);
    assert(seq1.GetSize() == 4);

    seq1.Prepend(0);
    seq1.Append(6);
    seq1.Insert(-1, 0);
    seq1.Insert(7, 7);
    seq1.Insert(4, 5);
    assert(seq1 == ListSequence<int>(initArr2, 9));

    ListSequence<int>* seq2 = seq1.GetSubsequence(0, 0);
    ListSequence<int>* seq3 = seq1.GetSubsequence(0, 1);
    ListSequence<int>* seq4 = seq1.GetSubsequence(0, 9);
    assert(*seq2 == ListSequence<int>());
    assert(*seq3 == ListSequence<int>(initArr3, 1));
    assert(*seq4 == seq1);

    seq1.Set(-2, 0);
    seq1.Set(8, 8);
    seq1.Set(0, 7);
    assert(seq1 == ListSequence<int>(initArr4, 9));

    ListSequence<int>* seq5 = seq1.Concat(ListSequence<int>());
    ListSequence<int>* seq6 = seq1.Concat(ListSequence<int>(initArr3, 1));
    ListSequence<int>* seq7 = seq1.Concat(ListSequence<int>(initArr1, 4));
    assert(*seq5 == seq1);
    assert(*seq6 == ListSequence<int>(initArr5, 10));
    assert(*seq7 == ListSequence<int>(initArr6, 13));

    delete seq2;
    delete seq3;
    delete seq4;
    delete seq5;
    delete seq6;
    delete seq7;
}

void alltests() {
    testDynamicArray();
    cerr << "class DynamicArray is successfully tested" << endl;
    testLinkedList();
    cerr << "class LinkedList is successfully tested" << endl;
    testArraySequence();
    cerr << "class ArraySequence is successfully tested" << endl;
    testListSequence();
    cerr << "class ListSequence is successfully tested" << endl;
    testGraph();
    cerr << "Graph is tested" << endl;
    cout << endl;
}
#endif //LAB3SEM3_TESTS_H
