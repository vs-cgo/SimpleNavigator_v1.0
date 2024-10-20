#ifndef _MODEL_GRAPH_ALGORITHMS_TSM_TSM_RESULT_H_
#define _MODEL_GRAPH_ALGORITHMS_TSM_TSM_RESULT_H_

#include <vector>

namespace s21 {
/**
 * @brief The TsmResult struct для хранения пути и расстояния.
 */
struct TsmResult {
  /**
   * @brief vertices путь(последовательность вершин, которые надо посетить).
   */
  std::vector<int> vertices;
  /**
   * @brief distance дистанция пути.
   */
  double distance = 0;
};
}  // end namespace s21
#endif  // _MODEL_GRAPH_ALGORITHMS_TSM_TSM_RESULT_H_
