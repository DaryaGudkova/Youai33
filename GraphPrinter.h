#ifndef LAB3SEM3_GRAPHPRINTER_H
#define LAB3SEM3_GRAPHPRINTER_H
#include <iostream>
#include "tests.h"
#pragma once



void PrintPath(Sequence<int>* path) {
    int i = 0;
    if (path->GetSize() == 1)
    {
        if (path->Get(0) == INT_MAX)
            cout << "Vertexes aren't connected" << endl;
    }
    else {
        for (i = 0; i < path->GetSize() - 1; i++)
            cout << path->Get(i) << ", ";
        cout << path->Get(i) << endl;
    }

};

template <typename T>
void PrintDijkstra(Graph<T>* graph, int ver1, int ver2) {
    cout << "Shortest path from " << ver1 << " to " << ver2 << endl;
    pair< int, Sequence<int>*> weight_Path = graph->Dijkstra(ver1, ver2);

    PrintPath(weight_Path.second);
    if (weight_Path.first != INT_MAX)
        cout << "Weight of the path: " << weight_Path.first << endl;
};

template <typename T>
void AdjacencyMatrix(Graph<T>* graph) {
    for (int i = 0; i < graph->getSize(); i++) {
        for (int j = 0; j < graph->getSize(); j++) {
            cout << graph->getWeightOfEdge(i, j) << "   ";
        }
        cout << endl;
    }
};
#endif //LAB3SEM3_GRAPHPRINTER_H
