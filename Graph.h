#ifndef LAB3SEM3_GRAPH_H
#define LAB3SEM3_GRAPH_H
#pragma once

#include "Sequence.h"
#include "LinkedListSequence.h"
#include "DynamicArray.h"
#include <string>
#include "LinkedList.h"

#define INDEX_OUT_OF_RANGE_MESSAGE "index out of range"


template <typename T>
class Graph {
private:
    class Edge {
    private:
        T weight;
        int vertex;
    public:
        Edge() {
            this->weight = 0;
            this->vertex = -1;
        }
        Edge(const Edge& edge){
            this->weight = edge.weight;
            this->vertex = edge.vertex;
        }
        Edge(int ver, T weight) {
            this->weight = weight;
            this->vertex = ver;
        }
        void changeWeight(T weight_) {
            this->weight = weight_;
        }
        T getWeight() {
            return this->weight;
        }
        int getVertex() {
            return this->vertex;
        }
        bool operator==(Edge& other) {
            return (this->weight == other.weight) && (this->vertex == other.vertex);
        }
        bool operator!=(Edge& other) {
            return (this->weight != other.weight) || (this->vertex != other.vertex);
        }

        ~Edge() = default;
    };

    class Vertex {
    private:
        LinkedList<Edge*>* edges = new LinkedList<Edge*>();
    public:
        Vertex() {
            LinkedList<Edge*>* edges = new LinkedList<Edge*>();
        }

        Vertex(LinkedList<Edge*>& edges) {
            this->edges = new LinkedList<Edge*>(edges);
        }

        int getEdgesCount() {
            return this->edges->GetSize();
        }

        void addEdge(int ver, T weight) {
            Edge* ed = new Edge(ver, weight);
            this->edges->Append(ed);
        }

        Edge* getEdge(int ver) {
            for (int i = 0; i < this->getEdgesCount(); i++) {
                if (this->edges->Get(i)->getVertex() == ver) {
                    return this->edges->Get(i);
                }
            }
            Edge* ed = new Edge(ver, 0);
            return ed;
        }

        T getWeight(int ver2) {
            for (int i = 0; i < this->getEdgesCount(); i++) {
                if (ver2 == this->edges->Get(i)->getVertex()) {
                    return this->edges->Get(i)->getWeight();
                }
            }
            return 0;
        }
        void changeWeight(int ver, T weight = 0) {
            for (int i = 0; i < this->getEdgesCount(); i++) {
                if (ver == this->edges->Get(i)->getVertex()) {
                    this->edges->Get(i)->changeWeight(weight);
                }
            }
        }
        bool findEdge(int ver2) {
            for (int i = 0; i < this->getEdgesCount(); i++) {
                if (ver2 == this->getEdge(i)->getVertex())
                    return true;
            }
            return false;
        }
        bool operator==(Vertex& other) {
            return (this->edges == other.edges);
        }
        bool operator!=(Vertex& other) {
            return (this->edges != other.edges);
        }
    };

    void TopologicalSortHelper(int ver, bool *visited, ArraySequence<int> *seq){
        visited[ver] = true;
        for(int i = 0; i < this->getSize(); i++)
            if(this->existOfEdge(ver, i))
                if(!visited[i])
                    this->TopologicalSortHelper(i, visited, seq);
        seq->Prepend(ver);
    }
    LinkedList<Vertex*>* vertices = new LinkedList<Vertex*>();
    bool directed = true;
    int size = 0;

public:

    Graph(int size, bool direct) {
        Vertex* ver;
        vertices = new LinkedList<Vertex*>();
        for (int i = 0; i < size; i++) {
            ver = new Vertex();
            vertices->Append(ver);
        }
        this->directed = direct;
        this->size = size;
    }

    int getSize() {
        return this->vertices->GetSize();
    }

    bool isDirected() {
        return this->directed;
    }

    void addVertex() {
        Vertex* ver = new Vertex();
        this->vertices->Append(ver);
        this->size++;
    }

