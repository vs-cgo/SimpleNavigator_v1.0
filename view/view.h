#ifndef _SIMPLE_NAVIGATOR_VIEW_VIEW_H_
#define _SIMPLE_NAVIGATOR_VIEW_VIEW_H_

#include <chrono>
#include <limits>

#include "../controller/controller.h"
#include "../graph_algorithms/graph_algorithms.h"

/**
 *\namespace s21 пространство имен в котором работают данные классы
 */
namespace s21 {
/*!
 * \enum The Choice enum выбор действия с графом
 */
enum Choice {
  kOpen = 1, /*!< открыть файл */
  kExport,   /*!< сохранить граф в формате DOT */
  kPrintDFS, /*!< обход графа в глубину и распечатка всех путей */
  kPrintBFS, /*!< обход графа в ширину и распечатка всех путей */
  kPrintShortPath, /*!< нахождение кратчайшего пути между 2 точками */
  kPrintAllShortPath, /*!< нахождение всех кратчайших путей */
  kPrintMinSpanningTree, /*!< нахождения минимального остового дерева */
  kTSP, /*!< нахождение гамильтонового цикла методом муравьиного алгоритма */
  kFullRecursion, /*!< нахождение гамильтонового цикла методом полной рекурсии
                   */
  kBurn, /*!< нахождение гамильтонового цикла методом имитации отжига */
  kCompareTSP, /*!< сравнение решения задачи коммивояжера 3 методами */
  kPrintMatrix, /*!< распечатка текущего графа */
  kExit = 0     /*!< выход из программы */
};
/**
 * @brief The View class для отображения результатов вычмсления над графом
 */
class View {
 public:
  /**
   * @brief View конструктор по умолчанию.
   */
  View();
  ~View();
  /**
   * @brief Show запуск начала программы.
   */
  void Show();

 private:
  void Menu();
  void EmptyGraph();
  void GetShortestPathBetweenVertices(Graph &graph, int v1, int v2);

  // Print
  void Print();
  void PrintDFS(std::vector<int> tv, int start);
  void PrintBFS(std::vector<int> tv, int start);
  void ShortPath(int path, int start, int end);
  void AllShortPath(std::vector<std::vector<int>> matrix);
  void SpanningTree(std::vector<std::vector<int>> matrix);
  void TravelingSalesmanProblem(TsmResult res);
  void CompareTSP();

  void PrintVector(std::vector<int> &v);
  void PrintTraversedVertices(std::vector<int> &tv);
  void PrintAdjacencyMatrix(Graph &graph);
  // temp
  // void PrintTraversedVertices2(std::vector<int> &tv);
  // get number
  int GetChoice();
  int GetNumber(int vert);
  std::string GetString();

 private:
  Controller controller_;
};
}  // namespace s21
#endif  // _SIMPLE_NAVIGATOR_VIEW_VIEW_H_
