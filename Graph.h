#ifndef LAB3SEM3_GRAPH_H
#define LAB3SEM3_GRAPH_H
#pragma once

#include "Sequence.h"
#include "LinkedListSequence.h"
#include "DynamicArray.h"
#include <string>
#include "LinkedList.h"

using namespace std;

#define INDEX_OUT_OF_RANGE_MESSAGE "index out of range"


template <typename T>
class Graph {
private:
    class Edge {
    private:
        T weight;
        int ver;
    public:

        Edge() {
            this->weight = 0;
            this->ver = -1;
        }
        Edge(int ver, T weight) {
            this->weight = weight;
            this->ver = ver;
        }

        void changeWeight(T weight) {
            this->weight = weight;
        }

        T getWeight() {
            return this->weight;
        }
        int getVertex() {
            return this->ver;
        }
        bool operator==(Edge& other) {
            return (this->weight == other.weight) && (this->ver == other.ver);
        }
        bool operator!=(Edge& other) {
            return (this->weight != other.weight) || (this->ver != other.ver);
        }

        ~Edge() = default;
    };
    class Vertex {
    private:
        LinkedList<Edge*>* edges = new LinkedList<Edge*>(); //окрестность
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
            return 0;
        }

        /*void removeEdge(int ver2) {
            if (!this->existOfEdge(ver2)) return;
            else {
                for (int i = 0; i < this->getEdgesCount(); i++) {
                    if (ver2 == this->getEdge(i).getVertex())
                        this->edges->Remove(i);
                }
            }
        }*/


        bool operator==(Vertex& other) {
            return (this->edges == other.edges);
        }
        bool operator!=(Vertex& other) {
            return (this->edges != other.edges);
        }

        /*void print() {
            cout << "kolvo" << this->getEdgesCount() << endl;
            for (int i = 0; i < this->getEdgesCount(); i++)
                cout << i << "." << this->edges->Get(i)->getVertex() << ", " <<this->edges->Get(i)->getWeight() << "*"<< endl;
            cout << "ENDprintver" << endl;
        }*/

    };

    LinkedList<Vertex*>* vertices = new LinkedList<Vertex*>();
    bool directed = true;
    int size = 0;

public:

    Graph(int size,  bool direct) {
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

    /*void print() {
        cout << "PRINT" << endl;
        for (int i = 0; i < this->getSize(); i++) {
            //for (int j = 0; j < this->getSize(); j++)
            this->vertices->Get(i)->print();
        }
        cout << "END";
    }
    void print2() {
        cout << "qPRINTq" << endl;
        for (int i = 0; i < this->getSize(); i++) {
            for (int j = 0; j < this->getSize(); j++)
            cout << this->vertices->Get(i)->getWeight(j);

        }
        cout << "qENDq";
    }*/


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
            if (!this->directed) { //если неориентированны то создаем ребро и в обратную сторону
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



    /*void removeEdge(int ver1, int ver2) {
        this->getVertex(ver1)->RemoveEdge(ver2);
        if (!this->directed) {
            this->getVertex(ver2)->RemoveEdge(ver1);
        }
    }*/

    pair<int,Sequence<int>*> Dijkstra(int ver1, int ver2) {
        if (ver1 < 0 || ver1 >= this->getSize() || ver2 < 0 || ver2 >= this->getSize())
            throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);

        Sequence<T>* Distance = new ListSequence<T>(this->getSize());
        Sequence<bool>* visited = new ListSequence<bool>(this->getSize());
        Sequence<int>* PredVertex = new ListSequence<int>(this->getSize());
        Sequence<int>* Path = new ListSequence<int>();

        for (int i = 0; i < this->getSize(); i++) {
            Distance->Set(INT_MAX, i);
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
                for (int i = 0; i < this->getSize(); i++)
                    if (this->getVertex(index)->getWeight(i) > 0)
                        if (minWeight + this->getVertex(index)->getWeight(i)  < Distance->Get(i))
                            Distance->Set(minWeight + this->getVertex(index)->getWeight(i), i);
                visited->Set(true, index);
            }
        }
        //Distance->Set(minWeight + this->getVertex(index)->getWeight(i), i);
        //PredVertex->Set(index, i);

        // Восстановление пути
        int ver[SIZE]; // массив посещенных вершин
        int end = 4; // индекс конечной вершины = 5 - 1
        ver[0] = end + 1; // начальный элемент - конечная вершина
        int k = 1; // индекс предыдущей вершины
        int weight = minDist[end]; // вес конечной вершины

        while (end != beginIndex) // пока не дошли до начальной вершины
        {
            for (int i = 0; i<SIZE; i++) // просматриваем все вершины
                if (matrix[i][end] != 0)   // если связь есть
                {
                    int temp = weight - matrix[i][end]; // определяем вес пути из предыдущей вершины
                    if (temp == minDist[i]) // если вес совпал с рассчитанным
                    {                 // значит из этой вершины и был переход
                        weight = temp; // сохраняем новый вес
                        end = i;       // сохраняем предыдущую вершину
                        ver[k] = i + 1; // и записываем ее в массив
                        k++;
                    }
                }
        }
            for (i = 0; i < this->getSize(); i++) {
                if (this->existOfEdge(index, i)) {
                    if (Distance->Get(index) + this->getVertex(index)->getWeight(i) < Distance->Get(i)) {
                        Distance->Set(Distance->Get(index) + this->getVertex(index)->getWeight(i), i);
                        PredVertex->Set(index, i);
                    }
                }
            }
        }
        /*for (int i = 0; i < this->getSize(); i++) {
            cout<<i <<". " << Distance->Get(i)<< endl;
        }
        for (int i = 0; i < this->getSize(); i++) {
            cout << i << ". " << visited->Get(i) << endl;
        }
        for (int i = 0; i < this->getSize(); i++) {
            cout << i << ". " << PredVertex->Get(i) << endl;
        }*/

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




};
#endif //LAB3SEM3_GRAPH_H
