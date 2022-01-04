#ifndef LAB3SEM3_GRAPH_H
#define LAB3SEM3_GRAPH_H
#pragma once

#include "Sequence.h"
#include "LinkedListSequence.h"
#include "DynamicArray.h"
#include <string>
#include "LinkedList.h"
#include "Dictionary.h"
#include "Matrix.h"
#include "Sorts.h"

#define INDEX_OUT_OF_RANGE_MESSAGE "index out of range"


template <typename T>
class Graph {
private:
    class Edge {
    private:
        T weight;
        int vertex1;
        int vertex2;
    public:
        Edge() {
            this->weight = 0;
            this->vertex1 = -1;
            this->vertex2 = -1;
        }
        Edge(const Edge& edge){
            this->weight = edge.weight;
            this->vertex1 = edge.vertex1;
            this->vertex2 = edge.vertex2;
        }
        Edge(int ver1, int ver2, T weight) {
            this->weight = weight;
            this->vertex1 = ver1;
            this->vertex2 = ver2;
        }
        void changeWeight(T weight_) {
            this->weight = weight_;
        }
        T getWeight() {
            return this->weight;
        }
        int getVertex1() {
            return this->vertex1;
        }
        int getVertex2(){
            return this->vertex2;
        }
        bool operator==(Edge& other) {
            return (this->weight == other.weight) && (this->vertex1 == other.vertex1) && (this->vertex2 == other.vertex2);
        }
        bool operator!=(Edge& other) {
            return (this->weight != other.weight) || (this->vertex1 != other.vertex1) || (this->vertex2 != other.vertex2);
        }
        Edge& operator=(const Edge &edge)
        {
            // Выполняем копирование значений
            this->weight = edge.weight;
            this->vertex1 = edge.vertex1;
            this->vertex2 = edge.vertex2;
            // Возвращаем текущий объект, чтобы иметь возможность связать в цепочку выполнение нескольких операций присваивания
            return *this;
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

       /* Vertex(const Vertex& v) {
            this->edges = new LinkedList<Edge *>(v->edges);
        }*/

        Vertex(LinkedList<Edge*>& edges) {
            this->edges = new LinkedList<Edge*>(edges);
        }

        int getEdgesCount(){
            return this->edges->GetSize();
        }

        void addEdge(int ver1, T weight) {
            Edge* ed = new Edge(ver1, -1, weight);
            this->edges->Append(ed);
        }

        Edge* getEdge(int ver1, int ver2) {
            for (int i = 0; i < this->getEdgesCount(); i++) {
                if (this->edges->Get(i)->getVertex1() == ver1 && this->edges->Get(i)->getVertex2() == ver2) {
                    return this->edges->Get(i);
                }
            }
            Edge* ed = new Edge(ver1, ver2, 0);
            return ed;
        }

        T getWeight(int ver1) {
            for (int i = 0; i < this->getEdgesCount(); i++) {
                if (ver1 == this->edges->Get(i)->getVertex1()) {
                    return this->edges->Get(i)->getWeight();
                }
            }
            return 0;
        }
        void changeWeight(int ver1, T weight) {
            for (int i = 0; i < this->getEdgesCount(); i++) {
                if (ver1 == this->edges->Get(i)->getVertex1()) {
                    this->edges->Get(i)->changeWeight(weight);
                }
            }
        }
        bool findEdge(int ver1, int ver2) {
            for (int i = 0; i < this->getEdgesCount(); i++) {
                if (ver1 == this->getEdge(i)->getVertex1() && ver2 == this->getEdge(i)->getVertex2())
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
        Vertex& operator=(const Vertex &v)
        {
            // Выполняем копирование значений
            this->edges = v.edges;
            // Возвращаем текущий объект, чтобы иметь возможность связать в цепочку выполнение нескольких операций присваивания
            return *this;
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

    Graph& operator=(const Graph<T> &graph)
    {
        // Выполняем копирование значений
        this->vertices = new LinkedList<Vertex*>(graph.vertices);
        this->directed = graph.directed;
        this->size = graph.size;
        // Возвращаем текущий объект, чтобы иметь возможность связать в цепочку выполнение нескольких операций присваивания
        return *this;
    }
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
    Graph(Graph& graph){
        this->vertices = graph.vertices;
        this->size = graph.size;
        this->directed = graph.directed;
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
    bool existOfVertex (Vertex* vertex){
        bool t = false;
        for(int i = 0; i < this->getSize(); i++){
            if(vertex == this->getVertex(i)){
                t = true;
            }
        }
        return t;
    }
    bool existOfEdge (int ver1, int ver2) {
        for (int i = 0; i < this->getSize(); i++) {
            if (this->getWeightOfEdge(ver1,ver2) != 0)
                return true;
        }
        return false;
    }
    T getDegreeOfVertex(int ver1){ //число ребер графа, которым принадлежит эта вершина
        int counter = 0;
        for(int i = 0; i < this->getSize(); i++){
            if(this->existOfEdge(ver1, i)/*this->getEdge(ver1,i) != 0*/)
                counter++;
        }
        return counter;
    }
    T getWeightOfEdge(int ver1, int ver2) {
        return this->getVertex(ver1)->getWeight(ver2);
    }

    void SetVertex(const Vertex& value, int index) {
        if (index < 0 || index > this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);
        *this->vertices->Get(index) = value;
    }
    void SwapVertex(Vertex& i, Vertex& j){
        Vertex tmp = i;
        i = j;
        j = tmp;
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
    Matrix<int>* AdjacencyMatrix(){
        auto* matrix = new Matrix<int>();
        for (int i = 0; i < this->getSize(); i++) {
            for (int j = 0; j < this->getSize(); j++) {
                matrix->Set(this->getWeightOfEdge(i, j), i, j);
            }
        }
        return matrix;
    }

    void PrintAdjacencyMatrix(Graph<T>* graph) {
        for (int i = 0; i < graph->getSize(); i++) {
            for (int j = 0; j < graph->getSize(); j++) {
                cout << graph->getWeightOfEdge(i, j) << "   ";
            }
            cout << endl;
        }
    }
    Graph<T>* BubbleSort() { //O(n^2)
        Graph<T>* graph = this;
        for (int i = 0; i < graph->getSize(); i++) {
            for (int j = 0; j < graph->getSize() - i - 1; j++) {
                if (graph->getDegreeOfVertex(i-1) > graph->getDegreeOfVertex(i)) {
                    graph->SwapVertex(*graph->getVertex(i-1), *graph->getVertex(i));
                }
            }
        }
        return graph;
    }

    //template< class TKey, class TElement>
    Dictionary<int, int>* UndirGraphColoring(){
        auto* orderedGraph = new Graph<T>(*this);
        //упорядочиваем вершины по убыванию степени
        for (int i = 0; i < orderedGraph->getSize(); i++) {
            for (int j = 0; j < orderedGraph->getSize() - i - 1; j++) {
                if (orderedGraph->getDegreeOfVertex(j) < orderedGraph->getDegreeOfVertex(j + 1)) {
                    orderedGraph->SwapVertex(*orderedGraph->getVertex(j), *orderedGraph->getVertex(j + 1));
                }
            }
        }
        PrintAdjacencyMatrix(orderedGraph);
        auto* coloredGraph = new Dictionary<int, int>(); //вершина-цвет
        for(int i = 0; i < orderedGraph->getSize(); i++){
            coloredGraph->add(i, 0);
        }
        coloredGraph->print();
        int k = 1;
        coloredGraph->changeElem(0, k);
        //int i = 0;
        //while(coloredGraph->containsElem(0)){
        for(int i = 0; i<orderedGraph->getSize(); i++){
            for(int j = 0; j < orderedGraph->getSize(); j++){
                cout<<"_";
                cout<<orderedGraph->getWeightOfEdge(i,j);
                if(orderedGraph->getWeightOfEdge(i,j)==0 && coloredGraph->get(j) == 0 && coloredGraph->get(i) == k /*!orderedGraph->existOfEdge(i,j) && coloredGraph->getKeyByElem(i)==coloredGraph->getKeyByElem(i)*/){
                    coloredGraph->changeElem(j, k);
                }
            }
            //i++;
            k++;
        }
        //Matrix<T> adjMatrix = this->AdjacencyMatrix();
        //Graph<T>* orderedGraph = this->BubbleSort();
        //orderedGraph->BubbleSort();
        //LinkedList<Vertex*>* orderedVertices = vertices;
        /*for(int i = 1; i < this->getSize(); i++){
            if(orderedGraph->getDegreeOfVertex(i-1) > orderedGraph->getDegreeOfVertex(i)){
                orderedGraph->SwapVertex(*orderedGraph->getVertex(i-1), *orderedGraph->getVertex(i));
                //orderedGraph->swapVertex(*orderedGraph->getVertex(i-1), *orderedGraph->getVertex(i));
                Vertex* temp = orderedGraph->getVertex(i-1);
                *orderedGraph->getVertex(i-1) = *orderedGraph->getVertex(i);
                orderedGraph->getVertex(i) = temp;
                cout<<"----"<<endl;
                PrintAdjacencyMatrix(orderedGraph);
                cout<<endl;
                Vertex* temp = orderedVertices->Get(i-1);
                *orderedVertices->Get(i-1) = *orderedVertices->Get(i);
                *orderedVertices->Get(i) = *temp;
                //orderedVertices->Swapper(orderedVertices->Get(i-1), orderedVertices->Get(i));
            }
        }*/
        return coloredGraph;
/*
        //Sequence<int>* V = new ArraySequence<int>(); //множество вершин
        auto* ColoredInK = new Dictionary<int, int>();//множество вершин окрашенных в цвет к
        for (int i = 0; i < this->getSize(); i++){
            if (existOfVertex(i))
                continue;
            ColoredInK->changeElem(k,i); //красим в цвет k вершину i
            S->Append(i);//добавляем цвет
            this->getVertex(i) = this->getVertex(i) // исключаем итую вершину
*/
    }


};
#endif //LAB3SEM3_GRAPH_H
