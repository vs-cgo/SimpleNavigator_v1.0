#ifndef _SIMPLE_NAVIGATOR_GRAPH_ALGORITHMS_ANT_ANT_H_
#define _SIMPLE_NAVIGATOR_GRAPH_ALGORITHMS_ANT_ANT_H_

#include <cmath>
#include <iostream>
#include <random>
#include <vector>

#include "../tsm/tsm_result.h"

namespace s21 {
/**
 * @brief The Ant class для реализации муравьиного алгоритма.
 */
class Ant {
 public:
  /**
   * @brief Ant конструктор по умолчанию.
   * @param[in] g граф в виде матрицы смежности.
   */
  Ant(std::vector<std::vector<int>> g);
  ~Ant();
  /**
   * @brief Solve метод для нахождения кратчайшего(приблизительно)
   * гамильтонового цикла в графе.
   * @return структура содержащая путь и дистанцию.
   */
  TsmResult Solve();

 private:
  std::vector<int> GetPossiblePath(std::vector<bool> &visited, int vertex);
  std::vector<double> CreateProbability(std::vector<int> const &pp, int vertex);
  int ChooseVertex(std::vector<double> &probility);
  void UpdateLocalPheromon(std::vector<std::vector<double>> &p,
                           std::vector<int> &path, int distance);
  void UpdateGlobalPheromon(std::vector<std::vector<double>> &lp);

 private:
  double a, b, kQ, p;
  std::vector<std::vector<int>> graph;
  std::vector<std::vector<double>> pheromon;
};

}  // end namespace s21
#endif  // _SIMPLE_NAVIGATOR_GRAPH_ALGORITHMS_ANT_ANT_H_
