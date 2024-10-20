#include "./controller.h"

namespace s21 {
Controller::Controller() : model_() {}
Controller::~Controller() {}

void Controller::LoadGraphFromFile(std::string filename) {
  model_.LoadGraphFromFile(filename);
}
void Controller::ExportGraphToDot(std::string filename) {
  model_.ExportGraphToDot(filename);
}

// algorithms
std::vector<int> Controller::DepthFirstSearch(int vertex) {
  return model_.DepthFirstSearch(vertex);
}
std::vector<int> Controller::BreadthFirstSearch(int vertex) {
  return model_.BreadthFirstSearch(vertex);
}

int Controller::GetShortestPathBetweenVertices(int vertex1, int vertex2) {
  return model_.GetShortestPathBetweenVertices(vertex1, vertex2);
}
std::vector<std::vector<int>> Controller::GetShortestPathsBetweenAllVertices() {
  return model_.GetShortestPathsBetweenAllVertices();
}
std::vector<std::vector<int>> Controller::GetLeastSpanningTree() {
  return model_.GetLeastSpanningTree();
}
TsmResult Controller::SolveTravelingSalesmanProblem() {
  return model_.SolveTravelingSalesmanProblem();
}
TsmResult Controller::SolveTravelingSalesmanProblemR() {
  return model_.SolveTravelingSalesmanProblemR();
}
TsmResult Controller::SolveTravelingSalesmanProblemB() {
  return model_.SolveTravelingSalesmanProblemB();
}

Graph& Controller::Get() { return model_.Get(); }
int Controller::GetCountVertex() { return model_.GetCountVertex(); }

}  // end namespace s21
