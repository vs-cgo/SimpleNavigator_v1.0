#include "./model.h"

namespace s21 {
Model::Model() : graph_() {}
Model::~Model() {}
// algorithms

Graph &Model::Get() { return graph_; }
int Model::GetCountVertex() { return graph_.GetCountVertex(); }

void Model::LoadGraphFromFile(std::string &filename) {
  try {
    graph_.LoadGraphFromFile(filename);
  } catch (not_open) {
    std::cout << "File wasn`t opened" << std::endl;
  } catch (bad_file) {
    std::cout << "File format is bad" << std::endl;
    graph_.Clear();
  }
}

void Model::ExportGraphToDot(std::string &filename) {
  try {
    graph_.ExportGraphToDot(filename);
  } catch (not_open) {
    std::cout << "File wasn`t opened" << std::endl;
  }
}
// task
std::vector<int> Model::DepthFirstSearch(int vertex) {
  GraphAlgorithms a;
  return a.DepthFirstSearch(graph_, vertex - 1);
}

std::vector<int> Model::BreadthFirstSearch(int vertex) {
  GraphAlgorithms a;
  return a.BreadthFirstSearch(graph_, vertex - 1);
}
int Model::GetShortestPathBetweenVertices(int vertex1, int vertex2) {
  GraphAlgorithms a;
  return a.GetShortestPathBetweenVertices(graph_, vertex1 - 1, vertex2 - 1);
}
std::vector<std::vector<int>> Model::GetShortestPathsBetweenAllVertices() {
  GraphAlgorithms a;
  return a.GetShortestPathsBetweenAllVertices(graph_);
}

std::vector<std::vector<int>> Model::GetLeastSpanningTree() {
  GraphAlgorithms a;
  return a.GetLeastSpanningTree(graph_);
}

TsmResult Model::SolveTravelingSalesmanProblem() {
  GraphAlgorithms a;
  return a.SolveTravelingSalesmanProblem(graph_);
}
TsmResult Model::SolveTravelingSalesmanProblemR() {
  GraphAlgorithms a;
  return a.SolveTravelingSalesmanProblemR(graph_);
}
TsmResult Model::SolveTravelingSalesmanProblemB() {
  GraphAlgorithms a;
  return a.SolveTravelingSalesmanProblemB(graph_);
}
}  // end namespace s21
