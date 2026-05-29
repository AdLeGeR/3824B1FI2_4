#pragma once
#include <iostream>
#include <vector>

#include "BinaryHeap.h"
#include "Graph.h"

using std::out_of_range;
using std::vector;
using std::reverse;

struct DijkstraResult {
  vector<unsigned> dist;  // дистанция до вершины с индексом i
  vector<size_t> parent;  // родитель вершины с индексом i в пути до нее
  size_t startNode;
};

struct VertexNode {
  size_t vertex;
  unsigned dist;
  bool operator>(struct VertexNode other) const {
    return dist > other.dist;
  }
  bool operator<(struct VertexNode other) const {
    return dist < other.dist;
  }
  bool operator==(struct VertexNode other) const {
    return dist < other.dist;
  }
};

typedef struct VertexNode VertexNode;

class DijkstraSolver {
 public:
  DijkstraResult solve(const Graph* graph,
                       size_t startNode,
                       QueueWithTracking<VertexNode>* pq) {
    size_t n = graph->getVerticesCount();

    if (startNode < 0 || startNode >= n) {
      throw out_of_range("Start node index out of range");
    }

    // по умолчанию все вершины недостижимы (false)
    vector<pair<unsigned, bool>> dist(
        n, pair<unsigned, bool>(0, false));  // дистанция до вершин

    vector<pair<size_t, bool>> parent(
        n, pair<size_t, bool>(0, false));  // родитель вершины в пути до нее
                                           // (false для недостижимых)

    vector<pair<size_t, bool>> queued(
        n, {0, false});  // флаг, была ли вершина добавлена в очередь и id в
                         // этой очереди

    dist[startNode] = {0, true};

    size_t index = pq->push({startNode, 0});
    queued[startNode] = {index, true};

    while (!pq->isEmpty()) {
      VertexNode top = pq->pop();
      size_t u = top.vertex;
      queued[u].second = false;
      // получаем соседей
      vector<Edge> neighbors = graph->getNeighbors(u);

      for (const auto& edge : neighbors) {
        size_t v = edge.to;
        unsigned weight = edge.weight;

        unsigned nextDist = dist[u].first + weight;
        if (nextDist < weight) {
          nextDist = UINT32_MAX;  // если сумма уже превышает максимальный
                                  // вес, то ограничиваем
        }

        // если целевая вершина еще не достигалась
        if (dist[v].second == false) {
          dist[v].first = nextDist;
          dist[v].second = true;  // помечаем вершину как достижимую
          // обновляем родителя
          parent[v].first = u;
          parent[v].second = true;  // помечаем родителя как достижимого
          // кладём в очередь
          queued[v].first = pq->push({v, dist[v].first});
          queued[v].second = true;
        }
        // если вершина уже достижима, но нашли более короткий путь до нее
        else if (nextDist < dist[v].first) {
          dist[v].first = nextDist;

          // обновляем родителя
          parent[v].first = u;

          // меняем расстояние до соседа в очереди
          pq->decreaseKey(queued[v].first, {v, dist[v].first});
        }
      }
    }
    // т.к. мы в начале проверили на связанность, то в dist и parent не будет
    // недостижимых вершин, и мы можем просто скопировать данные в результат
    vector<unsigned> resDist(n);
    for (size_t i = 0; i < n; ++i) {
      resDist[i] = dist[i].first;
    }
    vector<size_t> resParent(n);
    for (size_t i = 0; i < n; ++i) {
      resParent[i] = parent[i].first;
    }
    return {resDist, resParent, startNode};
  }
};

vector<size_t> getPath(const DijkstraResult& result,
                       size_t targetNode) {  // кратчайший путь до вершины
  vector<size_t> path;

  for (size_t v = targetNode; v != -1; v = result.parent[v]) {
    path.push_back(v);
  }

  reverse(path.begin(), path.end());
  return path;
}