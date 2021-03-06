#include <iostream>
#include "tests.h"
#include "GraphPrinter.h"

using namespace std;

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
    gr->changeEdge(8, 7, 1);
    gr->changeEdge(6, 1, 90);
    gr->changeEdge(6, 3, 13);
    gr->changeEdge(6, 7, 2);
    gr->changeEdge(3, 6, 3);
    gr->changeEdge(1, 2, 9);
    gr->changeEdge(2, 3, 20);
    gr->changeEdge(4, 5, 10);

    return gr;
}

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
        cout << "4 - Coloring" << endl;
        if(graph->isDirected())
            cout << "5 - Topological sort" << endl;
        cin >> choose;
        switch (choose)
        {
            case 0:
                InterfaceGraph();
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
                cout << "Coloring your graph: " << endl;
                graph->GraphColoring()->print();
                break;
            case 5:
                if(graph->isDirected()){
                    cout << "Your topological sort: " << endl;
                    for (int i = 0; i < graph->TopologicalSort()->GetSize(); i++)
                        cout << graph->TopologicalSort()->Get(i) << " ";
                    cout << endl;
                }
                break;
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
        case 0:
            break;
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
            switch (choose) {
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
            break;
        default:
            return;
    }
}

int main() {
    alltests();
    InterfaceGraph();
    return 0;
}
//???????????????? ?????? ???????????? ?????????? ?????????? ?????????????????? ???????????????????????????? ??????????????
