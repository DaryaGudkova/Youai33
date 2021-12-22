/*#include <iostream>
#include "tests.h"
#include "GraphPrinter.h"

using namespace std;

Graph<int>* Graph1()
{
    Graph<int>* gr = new Graph<int>(7, true);
    gr->changeEdge(0, 1, 15);
    gr->changeEdge(0, 2, 2);
    gr->changeEdge(0, 6, 1);
    gr->changeEdge(2, 3, 3);
    gr->changeEdge(2, 4, 4);
    gr->changeEdge(3, 1, 1);
    gr->changeEdge(4, 1, 2);
    gr->changeEdge(5, 4, 10);
    gr->changeEdge(6, 0, 1);
    return gr;
}
Graph<int>* Graph2()
{
    Graph<int>* gr = new Graph<int>(10, false);
    gr->changeEdge(0, 7, 1);
    gr->changeEdge(7, 1, 100);
    gr->changeEdge(7, 3, 15);
    gr->changeEdge(7, 3, 12);
    gr->changeEdge(7, 6, 2);
    gr->changeEdge(3, 6, 3);
    gr->changeEdge(1, 2, 10);
    gr->changeEdge(2, 3, 20);
    gr->changeEdge(4, 5, 9);

    return gr;
}



template <typename T>
void GraphConstructuor(Graph<T>* graph) {
    int choose = 0;
    int ver1 = 0;
    int ver2 = 0;
    T weight = T(1);
    while (true)
    {
        cout << "1 - change an edge" << endl;
        cout << "2 - Print Matrix" << endl;
        cout << "3 - Find Shortest path from ver1 to ver2" << endl;
        cout << "4 - exit" << endl;
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
                AdjacencyMatrix(graph);
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
            default:
                return;
        }
    }
};


void interfaceGraph()
{
    int choose = 0;
    int number = 0;
    int i = 0;
    int j = 0;
    int vert1 = 0;
    int vert2 = 0;
    int weight = 0;
    Graph<int>* gr;

    cout << "1 - Graph1" << endl;
    cout << "2 - Graph2" << endl;
    cout << "3 - to create a graph yourself" << endl;
    cout << "4 - exit" << endl;
    cin >> choose;
    cout << endl;
    switch (choose)
    {
        case 1:
            gr = Graph1();
            GraphConstructuor(gr);
            break;
        case 2:
            gr = Graph2();
            GraphConstructuor(gr);
            break;
        case 3:
            cout << "Enter a number of vertexes" << endl;
            cin >> number;
            cout << "Enter 1 if the graph is directed" << endl;
            cin >> choose;
            switch (choose)
            {
                case 1:
                    gr = new Graph<int>(number, true);
                    GraphConstructuor(gr);
                    break;
                default:
                    gr = new Graph<int>(number, false);
                    GraphConstructuor(gr);
                    break;
            }

    }
};


int main() {
    alltests();
    interfaceGraph();
    return 0;
}
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define SIZE 6
int main()
{
    int matrix[SIZE][SIZE]; // матрица связей
    int minDist[SIZE]; // минимальное расстояние
    int visitedVertex[SIZE]; // посещенные вершины
    int temp, minIndex, minWeight;
    int beginIndex = 0;
    //system("chcp 1251");
    //system("cls");
    // Инициализация матрицы связей
    for (int i = 0; i<SIZE; i++)
    {
        matrix[i][i] = 0;
        for (int j = i + 1; j<SIZE; j++) {
            printf("Enter the distance %minDist - %minDist: ", i + 1, j + 1);
            scanf("%minDist", &temp);
            matrix[i][j] = temp;
            matrix[j][i] = temp;
        }
    }
    // Вывод матрицы связей
    for (int i = 0; i<SIZE; i++)
    {
        for (int j = 0; j<SIZE; j++)
            printf("%5d ", matrix[i][j]);
        printf("\n");
    }
    //Инициализация вершин и расстояний
    for (int i = 0; i<SIZE; i++)
    {
        minDist[i] = 10000;
        visitedVertex[i] = 1;
    }
    minDist[beginIndex] = 0;
    // Шаг алгоритма
    do {
        minIndex = 10000;
        minWeight = 10000;
        for (int i = 0; i<SIZE; i++)
        { // Если вершину ещё не обошли и вес меньше minWeight
            if ((visitedVertex[i] == 1) && (minDist[i] < minWeight))
            { // Переприсваиваем значения
                minWeight = minDist[i];
                minIndex = i;
            }
        }
        // Добавляем найденный минимальный вес
        // к текущему весу вершины
        // и сравниваем с текущим минимальным весом вершины
        if (minIndex != 10000)
        {
            for (int i = 0; i<SIZE; i++)
            {
                if (matrix[minIndex][i] > 0)
                {
                    temp = minWeight + matrix[minIndex][i];
                    if (temp < minDist[i])
                    {
                        minDist[i] = temp;
                    }
                }
            }
            visitedVertex[minIndex] = 0;
        }
    } while (minIndex < 10000);
    // Вывод кратчайших расстояний до вершин
    printf("\nShortest distances to the peaks: \n");
    for (int i = 0; i<SIZE; i++)
        printf("%5d ", minDist[i]);

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
    // Вывод пути (начальная вершина оказалась в конце массива из k элементов)
    printf("\nВывод кратчайшего пути\n");
    for (int i = k - 1; i >= 0; i--)
        printf("%3d ", ver[i]);
    getchar(); getchar();
    return 0;
}
void Dijkstra(int GR[V][V], int st)
{
    int distance[V], count, index, i, u, m=st+1;
    bool visited[V];
    for (i=0; i<V; i++)
    {
        distance[i]=INT_MAX; visited[i]=false;
    }
    distance[st]=0;
    for (count=0; count<V-1; count++)
    {
        int min=INT_MAX;
        for (i=0; i<V; i++)
            if (!visited[i] && distance[i]<=min)
            {
                min=distance[i]; index=i;
            }
        u=index;
        visited[u]=true;
        for (i=0; i<V; i++)
            if (!visited[i] && GR[u][i] && distance[u]!=INT_MAX &&
                distance[u]+GR[u][i]<distance[i])
                distance[i]=distance[u]+GR[u][i];
    }
    cout<<"Стоимость пути из начальной вершины до остальных:\t\n";
    for (i=0; i<V; i++) if (distance[i]!=INT_MAX)
            cout<<m<<" > "<<i+1<<" = "<<distance[i]<<endl;
        else cout<<m<<" > "<<i+1<<" = "<<"маршрут недоступен"<<endl;
}