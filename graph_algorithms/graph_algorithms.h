#ifndef _SIMPLE_NAVIGATOR_GRAPH_ALGORITHMS_GRAPH_ALGORITHMS_H_
#define _SIMPLE_NAVIGATOR_GRAPH_ALGORITHMS_GRAPH_ALGORITHMS_H_

#include <algorithm>
#include <climits>
#include <queue>
#include <unordered_set>
#include <vector>

#include "../container/s21_queue.h"
#include "../container/s21_stack.h"
#include "../graph/graph.h"
#include "ant/ant.h"
#include "tsm/tsm_result.h"

namespace s21 {
/**
 * @brief The GraphAlgorithms class алгоритмы для решения чатси вычислений над
 * графом.
 */
class GraphAlgorithms {
 public:
  /**
   * @brief GraphAlgorithms конструктор по умолчанию.
   */
  GraphAlgorithms();
  ~GraphAlgorithms();
  /**
   * @brief DepthFirstSearch обход графа в глубину.
   * @param[in] graph данный граф.
   * @param[in] start_vertex начальная вершина.
   * @return вектор с путем в порядке обхода.
   */
  std::vector<int> DepthFirstSearch(Graph &graph, int start_vertex);
  /**
   * @brief BreadthFirstSearch обход графа в ширину.
   * @param[in] graph граф над которым требуется вычисления.
   * @param[in] start_vertex начальная вершина.
   * @return вектор с путем в порядке обхода.
   */
  std::vector<int> BreadthFirstSearch(Graph &graph, int start_vertex);
  /**
   * @brief GetShortestPathBetweenVertices нахождение кратчайшего пути между 2
   * вершинами.
   * @param[in] graph граф над которым надо произвести вычисления.
   * @param[in] vertex1 начальная вершина.
   * @param[in] vertex2 конечная вершина.
   * @return дистанция(-1 если путь не может быть найден).
   */
  int GetShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2);
  /**
   * @brief GetShortestPathsBetweenAllVertices кратчайшие пути пужду всеми
   * вершинами.
   * @param[in] graph текущий граф.
   * @return матрица смежности с возможными кратчайшими путями.
   */
  std::vector<std::vector<int>> GetShortestPathsBetweenAllVertices(
      Graph &graph);
  /**
   * @brief GetLeastSpanningTree нахождение минимального остового дерева.
   * @param[in] graph граф над которым требуется ычисления.
   * @return матрица смежности с вариантом минимального остового дерева.
   */
  std::vector<std::vector<int>> GetLeastSpanningTree(Graph &graph);
  /**
   * @brief SolveTravelingSalesmanProblem нахождение минимального гамильтонового
   * цикла методом муравьиного алгоритма.
   * @param[in] graph граф над которым производятся вычисления.
   * @return структура содержащая путь и дистанцию(путь пустой вектор если найти
   * невозможно).
   */
  TsmResult SolveTravelingSalesmanProblem(Graph &graph);
  /**
   * @brief SolveTravelingSalesmanProblemR нахождение минимального
   * гамильтонового цикла методом полной рекурсии.
   * @param[in] graph граф над которым производятся вычисления.
   * @return структура содержащая путь и дистанцию(путь пустой вектор если найти
   * невозможно).
   */
  TsmResult SolveTravelingSalesmanProblemR(Graph &graph);
  /**
   * @brief SolveTravelingSalesmanProblemB нахождение минимального
   * гамильтонового цикла методом имитации отжига.
   * @param[in] graph граф над которым производятся вычисления.
   * @return структура содержащая путь и дистанцию(путь пустой вектор если найти
   * невозможно).
   */
  TsmResult SolveTravelingSalesmanProblemB(Graph &graph);

 private:
  void Recur(std::vector<std::vector<int>> &graph, std::vector<bool> &visited,
             TsmResult &res, TsmResult &temp, int vertex, int all_vertex);
  TsmResult InitState(std::vector<std::vector<int>> graph);
  bool FindAnyPath(std::vector<bool> &visited, TsmResult &path,
                   std::vector<std::vector<int>> &graph);
  int Calculate(std::vector<int> &p, std::vector<std::vector<int>> &g);
};
}  // end namespace s21
#endif  // _SIMPLE_NAVIGATOR_GRAPH_ALGORITHMS_GRAPH_ALGORITHMS_H_
