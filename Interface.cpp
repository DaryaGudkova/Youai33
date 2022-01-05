#include <iostream>
#include "tests.h"
#include "GraphPrinter.h"

using namespace std;
template <typename T>
void PrintSequence(LinkedList<T*>* seq) {
    for (int i=0; i<seq->GetSize(); i++) {
        cout << seq->Get(i);
        cout << " ";
    }
    cout<<endl;
}
Graph<int>* DirectedGraph()
{
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
    return gr;
}
Graph<int>* UndirectedGraph()
{
    Graph<int>* gr = new Graph<int>(10, false);
    gr->changeEdge(0, 7, 1);
    gr->changeEdge(6, 1, 90);
    gr->changeEdge(6, 3, 13);
    gr->changeEdge(6, 7, 2);
    gr->changeEdge(3, 6, 3);
    gr->changeEdge(1, 2, 9);
    gr->changeEdge(2, 3, 20);
    gr->changeEdge(4, 5, 10);

    return gr;
}

//void PrintMenu();

template <typename T>
void GraphConstructor(Graph<T>* graph) {
    int choose = 0;
    int ver1 = 0;
    int ver2 = 0;
    T weight = T(1);
    while (true)
    {
        cout << "0 - Exit" << endl;
        cout << "1 - Change an edge" << endl;
        cout << "2 - Print adjacency matrix" << endl;
        cout << "3 - Find shortest path from ver1 to ver2" << endl;
        cout << "4 - Topological sort" << endl;
        cin >> choose;
        switch (choose)
        {
            case 1:
                cout << endl;
                cout << "Enter the first vertex: ";
                cin >> ver1;
                cout << "Enter the second vertex: ";
                cin >> ver2;
                cout << "Enter a weight of the edge: ";
                cin >> weight;
                cout << endl;
                graph->changeEdge(ver1, ver2, weight);
                break;
            case 2:
                cout << endl;
                PrintAdjacencyMatrix(graph);
                cout << endl;
                break;
            case 3:
                cout << endl;
                cout << "Enter the first vertex: ";
                cin >> ver1;
                cout << "Enter the second vertex: ";
                cin >> ver2;
                cout << endl;
                PrintDijkstra(graph, ver1, ver2);
                cout << endl;
                break;
            case 4:
                cout << "Your topological sort: " << endl;
                for (int i = 0; i < graph->TopologicalSort()->GetSize(); i++)
                    cout << graph->TopologicalSort()->Get(i) << " ";
                cout << endl;
                break;
            case 5:
                graph->GraphColoring()->print();
                //graph->BubbleSort();
                //PrintAdjacencyMatrix(graph->GraphColoring());
                //cout<<"degree: ";
                //PrintSequence(graph->UndirGraphColoring());
                //cout<<"degree: ";
                //cout << graph->getDegreeOfVertex(0);
            default:
                return;
        }
    }
}


void InterfaceGraph(){
    int choose = 0;
    int number = 0;
    int i = 0;
    int j = 0;
    int vert1 = 0;
    int vert2 = 0;
    int weight = 0;
    Graph<int>* gr;
    cout << "0 - Exit" << endl;
    cout << "1 - Use example of directed graph" << endl;
    cout << "2 - Use example of undirected graph" << endl;
    cout << "3 - Create a graph yourself" << endl;
    cin >> choose;
    cout << endl;
    switch (choose){
        case 1:
            gr = DirectedGraph();
            GraphConstructor(gr);
            break;
        case 2:
            gr = UndirectedGraph();
            GraphConstructor(gr);
            break;
        case 3:
            cout << "Enter an amount of vertexes" << endl;
            cin >> number;
            cout << "Select the type of graph:" << endl;
            cout << "0 - Undirected graph" << endl;
            cout << "1 - Directed graph" << endl;
            cin >> choose;
            switch (choose){
                case 0:
                    gr = new Graph<int>(number, false);
                    GraphConstructor(gr);
                    break;
                case 1:
                    gr = new Graph<int>(number, true);
                    GraphConstructor(gr);
                    break;
                default:
                    return;
            }
    }
}

int main() {
    alltests();
    InterfaceGraph();
    return 0;
}
//написать для случая когда хотим заполнить несуществующую вершину
