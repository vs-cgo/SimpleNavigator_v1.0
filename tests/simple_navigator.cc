#include "simple_navigator.h"

namespace s21 {
TEST_F(SimpleNavigatorTest, NoFile) {
  controller_.LoadGraphFromFile("example/NoFile.txt");
  EXPECT_EQ(controller_.GetCountVertex(), 0);
}
TEST_F(SimpleNavigatorTest, BadFile) {
  controller_.LoadGraphFromFile(bad_file);
  EXPECT_EQ(controller_.GetCountVertex(), 0);
}
TEST_F(SimpleNavigatorTest, BadFile2) {
  controller_.LoadGraphFromFile("example/graph_example_bad_2.txt");
  EXPECT_EQ(controller_.GetCountVertex(), 0);
}
TEST_F(SimpleNavigatorTest, Open) {
  controller_.LoadGraphFromFile(example2);
  std::vector<std::vector<int>> cur = controller_.Get().GetData();
  int arr[9][9] = {{0, 4, 0, 0, 0, 0, 0, 8, 0},  {4, 0, 8, 0, 0, 0, 0, 11, 0},
                   {0, 8, 0, 7, 0, 4, 0, 0, 2},  {0, 0, 7, 0, 9, 14, 0, 0, 0},
                   {0, 0, 0, 9, 0, 10, 0, 0, 0}, {0, 0, 4, 14, 10, 0, 2, 0, 0},
                   {0, 0, 0, 0, 0, 2, 0, 1, 6},  {8, 11, 0, 0, 0, 0, 1, 0, 7},
                   {0, 0, 2, 0, 0, 0, 6, 7, 0}};
  for (std::size_t i = 0; i < cur.size(); ++i) {
    for (std::size_t k = 0; k < cur[0].size(); ++k) {
      EXPECT_EQ(cur[i][k], arr[i][k]);
    }
  }
}
TEST_F(SimpleNavigatorTest, Open2) {
  controller_.LoadGraphFromFile(example4);
  std::vector<std::vector<int>> cur = controller_.Get().GetData();
  int arr[6][6] = {{0, 7, 9, 0, 0, 14},  {7, 0, 10, 15, 0, 0},
                   {9, 10, 0, 11, 0, 2}, {0, 15, 11, 0, 6, 0},
                   {0, 0, 0, 6, 0, 9},   {14, 0, 2, 0, 9, 0}};
  for (std::size_t i = 0; i < cur.size(); ++i) {
    for (std::size_t k = 0; k < cur[0].size(); ++k) {
      EXPECT_EQ(cur[i][k], arr[i][k]);
    }
  }
}
TEST_F(SimpleNavigatorTest, Export) {
  controller_.LoadGraphFromFile(example4);
  controller_.ExportGraphToDot("./test.dot");
}
TEST_F(SimpleNavigatorTest, Export2) {
  controller_.ExportGraphToDot("./test.dot");
}
TEST_F(SimpleNavigatorTest, DFS) {
  controller_.LoadGraphFromFile(example2);
  std::vector<int> ans = controller_.DepthFirstSearch(7);
  std::vector<int> res = {6, 5, 2, 1, 0, 7, 8, 3, 4};
  for (std::size_t i = 0; i < ans.size(); ++i) {
    EXPECT_EQ(ans[i], res[i]);
  }
}
TEST_F(SimpleNavigatorTest, DFS2) {
  controller_.LoadGraphFromFile(example3);
  std::vector<int> ans = controller_.DepthFirstSearch(3);
  std::vector<int> res = {2, 4, 0, 8, 10, 11, 6, 5, 1, 3, 9, 7};
  for (std::size_t i = 0; i < ans.size(); ++i) {
    EXPECT_EQ(ans[i], res[i]);
  }
}
TEST_F(SimpleNavigatorTest, DFS3) {
  controller_.LoadGraphFromFile(example6);
  std::vector<int> ans = controller_.DepthFirstSearch(8);
  std::vector<int> res = {7, 0, 1, 2, 3, 4, 5, 8, 9, 6};
  for (std::size_t i = 0; i < ans.size(); ++i) {
    EXPECT_EQ(ans[i], res[i]);
  }
}
TEST_F(SimpleNavigatorTest, BFS) {
  controller_.LoadGraphFromFile(example4);
  std::vector<int> ans = controller_.BreadthFirstSearch(3);
  std::vector<int> res = {2, 0, 1, 3, 5, 4};
  for (std::size_t i = 0; i < ans.size(); ++i) {
    EXPECT_EQ(ans[i], res[i]);
  }
}
TEST_F(SimpleNavigatorTest, BFS2) {
  controller_.LoadGraphFromFile(example5);
  std::vector<int> ans = controller_.BreadthFirstSearch(10);
  std::vector<int> res = {9, 3, 6, 7, 8, 0, 2, 4, 5, 1};
  for (std::size_t i = 0; i < ans.size(); ++i) {
    EXPECT_EQ(ans[i], res[i]);
  }
}
TEST_F(SimpleNavigatorTest, BFS3) {
  controller_.LoadGraphFromFile(example6);
  std::vector<int> ans = controller_.BreadthFirstSearch(5);
  std::vector<int> res = {4, 0, 1, 3, 5, 8, 7, 2, 6, 9};
  for (std::size_t i = 0; i < ans.size(); ++i) {
    EXPECT_EQ(ans[i], res[i]);
  }
}
TEST_F(SimpleNavigatorTest, ShortestPath) {
  controller_.LoadGraphFromFile(example6);
  int ans = controller_.GetShortestPathBetweenVertices(1, 10);
  int exp = 16;
  EXPECT_EQ(ans, exp);
}
TEST_F(SimpleNavigatorTest, ShortestPath2) {
  controller_.LoadGraphFromFile(example6);
  int ans = controller_.GetShortestPathBetweenVertices(2, 9);
  int exp = 9;
  EXPECT_EQ(ans, exp);
}
TEST_F(SimpleNavigatorTest, ShortestPath3) {
  controller_.LoadGraphFromFile(example7);
  int ans = controller_.GetShortestPathBetweenVertices(2, 18);
  int exp = 33;
  EXPECT_EQ(ans, exp);
}
TEST_F(SimpleNavigatorTest, ShortestPath4) {
  controller_.LoadGraphFromFile(example7);
  int ans = controller_.GetShortestPathBetweenVertices(2, 21);
  int exp = -1;
  EXPECT_EQ(ans, exp);
}
TEST_F(SimpleNavigatorTest, AllShortestPath) {
  controller_.LoadGraphFromFile(example4);
  std::vector<std::vector<int>> ans =
      controller_.GetShortestPathsBetweenAllVertices();
  std::vector<std::vector<int>> res = {
      {0, 7, 9, 20, 20, 11},  {7, 0, 10, 15, 21, 12}, {9, 10, 0, 11, 11, 2},
      {20, 15, 11, 0, 6, 13}, {20, 21, 11, 6, 0, 9},  {11, 12, 2, 13, 9, 0}};
  for (std::size_t i = 0; i < ans.size(); ++i) {
    for (std::size_t k = 0; k < ans[0].size(); ++k) {
      EXPECT_EQ(ans[i][k], res[i][k]);
    }
  }
}
TEST_F(SimpleNavigatorTest, AllShortestPath2) {
  controller_.LoadGraphFromFile(example8);
  std::vector<std::vector<int>> ans =
      controller_.GetShortestPathsBetweenAllVertices();
  std::vector<std::vector<int>> res = {
      {0, 46, 18, 23, 50, 35, 54, 27, 28, 25, 29, 33},
      {46, 0, 28, 27, 41, 37, 18, 19, 47, 21, 17, 37},
      {18, 28, 0, 41, 32, 53, 44, 9, 37, 7, 11, 46},
      {23, 27, 41, 0, 28, 12, 35, 41, 24, 43, 43, 10},
      {50, 41, 32, 28, 0, 40, 59, 26, 44, 28, 24, 30},
      {35, 37, 53, 12, 40, 0, 47, 49, 21, 51, 51, 22},
      {54, 18, 44, 35, 59, 47, 0, 37, 35, 37, 35, 45},
      {27, 19, 9, 41, 26, 49, 37, 0, 28, 2, 2, 41},
      {28, 47, 37, 24, 44, 21, 35, 28, 0, 30, 30, 14},
      {25, 21, 7, 43, 28, 51, 37, 2, 30, 0, 4, 39},
      {29, 17, 11, 43, 24, 51, 35, 2, 30, 4, 0, 43},
      {33, 37, 46, 10, 30, 22, 45, 41, 14, 39, 43, 0}};
  for (std::size_t i = 0; i < ans.size(); ++i) {
    for (std::size_t k = 0; k < ans[0].size(); ++k) {
      EXPECT_EQ(ans[i][k], res[i][k]);
    }
  }
}

TEST_F(SimpleNavigatorTest, LeastSpanningTree) {
  controller_.LoadGraphFromFile(example7);
  std::vector<std::vector<int>> ans = controller_.GetLeastSpanningTree();
  int row = ans.size(), col = ans[0].size();
  EXPECT_EQ(row, 20);
  EXPECT_EQ(col, 20);
}
TEST_F(SimpleNavigatorTest, TSP_Ant) {
  controller_.LoadGraphFromFile(example4);
  TsmResult ans = controller_.SolveTravelingSalesmanProblem();
  TsmResult exp = controller_.SolveTravelingSalesmanProblemR();
  double expect = exp.distance * 1.1, result = ans.distance;
  EXPECT_LE(result, expect);
}

TEST_F(SimpleNavigatorTest, TSP_Ant2) {
  controller_.LoadGraphFromFile(example1);
  TsmResult ans = controller_.SolveTravelingSalesmanProblem();
  double expect = 253 * 1.1, result = ans.distance;
  EXPECT_LE(result, expect);
}
TEST_F(SimpleNavigatorTest, TSP_Ant3) {
  controller_.LoadGraphFromFile(example8);
  TsmResult ans = controller_.SolveTravelingSalesmanProblem();
  double expect = 219 * 1.1, result = ans.distance;
  EXPECT_LE(result, expect);
}
TEST_F(SimpleNavigatorTest, TSP_Burn) {
  controller_.LoadGraphFromFile(example1);
  TsmResult ans = controller_.SolveTravelingSalesmanProblemB();
  double expect = 253 * 1.1, result = ans.distance;
  EXPECT_LE(result, expect);
}
TEST_F(SimpleNavigatorTest, TSP_Burn2) {
  controller_.LoadGraphFromFile(example8);
  TsmResult ans = controller_.SolveTravelingSalesmanProblemB();
  double expect = 219 * 1.5, result = ans.distance;
  EXPECT_LE(result, expect);
}

}  // end namespace s21

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
