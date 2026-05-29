#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

#include "../Lab3/BinaryHeap.h"
#include "../Lab3/Dijkstra.h"
#include "../Lab3/FibonacciHeap.h"
#include "../Lab3/Graph.h"

struct RawEdge {  // структура для промежуточного хранения ребер, чтобы
                  // использовать ее для всех структур данных
  int u;
  int v;
  int weight;
};

std::vector<RawEdge> generateRawGraph(
    int numVertices,
    int numEdges,
    int minW,
    int maxW) {  // функция генерации списка рёбер графа
  std::vector<RawEdge> edges;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> weightDist(minW, maxW);
  std::uniform_int_distribution<> vertexDist(0, numVertices - 1);

  // чтобы граф гарантированно был связным, соединяем вершины в цепочку
  for (int i = 0; i < numVertices - 1; ++i) {
    edges.push_back({i, i + 1, weightDist(gen)});
  }

  // матрица существования рёбер
  std::vector<std::vector<bool>> hasEdge(numVertices,
                                         std::vector<bool>(numVertices, false));
  for (int i = 0; i < numVertices - 1; ++i) {
    hasEdge[i][i + 1] = true;
    hasEdge[i + 1][i] = true;
  }

  int maxPossible = numVertices * (numVertices - 1) / 2;
  int targetEdges = numEdges;
  if (targetEdges > maxPossible)
    targetEdges = maxPossible;
  if (targetEdges < numVertices - 1)
    targetEdges = numVertices - 1;

  int currentEdges = numVertices - 1;
  while (currentEdges < targetEdges) {
    int u = vertexDist(gen);
    int v = vertexDist(gen);
    if (u != v && !hasEdge[u][v]) {
      edges.push_back({u, v, weightDist(gen)});
      hasEdge[u][v] = true;
      hasEdge[v][u] = true;
      currentEdges++;
    }
  }
  return edges;
}

void populateGraph(
    Graph* g,
    const std::vector<RawEdge>& rawEdges) {  // заполнение графа из набора рёбер
  for (size_t i = 0; i < rawEdges.size(); ++i) {
    g->setEdge(rawEdges[i].u, rawEdges[i].v, rawEdges[i].weight);
  }
}

struct Config {  // конфигурация для одного эксперимента
  int vertices;
  int edges;
  std::string densityType;  // разреженный или плотный
};

int main() {
  // конфигурации (вершины, ребра, характеристика)
  std::vector<Config> configs;
  configs.push_back({100, 150, "Sparse"});  // Sparse - разреженный
  configs.push_back({100, 2000, "Dense"});  // Dense - плотный
  configs.push_back({500, 1000, "Sparse"});
  configs.push_back({500, 50000, "Dense"});
  configs.push_back({1000, 3000, "Sparse"});
  configs.push_back({1000, 100000, "Dense"});

  // печатаем шапку таблицы
  std::cout << std::left << std::setw(10) << "Vertices" << std::setw(10)
            << "Edges" << std::setw(15) << "S/D" << std::setw(12) << "List Binary"
            << std::setw(12) << "List Fibonacci" << std::setw(12) << "Matrix Binary"
            << std::setw(12) << "Matrix Binom" << "\n";
  std::cout << "---------------------------------------------------------------"
               "--------------------------\n";

  for (size_t c = 0; c < configs.size(); ++c) {
    Config config = configs[c];

    double timeAL_Binary = 0;
    double timeAL_Binomial = 0;
    double timeAM_Binary = 0;
    double timeAM_Binomial = 0;

    std::vector<RawEdge> rawEdges =
        generateRawGraph(config.vertices, config.edges, 1, 100);

    // случайная стартовая вершина
    int startNode = rand() % config.vertices;

    Graph* graphAL = new ListGraph(config.vertices);
    Graph* graphAM = new MatrixGraph(config.vertices);
    populateGraph(graphAL, rawEdges);
    populateGraph(graphAM, rawEdges);
    BinaryHeapWithTracking<VertexNode> bh(graphAL->getVerticesCount());
    FibonacciHeapWithTracking<VertexNode> fh;

    DijkstraSolver solver;

    // 1: AL + BinaryHeap

    auto start = std::chrono::high_resolution_clock::now();
    DijkstraResult res = solver.solve(graphAL, startNode, &bh);
    auto end = std::chrono::high_resolution_clock::now();
    double AL_Binary =
        std::chrono::duration<double, std::milli>(end - start).count();

    // 2: AL + FibonacciHeap

    start = std::chrono::high_resolution_clock::now();
    res = solver.solve(graphAL, startNode, &fh);
    end = std::chrono::high_resolution_clock::now();
    double AL_Binomial =
        std::chrono::duration<double, std::milli>(end - start).count();

    // 3: AM + BinaryHeap

    start = std::chrono::high_resolution_clock::now();
    res = solver.solve(graphAM, startNode, &bh);
    end = std::chrono::high_resolution_clock::now();
    double AM_Binary =
        std::chrono::duration<double, std::milli>(end - start).count();

    // 4: AM + FibonacciHeap

    start = std::chrono::high_resolution_clock::now();
    res = solver.solve(graphAM, startNode, &fh);
    end = std::chrono::high_resolution_clock::now();
    double AM_Binomial =
        std::chrono::duration<double, std::milli>(end - start).count();

    std::cout << std::left << std::setw(10) << config.vertices << std::setw(10)
              << config.edges << std::setw(15) << config.densityType
              << std::fixed << std::setprecision(3) << std::setw(12)
              << AL_Binary << std::setw(12) << AL_Binomial << std::setw(12)
              << AM_Binary << std::setw(12) << AM_Binomial << "\n";
  }

  std::cout << "---------------------------------------------------------------"
               "--------------------------\n";
  return 0;
}