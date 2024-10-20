#include "graph_algorithms.h"

namespace s21 {

GraphAlgorithms::GraphAlgorithms() {}
GraphAlgorithms::~GraphAlgorithms() {}

std::vector<int> GraphAlgorithms::DepthFirstSearch(Graph &graph,
                                                   int start_vertex) {
  int vertex = graph.GetCountVertex();
  if (start_vertex < 0 || start_vertex >= vertex) return {};

  std::unordered_set<int> visited;
  std::vector<int> answer;
  Stack<int> s;
  s.push(start_vertex);
  visited.insert(start_vertex);
  answer.emplace_back(start_vertex);
  while (!s.empty()) {
    int cur = s.top();

    for (int i : graph.Adjacency(cur)) {
      if (!visited.count(i)) {
        s.push(i);
        visited.insert(i);
        answer.emplace_back(i);
        break;
      }
    }
    if (cur == s.top()) s.pop();
  }
  return answer;
}
std::vector<int> GraphAlgorithms::BreadthFirstSearch(Graph &graph,
                                                     int start_vertex) {
  int vertex = graph.GetCountVertex();
  if (start_vertex < 0 || start_vertex >= vertex) return {};
  std::unordered_set<int> visited;
  std::vector<int> answer;
  Queue<int> q;
  q.push(start_vertex);
  visited.insert(start_vertex);

  while (!q.empty()) {
    int cur = q.front();
    q.pop();
    answer.emplace_back(cur);
    for (int next : graph.Adjacency(cur)) {
      if (!visited.count(next)) {
        q.push(next);
        visited.insert(next);
      }
    }
  }
  return answer;
}
// города нумеруется цифрами или буквами, есть ли город под номером 0?
int GraphAlgorithms::GetShortestPathBetweenVertices(Graph &graph, int vertex1,
                                                    int vertex2) {
  std::unordered_set<int> visited;
  std::vector<int> distance(graph.GetCountVertex(), -1);
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                      std::greater<std::pair<int, int>>>
      q;
  q.push({0, vertex1});

  while (!q.empty()) {
    auto [dist, city] = q.top();
    q.pop();
    if (city == vertex2) return distance[city];
    if (distance[city] != -1 && distance[city] < dist) continue;
    visited.insert(city);
    for (auto [next, next_dist] : graph.AdjacencyWeight(city)) {
      if (!visited.count(next)) {
        if (distance[next] == -1 || distance[next] > dist + next_dist) {
          q.push({next_dist + dist, next});
          distance[next] = dist + next_dist;
        }
      }
    }
  }
  return -1;
}
std::vector<std::vector<int>>
GraphAlgorithms::GetShortestPathsBetweenAllVertices(Graph &graph) {
  int vertex = graph.GetCountVertex();
  auto g = graph.GetData();
  for (int j = 0; j < vertex; ++j) {
    for (int i = 0; i < vertex; ++i) {
      for (int k = 0; k < vertex; ++k) {
        if (k == j || i == j || i == k) continue;
        if (g[i][j] && g[j][k] && (!g[i][k] || g[i][k] > g[i][j] + g[j][k]))
          g[i][k] = g[i][j] + g[j][k];
      }
    }
  }
  return g;
}
std::vector<std::vector<int>> GraphAlgorithms::GetLeastSpanningTree(
    Graph &graph) {
  auto g = graph.GetData();
  int vertex = graph.GetCountVertex();
  if (!vertex) return {};
  std::vector<std::vector<int>> spanning(vertex, std::vector<int>(vertex, 0));
  std::vector<bool> visited(vertex, false);
  std::vector<int> parent(vertex, -1);
  std::vector<int> weight(vertex, INT_MAX);
  // возможно через очередь быстрее будет
  // std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>>,
  // std::greater<std::pair<int, int>>> q;

  weight[0] = 0;
  for (size_t i = 0; i < g.size(); ++i) {
    int v = -1, min = INT_MAX;
    for (int k = 0; k < vertex; ++k) {
      if (!visited[k] && weight[k] < min) {
        v = k;
        min = weight[k];
      }
    }
    if (v == -1) continue;
    if (parent[v] != -1) {
      spanning[parent[v]][v] = min;
      spanning[v][parent[v]] = min;
    }
    visited[v] = true;

    for (int k = 0; k < vertex; ++k) {
      if (g[v][k] && !visited[k] && g[v][k] < weight[k]) {
        parent[k] = v;
        weight[k] = g[v][k];
      }
    }
  }
  return spanning;
}

// Ant algorithms
TsmResult GraphAlgorithms::SolveTravelingSalesmanProblem(Graph &graph) {
  TsmResult res;
  Ant a(graph.GetData());
  res = a.Solve();

  return res;
}

// FullRecursion TSP
TsmResult GraphAlgorithms::SolveTravelingSalesmanProblemR(Graph &graph) {
  auto g = graph.GetData();
  int vertex = graph.GetCountVertex();

  TsmResult res, temp;
  if (!vertex) return res;
  res.vertices.reserve(vertex + 1);
  temp.vertices.reserve(vertex + 1);
  std::vector<bool> visited(vertex, false);

  Recur(g, visited, res, temp, -1, vertex);
  return res;
}

void GraphAlgorithms::Recur(std::vector<std::vector<int>> &graph,
                            std::vector<bool> &visited, TsmResult &res,
                            TsmResult &temp, int vertex, int all_vertex) {
  if (static_cast<int>(temp.vertices.size()) == all_vertex) {
    int start = temp.vertices[0];
    int last = temp.vertices.back();
    if (graph[last][start] != 0) {
      if (res.distance == 0 ||
          res.distance > temp.distance + graph[last][start]) {
        res.vertices = temp.vertices;
        res.vertices.emplace_back(start);
        res.distance = temp.distance + graph[last][start];
      }
    }
    return;
  }

  for (int i = 0; i < all_vertex; ++i) {
    if (vertex == -1 || (i != vertex && !visited[i] && graph[vertex][i])) {
      temp.vertices.emplace_back(i);
      if (vertex >= 0) temp.distance += graph[vertex][i];
      visited[i] = true;
      Recur(graph, visited, res, temp, i, all_vertex);
      temp.vertices.pop_back();
      if (vertex >= 0) temp.distance -= graph[vertex][i];
      visited[i] = false;
    }
  }
}
// Burn metod

TsmResult GraphAlgorithms::SolveTravelingSalesmanProblemB(Graph &graph) {
  std::vector<std::vector<int>> g = graph.GetData();
  int row = g.size(), col = 0;
  TsmResult result;
  if (row) col = g[0].size();
  if (!row || !col) return result;

  int count = row * 1000;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(0, row - 1);
  std::uniform_real_distribution<double> distd(0, 1);
  std::vector<bool> visited(row, false);

  if (!FindAnyPath(visited, result, g)) return result;

  double t = 1 + result.distance / 5;
  for (int i = 0; i < count; ++i) {
    t *= 0.99;
    std::vector<int> temp = result.vertices;
    temp.pop_back();
    int s = dist(gen), end = dist(gen);
    if (s > end) std::swap(s, end);
    std::reverse(temp.begin() + s, temp.begin() + end);
    // std::swap(temp[dist(gen)], temp[dist(gen)]);
    int distance = Calculate(temp, g);

    if (distance > 0 && (distance < result.distance ||
                         distd(gen) < exp((result.distance - distance) / t))) {
      result.distance = distance;
      result.vertices = temp;
    }
  }
  return result;
}
int GraphAlgorithms::Calculate(std::vector<int> &p,
                               std::vector<std::vector<int>> &g) {
  int row = g.size(), dist = 0;

  if (!g[p[row - 1]][p[0]]) return -1;
  p.emplace_back(p[0]);

  for (size_t i = 1; i < p.size(); ++i) {
    if (!g[p[i - 1]][p[i]]) return -1;
    dist += g[p[i - 1]][p[i]];
  }
  return dist;
}

bool GraphAlgorithms::FindAnyPath(std::vector<bool> &visited, TsmResult &path,
                                  std::vector<std::vector<int>> &graph) {
  if (!path.vertices.empty() && path.vertices.size() == graph.size() &&
      graph[path.vertices.back()][path.vertices[0]]) {
    path.distance += graph[path.vertices.back()][path.vertices[0]];
    path.vertices.emplace_back(path.vertices[0]);

    return true;
  }

  for (std::size_t i = 0; i < graph.size(); ++i) {
    int vertex = path.vertices.empty() ? i : path.vertices.back();
    if (!visited[i] && (path.vertices.empty() || graph[vertex][i])) {
      path.vertices.emplace_back(i);
      path.distance += graph[vertex][i];
      visited[i] = true;
      if (FindAnyPath(visited, path, graph)) return true;
      path.vertices.pop_back();
      path.distance -= graph[vertex][i];
      visited[i] = false;
    }
  }
  return false;
}
}  // end namespace s21
