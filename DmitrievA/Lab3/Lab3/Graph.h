#pragma once
#include <algorithm>
#include <iostream>
#include <list>
#include <queue>
#include <random>
#include <vector>

using std::invalid_argument;
using std::out_of_range;
using std::vector;
using std::list;
using std::cout;

struct Edge {
  size_t to;
  unsigned weight;
};

struct MatrixCell {
  unsigned weight;
  bool connected;
  MatrixCell() : weight(0), connected(false) {}
  MatrixCell(int w, bool c) : weight(w), connected(c) {}
};


class Graph {
 private:
  size_t numVertices;

 public:
  Graph(size_t vertices) : numVertices{vertices} {}

  virtual void setEdge(size_t u, size_t v, unsigned weight) = 0;

  void generateRandom(unsigned numEdges, unsigned minWeight, unsigned maxWeight) {
    size_t maxPossibleEdges = (size_t)numVertices * (numVertices - 1) / 2;
    if (numEdges > maxPossibleEdges) {
      throw invalid_argument("Too many edges for the number of vertices");
    }
    if (numEdges < numVertices - 1) {
      throw invalid_argument("Too few edges to ensure connectivity");
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> vertexDist(0, numVertices - 1);
    std::uniform_int_distribution<unsigned> weightDist(minWeight, maxWeight);

    // чтобы граф гарантированно был связным, сначала создаем
    // остов (0-1, 1-2, 2-3 ...), а затем остальные ребра
    for (int i = 0; i < numVertices - 1; ++i) {
      setEdge(i, i + 1, weightDist(gen));
    }

    size_t currentEdges = numVertices - 1;

    // случайным образом генерируем оставшиеся ребра без повторов
    while (currentEdges < numEdges) {
      size_t u = vertexDist(gen);
      size_t v = vertexDist(gen);

      // добавляем ребро только если вершины разные и между ними еще нет связи
      if (u != v && !hasEdge(u, v)) {
        setEdge(u, v, weightDist(gen));
        currentEdges++;
      }
    }
  }

  virtual bool isConnected() const = 0;

  size_t getVerticesCount() const {
    return numVertices;
  }

  virtual void print() const = 0;

  virtual vector<Edge> getNeighbors(size_t u) const = 0;

  virtual bool hasEdge(size_t u, size_t v) const = 0;
};

class MatrixGraph : public Graph {
 private:
  size_t numVertices;
  vector<vector<MatrixCell>> adjMatrix;

 public:
  MatrixGraph(size_t vertices) : Graph(vertices), numVertices(vertices) {
    adjMatrix.assign(vertices, vector<MatrixCell>(vertices, MatrixCell()));
  }
  void setEdge(size_t u, size_t v, unsigned weight) override {
    if (u < 0 || u >= numVertices || v < 0 || v >= numVertices)
      throw out_of_range("Vertex index out of range");
    if (u == v)
      throw invalid_argument("Self-loops are not allowed");
    adjMatrix[u][v].weight = weight;
    adjMatrix[u][v].connected = true;
    adjMatrix[v][u].weight = weight;
    adjMatrix[v][u].connected = true;
  }
  bool hasEdge(size_t u, size_t v) const override {
    if (u < 0 || u >= numVertices || v < 0 || v >= numVertices)
      throw out_of_range("Vertex index out of range");
    return adjMatrix[u][v].connected;
  }

  bool isConnected() const override {
    if (numVertices == 0)
      return true;

    std::vector<bool> visited(numVertices, false);
    std::queue<size_t> q;

    q.push(0);  // обход в ширину
    visited[0] = true;
    size_t visitedCount = 1;

    while (!q.empty()) {
      size_t u = q.front();
      q.pop();
      for (int v = 0; v < numVertices; ++v) {
        if (adjMatrix[u][v].connected && !visited[v]) {
          visited[v] = true;
          q.push(v);
          visitedCount++;
        }
      }
    }
    return visitedCount == numVertices;  // совпадает ли число посещенных вершин
                                         // с общим количеством
  }

  void print() const override {
    for (size_t i = 0; i < numVertices; ++i) {
      cout << i << ": ";
      for (size_t j = 0; j < numVertices; ++j) {
        if (adjMatrix[i][j].connected)
          cout << "-> " << j << "(" << adjMatrix[i][j].weight << ") ";
      }
      cout << "\n";
    }
  }
  vector<Edge> getNeighbors(size_t u) const override {
    vector<Edge> neighbors;
    for (size_t v = 0; v < numVertices; ++v) {
      if (adjMatrix[u][v].connected) {
        neighbors.push_back({v, adjMatrix[u][v].weight});
      }
    }
    return neighbors;
  }
};

class ListGraph : public Graph {
 private:
  size_t numVertices;
  vector<list<Edge>> adjList;

 public:
  ListGraph(size_t vertices) : Graph(vertices), numVertices(vertices) {
    adjList.resize(vertices);
  }
  void setEdge(size_t u, size_t v, unsigned weight) override {
    if (u < 0 || u >= numVertices || v < 0 || v >= numVertices)
      throw out_of_range("Vertex index out of range");
    if (u == v)
      throw invalid_argument("Self-loops are not allowed");
    if (hasEdge(u, v)) {
      for (auto& edge : adjList[u]) {
        if (edge.to == v) {
          edge.weight = weight;
        }
      }
      for (auto& edge : adjList[v]) {
        if (edge.to == u) {
          edge.weight = weight;
        }
      }
      return;
    }
    adjList[u].push_back({v, weight});
    adjList[v].push_back({u, weight});
  }
  bool hasEdge(size_t u, size_t v) const override {
    if (u < 0 || u >= numVertices || v < 0 || v >= numVertices)
      throw out_of_range("Vertex index out of range");
    for (const auto& edge : adjList[u]) {
      if (edge.to == v)
        return true;
    }
    return false;
  }

  bool isConnected() const override {
    if (numVertices == 0)
      return true;

    std::vector<bool> visited(numVertices, false);
    std::queue<size_t> q;

    q.push(0);  // обход в ширину
    visited[0] = true;
    int visitedCount = 1;

    while (!q.empty()) {
      size_t u = q.front();
      q.pop();
      for (const auto& edge : adjList[u]) {
        if (!visited[edge.to]) {
          visited[edge.to] = true;
          q.push(edge.to);
          visitedCount++;
        }
      }
    }
    return visitedCount == numVertices;  // совпадает ли число посещенных вершин
                                         // с общим количеством
  }

  void print() const override {
    for (int i = 0; i < numVertices; ++i) {
      std::cout << i << ": ";
      for (const auto& edge : adjList[i])
        std::cout << "-> " << edge.to << "(" << edge.weight << ") ";
      std::cout << "\n";
    }
  }
  vector<Edge> getNeighbors(size_t u) const override {
    vector<Edge> neighbors;
    for (const auto& edge : adjList[u]) {
      neighbors.push_back(edge);
    }
    return neighbors;
  }
};
