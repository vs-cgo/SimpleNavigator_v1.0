#ifndef _SIMPLE_NAVIGATOR_TEST_SIMPLE_NAVIGATOR_TEST_H_
#define _SIMPLE_NAVIGATOR_TEST_SIMPLE_NAVIGATOR_TEST_H_

#include <gtest/gtest.h>

#include <iostream>
#include <string>

#include "../controller/controller.h"
#include "../model/model.h"

namespace s21 {
class SimpleNavigatorTest : public testing::Test {
 protected:
  SimpleNavigatorTest()
      : controller_(),
        example1("example/graph_example_1.txt"),
        example2("example/graph_example_2.txt"),
        example3("example/graph_example_3.txt"),
        example4("example/graph_example_4.txt"),
        example5("example/graph_example_5.txt"),
        example6("example/graph_example_6.txt"),
        example7("example/graph_example_7.txt"),
        example8("example/graph_example_8.txt"),
        bad_file("example/graph_example_bad.txt"){};
  ~SimpleNavigatorTest(){};

  void TearDown() override{};
  void SetUp() override{};
  Controller controller_;
  std::string example1, example2, example3, example4, example5;
  std::string example6, example7, example8, bad_file;
};

}  // end namespace s21
#endif  // _SIMPLE_NAVIGATOR_TEST_SIMPLE_NAVIGATOR_TEST_H_
