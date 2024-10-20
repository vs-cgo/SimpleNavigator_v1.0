#include "./ant.h"

namespace s21 {
Ant::Ant(std::vector<std::vector<int>> g)
    : a(1), b(1), kQ(4), p(0.8), graph(g) {}
Ant::~Ant() {}

TsmResult Ant::Solve() {
  int row = graph.size(), col = 0;
  if (row > 0) col = graph[0].size();
  if (!row || !col) return TsmResult{};

  TsmResult result;

  pheromon = std::vector<std::vector<double>>(row, std::vector<double>(row, 1));
  for (int i = 0; i < row; ++i) {
    pheromon[i][i] = 0;
  }
  int count = 250;
  for (int i = 0; i < count; ++i) {
    std::vector<std::vector<double>> local_pheromon(
        row, std::vector<double>(row, 0));

    for (int vertex = 0; vertex < row; ++vertex) {
      std::vector<bool> visited(row, false);
      visited[vertex] = true;
      std::vector<int> possible_path;
      TsmResult current_path;
      current_path.vertices.emplace_back(vertex);

      int cur = vertex;
      while (!(possible_path = GetPossiblePath(visited, cur)).empty()) {
        std::vector<double> probability = CreateProbability(possible_path, cur);
        int next_vertex = possible_path[ChooseVertex(probability)];
        int last_vertex = current_path.vertices.back();

        current_path.vertices.emplace_back(next_vertex);
        current_path.distance += graph[last_vertex][next_vertex];
        visited[next_vertex] = true;
        cur = next_vertex;
      }  // Закончился путь 1 муравья
      // Если путь найден то добавляем феромон на пути
      if (current_path.vertices.size() == graph.size() &&
          graph[current_path.vertices.back()][vertex]) {
        current_path.distance += graph[current_path.vertices.back()][vertex];
        current_path.vertices.emplace_back(vertex);
        if (result.vertices.empty() ||
            result.distance > current_path.distance) {
          result.vertices = current_path.vertices;
          result.distance = current_path.distance;
          i = 0;
        }
        UpdateLocalPheromon(local_pheromon, current_path.vertices,
                            current_path.distance);
      }
    }  // Все муравьи прошлись 1 раз
    UpdateGlobalPheromon(pheromon);
  }
  return result;
}

std::vector<int> Ant::GetPossiblePath(std::vector<bool> &visited, int vertex) {
  std::vector<int> possible_path;
  for (size_t i = 0; i < graph.size(); ++i) {
    if (graph[vertex][i] && !visited[i]) {
      possible_path.emplace_back(i);
    }
  }
  return possible_path;
}

std::vector<double> Ant::CreateProbability(std::vector<int> const &pp,
                                           int vertex) {
  std::vector<double> prob;
  double sum_wish = 0;
  for (size_t i = 0; i < pp.size(); ++i) {
    double wish =
        pow(pheromon[vertex][pp[i]], a) * pow(1.0 / graph[vertex][pp[i]], b);
    sum_wish += wish;
    prob.emplace_back(sum_wish);
  }

  for (size_t i = 0; i < prob.size(); ++i) {
    prob[i] /= sum_wish;
  }
  return prob;
}

int Ant::ChooseVertex(std::vector<double> &prob) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<double> dist(0, 1);
  double random_num = dist(gen);
  int left = 0, right = prob.size() - 1, vertex = 0;
  while (left <= right) {
    int mid = (left + right) / 2;
    if (random_num <= prob[mid]) {
      vertex = mid;
      right = mid - 1;
    } else {
      left = mid + 1;
    }
  }

  return vertex;
}

void Ant::UpdateLocalPheromon(std::vector<std::vector<double>> &p,
                              std::vector<int> &path, int distance) {
  for (size_t i = 1; i < path.size(); ++i) {
    p[path[i - 1]][path[i]] += kQ / distance;
  }
}
void Ant::UpdateGlobalPheromon(std::vector<std::vector<double>> &lp) {
  for (size_t i = 0; i < pheromon.size(); ++i) {
    for (size_t k = 0; k < pheromon[0].size(); ++k) {
      pheromon[i][k] = p * pheromon[i][k] + lp[i][k];
    }
  }
}
}  // end namespace s21
