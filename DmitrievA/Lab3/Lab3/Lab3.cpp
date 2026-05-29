#include <iostream>
#include <vector>

#include "QueueWithTracking.h"
#include "BinaryHeap.h"
#include "Dijkstra.h"
#include "Graph.h"
#include "FibonacciHeap.h"

using std::cout;
using std::vector;
using std::exception;
using std::cin;

DijkstraResult runDijkstraDHeap(const Graph* graph, size_t start) {
  DijkstraSolver solver;
  BinaryHeapWithTracking<VertexNode> bh(graph->getVerticesCount());
    QueueWithTracking<VertexNode>* pq= &bh;
  return solver.solve(graph, start, pq);
}

DijkstraResult runDijkstraFibonacci(const Graph* graph, size_t start) {
  DijkstraSolver solver;
  FibonacciHeapWithTracking<VertexNode> fh;
  QueueWithTracking<VertexNode>* pq = &fh;
  return solver.solve(graph, start, pq);
}

vector<size_t> getPathDHeap(const DijkstraResult& result, size_t target) {
  return getPath(result, target);
}

vector<size_t> getPathBinomial(const DijkstraResult& result, size_t target) {
  return getPath(result, target);
}


size_t readSize_t() {  // ввод чисел
  size_t value;
  cin >> value;
  while (cin.fail()) {
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cout << "Ошибка! Введите целое число: ";
    cin >> value;
  }
  return value;
}

unsigned readUnsigned() {  // ввод чисел
  unsigned value;
  cin >> value;
  while (cin.fail()) {
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cout << "Ошибка! Введите целое число: ";
    cin >> value;
  }
  return value;
}

int readInt() {  // ввод чисел
  int value;
  cin >> value;
  while (cin.fail()) {
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cout << "Ошибка! Введите целое число: ";
    cin >> value;
  }
  return value;
}

