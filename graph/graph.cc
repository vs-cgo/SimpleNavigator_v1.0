#include "./graph.h"

namespace s21 {
Graph::Graph() : row_(0), col_(0), graph_() {}
Graph::~Graph() {}

void Graph::LoadGraphFromFile(std::string filename) {
  std::ifstream is(filename.c_str());
  if (!is.is_open()) {
    throw not_open();
  }

  int val = 0;
  if ((is >> val); val <= 0) {
    throw bad_file();
  }
  row_ = col_ = val;
  std::vector<std::vector<int>> temp(row_, std::vector<int>(col_, 0));
  for (int i = 0; i < row_; ++i) {
    for (int k = 0; k < col_; ++k) {
      if (is >> val; is.good() || (!is.fail() && is.eof())) {
        temp[i][k] = val;
      } else {
        is.close();
        throw bad_file();
      }
    }
  }
  is.close();
  graph_ = std::move(temp);
}

void Graph::ExportGraphToDot(std::string filename) {
  std::ofstream os(filename.c_str());
  if (!os.is_open()) {
    throw not_open();
  }
  int vertex = graph_.size();
  if (!vertex) {
    std::cout << "Graph is empty. Load graph from file" << std::endl;
    return;
  }

  bool digraph = IsDigraph();
  std::string dash = digraph ? " -> " : " -- ";

  os << (digraph ? "digraph" : "graph") << " V {" << std::endl;
  os << '\t' << "node [shape=circle, color=blue];" << std::endl;

  for (int i = 0; i < vertex; ++i) {
    os << '\t' << GetName(i) << ";" << std::endl;
  }

  for (int i = 0; i < vertex; ++i) {
    std::string name = GetName(i);
    for (int k = i; k < vertex; ++k) {
      if (graph_[i][k]) {
        os << '\t' << name << dash << GetName(k) << ";" << std::endl;
      }
    }
  }
  os << "}";
  os.close();
}

std::string Graph::GetName(int vertex) {
  std::string str;
  str += 'a' + vertex % 26;
  if (vertex >= 26) str += std::to_string(vertex / 26);
  return str;
}

bool Graph::IsDigraph() {
  for (std::size_t i = 0; i < graph_.size(); ++i) {
    for (std::size_t k = 0; k < graph_[0].size(); ++k) {
      if (graph_[i][k] != graph_[k][i]) return true;
    }
  }
  return false;
}

std::vector<int> Graph::Adjacency(int cur) {
  if (cur < 0 && cur >= row_) return {};

  std::vector<int> res;
  for (int i = 0; i < col_; ++i) {
    if (graph_[cur][i]) res.push_back(i);
  }
  return res;
}
std::vector<std::pair<int, int>> Graph::AdjacencyWeight(int cur) {
  if (cur < 0 && cur >= row_) return {};

  std::vector<std::pair<int, int>> res;
  for (int i = 0; i < col_; ++i) {
    if (graph_[cur][i] > 0) res.push_back({i, graph_[cur][i]});
  }
  return res;
}
// Get
int Graph::GetCountVertex() { return row_; }
std::vector<std::vector<int>> Graph::GetData() { return graph_; }

// Clear
void Graph::Clear() {
  row_ = col_ = 0;
  graph_.clear();
}
}  // end namespace s21
