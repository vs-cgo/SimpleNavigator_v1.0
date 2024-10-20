#ifndef _SIMPLE_NAVIGATOR_MODEL_MODEL_H_
#define _SIMPLE_NAVIGATOR_MODEL_MODEL_H_

#include "../graph/graph.h"
#include "../graph_algorithms/graph_algorithms.h"

namespace s21 {
/**
 * @brief The Model class для хранения и манимуляции с графом.
 */
class Model {
 public:
  /**
   * @brief Model класс конструктор по умолчанию.
   */
  Model();
  ~Model();
  /**
   * @brief Get метод для получения текущего графа.
   * @return
   */
  Graph &Get();
  /**
   * @brief GetCountVertex метод для получения количество вершин.
   * @return
   */
  int GetCountVertex();
  /**
   * @brief LoadGraphFromFile метод для загрузки графа в формате матрицы
   * смежности.
   * @param[in] filename путь к файлу.
   */
  void LoadGraphFromFile(std::string &filename);
  /**
   * @brief ExportGraphToDot метод для сохранения графа в формате dot.
   * @param[in] filename путь к файлу.
   */
  void ExportGraphToDot(std::string &filename);
  /**
   * @brief DepthFirstSearch обход графа в глубину.
   * @param[in] vertex начальная вершина.
   * @return вектор с содержищий вершины в порядке обхода.
   */
  std::vector<int> DepthFirstSearch(int vertex);
  /**
   * @brief BreadthFirstSearch обходграфа в ширину.
   * @param[in] vertex начальная вершина.
   * @return вектор с содержащи вершины в порядке обхода.
   */
  std::vector<int> BreadthFirstSearch(int vertex);
  /**
   * @brief GetShortestPathBetweenVertices метод для нахождения кратчайего пути
   * между 2 вершинами(алгоритм дейкстра).
   * @param[in] vertex1 начало маршрута.
   * @param[in] vertex2 конец маршрута.
   * @return стоимость маршрута(длина, вероятность, стоимость и т.д.)
   */
  int GetShortestPathBetweenVertices(int vertex1, int vertex2);
  /**
   * @brief GetShortestPathsBetweenAllVertices метод для получения всех
   * возможных кратчайших путей.
   * @return матрица смежности с кратчайшими путями.
   */
  std::vector<std::vector<int>> GetShortestPathsBetweenAllVertices();
  /**
   * @brief GetLeastSpanningTree метод для получения минимального остовного
   * дерева.
   * @return матрица смежности с результатом.
   */
  std::vector<std::vector<int>> GetLeastSpanningTree();
  /**
   * @brief SolveTravelingSalesmanProblem нахождение гамильтонового цикла
   * методом муравьиного алгоритма.
   * @return вектор с найденным путем(или пустой вектор, если невозможно
   * решить).
   */
  TsmResult SolveTravelingSalesmanProblem();
  /**
   * @brief SolveTravelingSalesmanProblemR нахождение гамильтонового цикла
   * методом полной рекурсии.
   * @return вектор с найденным путем(пустой вектор, если путь не может быть
   * найден).
   */
  TsmResult SolveTravelingSalesmanProblemR();
  /**
   * @brief SolveTravelingSalesmanProblemB метод нахождение гамильтонового цикла
   * методом имитации отжига.
   * @return вектор с найденным путем(пустой вектор, если путь не может быть
   * найден).
   */
  TsmResult SolveTravelingSalesmanProblemB();

 private:
  Graph graph_;
};
};      // namespace s21
#endif  // _SIMPLE_NAVIGATOR_MODEL_MODEL_H_