int main() {
  cout << "=== Dijkstra's Algorithm ===\n";

  cout << "\nChoose a graph storage method:\n";
  cout << "1. Adjacency list\n";
  cout << "2. Adjacency matrix\n";
  cout << "Your choice (1 or 2): ";
  int storageChoice = readInt();
  while (storageChoice < 1 || storageChoice > 2) {
    cout << "Wrong choice! Enter 1 or 2: ";
    storageChoice = readInt();
  }

  // ввод количества вершин
  cout << "Enter graph's vertex count: ";
  int numVertices = readInt();
  while (numVertices <= 0) {
    cout << "Vertex count must be greater than zero! Try again: ";
    numVertices = readInt();
  }
  Graph* graphPtr;
  if (storageChoice == 1) {
    graphPtr = new ListGraph(numVertices);
  } else {
    graphPtr = new MatrixGraph(numVertices);
  }

  // выбор способа создания графа
  cout << "\nChoose the graph creation method:\n";
  cout << "1. Enter the edges\n";
  cout << "2. Generate random\n";
  cout << "Your choice (1 or 2): ";
  int initChoice = readInt();
  while (initChoice < 1 || initChoice > 2) {
    cout << "Wrong choice! Enter 1 or 2: ";
    initChoice = readInt();
  }

  if (initChoice == 1) {
    cout << "Enter edges count: ";
    size_t numEdges = readSize_t();
    while (numEdges < 0) {
      cout << "The number of edges cannot be less than zero! Try again: ";
      numEdges = readInt();
    }

    cout << "Enter the edges in the format: <from> <to> <weight> "
                 "(separated by a space):\n";
    cout << "(The vertex numbers must be from 0 to " << numVertices - 1
              << ")\n";

    for (size_t i = 0; i < numEdges; i++) {
      cout << "Edge " << i + 1 << ": ";
      size_t u = readSize_t();
      size_t v = readSize_t();
      unsigned weight = readUnsigned();

      // поверка корректности ввода ребра
      if (u < 0 || u >= numVertices || v < 0 || v >= numVertices ||
          weight < 0) {
        cout
            << "An error in the edge data! Try to enter this edge again..\n";
        i--;  // повторяем ввод
        continue;
      }
      graphPtr->setEdge(u, v, weight);
    }
  } else {
    cout << "Enter the number of edges for random generation: ";
    int numEdges = readInt();
    cout << "Enter the minimum edge weight: ";
    int minWeight = readInt();
    cout << "Enter the maximum edge weight: ";
    int maxWeight = readInt();

    graphPtr->generateRandom(numEdges, minWeight, maxWeight);
    cout << "Random graph is created!\n";
  }


  // переменные для хранения результатов работы алгоритма
  DijkstraResult activeResult;
  bool isSolved = false;   // запускали ли уже алгоритм
  int activeHeapType = 0;  // какую кучу мы выбрали (1 - бинар, 2 - бином)

  // меню программы
  bool running = true;
  while (running) {
    cout << "\n------------   Menu   ------------\n";
    cout << "1. Display the graph structure\n";
    cout << "2. Start Dijkstra's Algorithm\n";
    cout << "3. Find the shortest path to the vertex\n";
    cout << "4. Exit\n";
    cout << "Enter the choice: ";
    int menuChoice = readInt();

    switch (menuChoice) {
      case 1: {
        cout << "\n------- Graph structur -------\n";
        graphPtr->print();
        break;
      }
      case 2: {
        cout << "Enter the start vertex (from 0 to " << numVertices - 1
                  << "): ";
        size_t startNode = readSize_t();
        while (startNode >= numVertices) {
          cout << "There is now such vertex! Try again: ";
          startNode = readSize_t();
        }

        cout << "Choose the queue (heap):\n";
        cout << "1. Binary heap\n";
        cout << "2. Fibonacci heap\n";
        int heapChoice = readInt();
        while (heapChoice < 1 || heapChoice > 2) {
          cout << "Wrong choice! Enter 1 or 2: ";
          heapChoice = readInt();
        }

        try {
          if (heapChoice == 1) {
            activeResult = runDijkstraDHeap(graphPtr, startNode);
            activeHeapType = 1;
            cout << "The algorithm was successfully executed through the "
                         "binary heap.\n";
          } else {
            activeResult = runDijkstraFibonacci(graphPtr, startNode);
            activeHeapType = 2;
            cout << "The algorithm was successfully executed through the "
                         "Fibonacci heap.\n";
          }
          isSolved = true;
        } catch (const exception& e) {
          cout << "An error occurred while executing: " << e.what()
                    << "\n";
        }
        break;
      }
      case 3: {
        if (isSolved == false) {
          cout
              << "First you need to run Dijkstra's algorithm (Menu item 2)!\n";
          break;  // выходим из switch, цикл пойдет на следующий круг
        }

        cout << "Enter the end vertex (from 0 to " << numVertices - 1
                  << "): ";
        size_t targetNode = readSize_t();
        while (targetNode >= numVertices) {
          cout << "There is now such vertex! Try again: ";
          targetNode = readSize_t();
        }

        // получаем путь
        vector<size_t> path;
        if (activeHeapType == 1) {
          path = getPathDHeap(activeResult, targetNode);
        } else {
          path = getPathBinomial(activeResult, targetNode);
        }

        // выводим результаты
        if (activeResult.dist[targetNode] == -1) {
          cout << "There is no path from vertex " << activeResult.startNode
                    << "to vertex " << targetNode << "\n";
        } else {
          cout << "Shortest distance: " << activeResult.dist[targetNode]
                    << "\n";
          cout << "Path: ";
          for (size_t i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i + 1 < path.size()) {
              cout << " -> ";
            }
          }
          cout << "\n";
        }
        break;
      }
      case 4: {
        cout << "Program shutdown.\n";
        running = false;  // чтобы цикл завершился
        break;
      }
      default: {
        cout << "Incorrect menu item! Try again.\n";
        break;
      }
    }
  }
  return 0;
}
