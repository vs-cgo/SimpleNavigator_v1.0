#include "./view.h"

namespace s21 {

View::View() : controller_() {}
View::~View() {}

void View::Show() {
  Menu();
  int c = GetChoice();
  while (c != kExit) {
    if (c == kOpen) {
      controller_.LoadGraphFromFile(GetString());
    } else if (c == kExport) {
      controller_.ExportGraphToDot(GetString());
    } else if (c == kPrintDFS) {
      int vert = controller_.GetCountVertex();
      int start = GetNumber(vert);
      if (vert) PrintDFS(controller_.DepthFirstSearch(start), start);
    } else if (c == kPrintBFS) {
      int vert = controller_.GetCountVertex();
      int start = GetNumber(vert);
      if (vert) PrintBFS(controller_.BreadthFirstSearch(start), start);
    } else if (c == kPrintShortPath) {
      int vert = controller_.GetCountVertex();
      int start = GetNumber(vert), end = GetNumber(vert);
      if (vert)
        ShortPath(controller_.GetShortestPathBetweenVertices(start, end), start,
                  end);
    } else if (c == kPrintAllShortPath) {
      AllShortPath(controller_.GetShortestPathsBetweenAllVertices());
    } else if (c == kPrintMinSpanningTree) {
      SpanningTree(controller_.GetLeastSpanningTree());
    } else if (c == kTSP) {
      TravelingSalesmanProblem(controller_.SolveTravelingSalesmanProblem());
    } else if (c == kFullRecursion) {
      TravelingSalesmanProblem(controller_.SolveTravelingSalesmanProblemR());
    } else if (c == kBurn) {
      TravelingSalesmanProblem(controller_.SolveTravelingSalesmanProblemB());
    } else if (c == kCompareTSP) {
      CompareTSP();
    } else if (c == kPrintMatrix) {
      PrintAdjacencyMatrix(controller_.Get());
    }
    Menu();
    c = GetChoice();
  }
}

void View::Menu() {
  std::cout << "Menu: " << std::endl;
  std::cout << "1. Open graf" << std::endl;
  std::cout << "2. Export graf to dot" << std::endl;
  std::cout << "3. Print depth first search" << std::endl;
  std::cout << "4. Print breadth first search" << std::endl;
  std::cout << "5. Print shortest path between vertices" << std::endl;
  std::cout << "6. Print shortest path between all vertices" << std::endl;
  std::cout << "7. Print least spanning tree" << std::endl;
  std::cout << "8. Print solving traveling salesman`s problem" << std::endl;
  std::cout
      << "9. Print solving traveling salesman`s problem metod full recursion"
      << std::endl;
  std::cout << "10. Print solving traveling salesman`s problem metod burn"
            << std::endl;
  std::cout << "11. Print compare solving traveling salesman`s problem"
            << std::endl;
  std::cout << "12. PrintAdjacencyMatrix()" << std::endl;
  std::cout << "0. Exit" << std::endl;
}

void View::EmptyGraph() {
  std::cout << "Sorry, no graph. Load graph from file!" << std::endl;
}
void View::Print() { std::cout << "Metod::print" << std::endl; }

// Print DFS
void View::PrintDFS(std::vector<int> tv, int start) {
  if (tv.empty()) {
    std::cout << "Incorrect data" << std::endl;
  } else {
    std::cout << "Order depth first search from " << start << std::endl;
    PrintTraversedVertices(tv);
  }
}
// Print BFS
void View::PrintBFS(std::vector<int> tv, int start) {
  if (tv.empty()) {
    std::cout << "Incorrect data" << std::endl;
  } else {
    std::cout << "Order breadth first search from " << start << std::endl;
    PrintTraversedVertices(tv);
  }
}
// Print Dejkstra
void View::ShortPath(int path, int v1, int v2) {
  if (path < 0) {
    std::cout << "Incorrect data" << std::endl;
  } else {
    std::cout << "Shortest path between vertex " << v1 << " and vertex " << v2
              << " : " << path << std::endl;
  }
}
// Print Floyd-Warshall
void View::AllShortPath(std::vector<std::vector<int>> matrix) {
  std::cout << "All shortest path between vertices: " << std::endl;
  for (auto &v : matrix) {
    PrintVector(v);
  }
  std::cout << std::endl;
}
// Print Spanning Tree
void View::SpanningTree(std::vector<std::vector<int>> matrix) {
  std::cout << "Minimum spanning tree: " << std::endl;
  for (auto &v : matrix) {
    PrintVector(v);
  }
  std::cout << std::endl;
}
// Print TSP
void View::TravelingSalesmanProblem(TsmResult tsm) {
  if (!controller_.GetCountVertex()) {
    EmptyGraph();
  } else if (tsm.vertices.empty()) {
    std::cout << "it is impossible to solve the problem with a given graph"
              << std::endl;
  } else {
    std::cout << "Path is:" << std::endl;
    PrintTraversedVertices(tsm.vertices);
    std::cout << "distance: " << tsm.distance << std::endl;
  }
}
// Compare TSP
void View::CompareTSP() {
  int vertex = controller_.GetCountVertex();
  if (!vertex) {
    EmptyGraph();
    return;
  }

  std::cout << "Enter the number of repetition: ";
  int count = GetNumber(1000000000);
  // int dist = controller_.SolveTravelingSalesmanProblemR().distance;
  // std::cout << "Minimum path is: " << dist << std::endl;

  {
    double x = 0;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < count; ++i) {
      x += (controller_.SolveTravelingSalesmanProblem()).distance;
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Ant colony algorithm: " << duration.count()
              << " ref: " << x / 1000 << std::endl;
  }
  {
    double x = 0;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < count; ++i) {
      x += controller_.SolveTravelingSalesmanProblemR().distance;
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Full recursion algorithm: " << duration.count()
              << " ref: " << x / 1000 << std::endl;
  }
  {
    double x = 0;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < count; ++i) {
      x += (controller_.SolveTravelingSalesmanProblemB()).distance;
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Burn imitation metod: " << duration.count()
              << " ref: " << x / 1000 << std::endl;
  }
}
void View::PrintVector(std::vector<int> &v) {
  for (size_t i = 0; i < v.size(); ++i) {
    std::cout << v[i] << ' ';
  }
  std::cout << std::endl;
}
// just print vector
void View::PrintTraversedVertices(std::vector<int> &tv) {
  for (size_t i = 0, len = tv.size(); i < len; ++i) {
    std::cout << tv[i] + 1 << (i < len - 1 ? "-" : "");
  }
  std::cout << std::endl;
}
// for delete
void View::GetShortestPathBetweenVertices(Graph &graph, int v1, int v2) {
  GraphAlgorithms a;
  int r = a.GetShortestPathBetweenVertices(graph, v1 - 1, v2 - 1);
  std::cout << "Shortest path betwen " << v1 << " and " << v2 << " is: " << r
            << std::endl;
}
// just print adjacency matrix
void View::PrintAdjacencyMatrix(Graph &graph) {
  int vertex = graph.GetCountVertex();
  if (!vertex) {
    std::cout << "-> Graph is empty! Load graph from file" << std::endl;
    return;
  }
  std::vector<std::vector<int>> temp = graph.GetData();
  for (int i = 0; i < vertex; ++i) {
    for (int k = 0; k < vertex; ++k) {
      std::cout << temp[i][k] << ' ';
    }
    std::cout << std::endl;
  }
}
// get choice принимать ли первую цифру дробного числа или же откидывать?
int View::GetChoice() {
  std::cout << "Enter your choice: ";
  int res = 0;
  while ((std::cin >> res).good() == false || (res < 0 || res > 12)) {
    std::cout << "Incorrect input> Please, enter number beetwen 0-10: ";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  return res;
}

// get number
int View::GetNumber(int vert) {
  int in = 0;
  if (!vert) {
    EmptyGraph();
    return 0;
  }
  std::cout << "Please, enter vertex beetwen 1-" << vert << " : ";
  while ((std::cin >> in).good() == false || (in <= 0 || in > vert)) {
    std::cout << "Incorrect input. Please, enter vertex beetwen 1-" << vert
              << " : ";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  return in;
}
// get string
std::string View::GetString() {
  std::cout << "Enter path to file with graph: ";
  std::string str;
  std::cin >> str;
  return str;
}
}  // end namespace s21
