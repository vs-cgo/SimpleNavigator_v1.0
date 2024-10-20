#ifndef _SIMPLE_NAVIGATOR_CONTROLLER_CONTROLLER_H_
#define _SIMPLE_NAVIGATOR_CONTROLLER_CONTROLLER_H_

#include "../model/model.h"

namespace s21 {
/**
 * @brief The Controller class для связывание вью и модели.
 */
class Controller {
 public:
  /**
   * @brief Controller конструктор по умолчанию.
   */
  Controller();
  ~Controller();
  /**
   * @brief LoadGraphFromFile передача в модель запроса на открытие графа.
   * @param[in] filename путь к файлу.
   */
  void LoadGraphFromFile(std::string filename);
  /**
   * @brief ExportGraphToDot передача запроса на сохранение графв.
   * @param[in] filename путь к файлу.
   */
  void ExportGraphToDot(std::string filename);
  /**
   * @brief DepthFirstSearch запрос на обход в глубину.
   * @param[in] vertex стартовая вершина.
   * @return возврат пути.
   */
  std::vector<int> DepthFirstSearch(int vertex);
  /**
   * @brief BreadthFirstSearch запрос на обход в ширину.
   * @param[in] vertex стартовая вершина.
   * @return возврат пути.
   */
  std::vector<int> BreadthFirstSearch(int vertex);
  /**
   * @brief GetShortestPathBetweenVertices запрос на вычисление кратчайшего
   * пути.
   * @param[in] vertex1 стартовая вершина.
   * @param[in] vertex2 конечная вершина.
   * @return длина(стоиость, возможность и т.д.) найденного пути.
   */
  int GetShortestPathBetweenVertices(int vertex1, int vertex2);
  /**
   * @brief GetShortestPathsBetweenAllVertices запрос на вычисление всех
   * кратчайших путей.
   * @return матриица смежности с результатом.
   */
  std::vector<std::vector<int>> GetShortestPathsBetweenAllVertices();
  /**
   * @brief GetLeastSpanningTree запрос на нахождение минимального остового
   * дерева.
   * @return результат в вие матрицы смежности.
   */
  std::vector<std::vector<int>> GetLeastSpanningTree();
  /**
   * @brief SolveTravelingSalesmanProblem запрос на нахождение гамильтонового
   * цикла методом муравьиного алгоритма.
   * @return структуру содержащую путь и длину.
   */
  TsmResult SolveTravelingSalesmanProblem();
  /**
   * @brief SolveTravelingSalesmanProblemR запрос на нахождение гамильтонового
   * цикла методом полной рекурсии.
   * @return структуру содержащую путь и длину.
   */
  TsmResult SolveTravelingSalesmanProblemR();
  /**
   * @brief SolveTravelingSalesmanProblemB запрос на нахождение гамильтонового
   * цикла методом имитации отжига.
   * @return структуру содержащую путь и длину.
   */
  TsmResult SolveTravelingSalesmanProblemB();
  /**
   * @brief Get запрос текущего графа.
   * @return граф.
   */
  Graph& Get();
  /**
   * @brief GetCountVertex запрос на количество вершин в графе.
   * @return количество вершин.
   */
  int GetCountVertex();

 private:
  Model model_;
};
}  // end namespace s21

#endif  // _SIMPLE_NAVIGATOR_CONTROLLER_CONTROLLER_H_
