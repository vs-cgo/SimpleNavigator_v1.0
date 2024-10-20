#ifndef _SIMPLE_NAVIGATOR_MODEL_GRAPH_GRAPH_H_
#define _SIMPLE_NAVIGATOR_MODEL_GRAPH_GRAPH_H_

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace s21 {
/**
 * @brief The not_open struct выбрасывается при невозможности открыть файл
 */
struct not_open {};
/**
 * @brief The bad_file struct выбрасывается при некорректном файле
 */
struct bad_file {};
/**
 * @brief The Graph class класс для октрытия, сохранения и хранения графа.
 */
class Graph {
 public:
  /**
   * @brief Graph конструктор по умолчанию.
   */
  Graph();
  ~Graph();
  /**
   * @brief LoadGraphFromFile метод для загрузки графа.
   * @param filename путь к файлу.
   */
  void LoadGraphFromFile(std::string filename);
  /**
   * @brief ExportGraphToDot метод для сохранения графа в формате dot.
   * @param[in] filename путь к файлу
   */
  void ExportGraphToDot(std::string filename);
  /**
   * @brief Adjacency метод для получения соседей текущей вершины.
   * @param[in] cur текущая вершина.
   * @return векторо с возможными соседями.
   */
  std::vector<int> Adjacency(int cur);
  /**
   * @brief AdjacencyWeight метод для получения соседей и веса ребра.
   * @param[in] cur текущая вершина.
   * @return вектор пар с соседом и весом ребра до этого соседа.
   */
  std::vector<std::pair<int, int>> AdjacencyWeight(int cur);
  /**
   * @brief GetCountVertex метод для получения количесво вершин.
   * @return количество вершин.
   */
  int GetCountVertex();
  /**
   * @brief GetData метод для получения матрицы смежности.
   * @return сатрица смежности.
   */
  std::vector<std::vector<int>> GetData();
  /**
   * @brief Clear сетод для очистки графа.
   */
  void Clear();

 private:
  bool IsDigraph();
  std::string GetName(int vertex);

 private:
  int row_;
  int col_;
  std::vector<std::vector<int>> graph_;
};

}  // end namespace s21
#endif  // _SIMPLE_NAVIGATOR_MODEL_GRAPH_GRAPH_H_