    Vertex* getVertex(int i) {
        if (i >= this->getSize())
            throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);
        return this->vertices->Get(i);
    }

    bool existOfVertex (int i){
        if (i >= this->getSize())
            return false;
        else
            return true;
    }
    bool existOfEdge (int ver1, int ver2) {
        for (int i = 0; i < this->getSize(); i++) {
            if (this->getWeightOfEdge(ver1,ver2) != 0)
                return true;
        }
        return false;
    }

    T getWeightOfEdge(int ver1, int ver2) {
        return this->getVertex(ver1)->getWeight(ver2);
    }

    void changeEdge(int ver1, int ver2, T weight) {
        if ((ver1 < 0) || (ver1 >= this->size))
            throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);
        if ((ver2 < 0) || (ver2 >= this->size))
            throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);
        if (this->existOfEdge(ver1, ver2) == false) {
            this->getVertex(ver1)->addEdge(ver2, weight);
            if (!this->directed) { //если неориентированы то создаем ребро и в обратную сторону
                this->getVertex(ver2)->addEdge(ver1, weight);
            }
        }
        else {
            this->getVertex(ver1)->changeWeight(ver2, weight);
            if (!this->directed) {
                this->getVertex(ver2)->changeWeight(ver1, weight);
            }
        }
    }

    pair<int,Sequence<int>*> Dijkstra(int ver1, int ver2) {
        if ((ver1 < 0) || (ver1 >= this->size))
            throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);
        if ((ver2 < 0) || (ver2 >= this->size))
            throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);
        Sequence<T>* Distance = new ListSequence<T>(this->getSize());
        Sequence<bool>* visited = new ListSequence<bool>(this->getSize());
        Sequence<int>* PredVertex = new ListSequence<int>(this->getSize()); //родитель
        Sequence<int>* Path = new ListSequence<int>();

        for (int i = 0; i < this->getSize(); i++) {
            Distance->Set(INT_MAX, i); //веса вершин
            visited->Set(false, i);
            PredVertex->Set(-1, i);
        }
        PredVertex->Set(ver1, ver1);
        Distance->Set(0, ver1);
        int index = 0;
        int minWeight = INT_MAX;

        while (true) {
            index = -1;
            minWeight = INT_MAX;
            for (int i = 0; i < this->getSize(); i++) {
                // Если вершину ещё не обошли и вес меньше min переприсваиваем значения
                if (visited->Get(i) == 0 && Distance->Get(i) < minWeight) {
                    minWeight = Distance->Get(i);
                    index = i;
                }
            }
            if (index == -1) break;
            visited->Set(true, index); //отмечаем вершину как посещенную
            // Добавляем найденный минимальный вес к текущему весу вершины
            // и сравниваем с текущим минимальным весом вершины
            if (index != INT_MAX) {
                for (int i = 0; i < this->getSize(); i++) {
                    if (this->getVertex(index)->getWeight(i) > 0)
                        if (minWeight + this->getVertex(index)->getWeight(i) < Distance->Get(i)) {
                            Distance->Set(minWeight + this->getVertex(index)->getWeight(i), i);
                            // если эта вершина не пройденная и она смежна с выбранной и если сумма веса выбранной вершины и ребра к текущей будет меньше, чем
                            // вес текущей на данный момент, то  - меняем значение веса текущей вершины.
                            PredVertex->Set(index, i);
                        }
                }
            }
        }
        if (Distance->Get(ver2) == INT_MAX) {//нет пути
            Path->Append(INT_MAX);
            return { INT_MAX,Path };
        }
        //создаем массив вершин, по которым прошлись
        int ver = ver2;
        Path->Prepend(ver2);
        while (ver != ver1) {
            Path->Prepend(PredVertex->Get(ver));
            ver = PredVertex->Get(ver);
        }

        return { Distance->Get(ver2),Path };
    }

    ArraySequence<int>* TopologicalSort(){
        if(!this->directed) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);
        ArraySequence<int> *seq;
        seq = new ArraySequence<int>();
        bool *visited = new bool[this->getSize()];
        for (int i = 0; i < this->getSize(); i++)
            visited[i] = false;
        for (int i = 0; i < this->getSize(); i++)
            if (!visited[i])
                this->TopologicalSortHelper(i, visited, seq);
        return seq;
    }
    template<class TKey, class TElement>
    ArraySequence<int>* UndirGraphColoring(){
        int k = 1;
        //Sequence<int>* V = new ArraySequence<int>(); //множество вершин
        D
        Sequence<int>* S = new ArraySequence<int>(); //множество вершин окрашенных в цвет к
        for (int i = 0; i < this->getSize(); i++){
            if (existOfVertex(i))
                continue;
            S->Append(i);//добавляем цвет
            this->getVertex(i) = this->getVertex(i) // исключаем итую вершину

    }


};
#endif //LAB3SEM3_GRAPH_H
