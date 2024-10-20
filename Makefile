CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++17 -g
GRAPHLIB := s21_graph s21_graph_algorithms
PROJECT := SimpleNavigator
PROJECT_DIR := ${PROJECT}/
TEST_DIR := tests

MODEL := $(shell find model -type f -name "*.cc") 
CONTROLLER := $(shell find controller -type f -name "*.cc")
VIEW := $(shell find view -type f -name "*.cc")
GRAPH := $(shell find graph -type f -name "*.cc")
GRAPH_ALG := $(shell find graph_algorithms -type f -name "*.cc")
SRC := ${MODEL} ${CONTROLLER} ${VIEW} main.cc
OBJ := $(patsubst %.cc, %.o, ${SRC})
SRC_TEST := $(shell find ${TEST_DIR} -type f -name "*.cc") ${MODEL} $(CONTROLLER)
OBJ_TEST := $(patsubst %.cc, %.o, ${SRC_TEST})
GCOV := ${MODEL} ${CONTROLLER} ${GRAPH} ${GRAPH_ALG} $(shell find ${TEST_DIR} -type f -name "*.cc")
GCOV_OBJ := $(patsubst %.cc, %.o, ${GCOV})
TAR = $(shell find .  -type f -name "*.cc" -o -name "*.h") 


LDFLAGS= -lgtest -lgmock
NAME := $(shell uname -s)
ifeq (${NAME}, Linux) 
		LDFLAGS = ${LDFLAGS} -lpthread
endif

.PHONY: all clean test build

all: clean install
e:
		@echo ${SRC}
start: ${OBJ} ${GRAPHLIB}
		${CXX} $^ -L. ${GRAPHLIB} -o $@
		./start
s21_graph: graph/graph.o
		ar rcs $@ $?
s21_graph_algorithms: $(patsubst %.cc, %.o, ${GRAPH_ALG})
		ar rcs $@ $?
install: clean start
		@-mkdir ../../${PROJECT}
		cp -r start ../../${PROJECT}/SimpleNavigator
uninstall:
		rm -rf ../../${PROJECT}
clean:
		@rm -rf $(shell find ./ -type f -name "*.o") tests/*.o ${GRAPHLIB} 
		@rm -rf test build latex/ html/ report start test.dot
		@rm -rf $(shell find ./ -type f -name "*.gcda" -o -name "*.gcno")
		@rm -rf tests/*.gcda tests/*.gcno test.info 
dvi: 
		-doxygen Doxyfile - w html
		open html/index.html
dviclean:
		rm -rf html/ latex/
		
dist:	
		@tar cvf ../../${PROJECT}.tar ${TAR} Makefile ./description.h ./Doxyfile
dist2: clean start
		@tar cvf ../../${PROJECT}.tar start
distclean:
		rm -rf ../../${PROJECT}.tar
			
test: ${OBJ_TEST}  ${GRAPHLIB}
		${CXX} $^ ${LDFLAGS} -L. ${GRAPHLIB} -o $@
		./test
%.o: %.cc %.h
		${CXX} ${CXXFLAGS} -c ${filter-out %.h, $^} -o $@
				
leaks: ${OBJ} ${OBJ_TEST}
		${CXX} $^ ${LDFLAGS} -o test
		leaks --atExit -- ./test
san: clean add_sanitaizer test
cpp:
		cppcheck ${PROJECT}
check: 
		@cp ../materials/linters/.clang-format ./
		clang-format -n $(shell find ./ tests -type f -name "*.cc" -o -name "*.h")
		@rm -rf .clang-format
check2:
		@cp ../materials/linters/.clang-format ./
		clang-format -i $(shell find ./ tests -type f -name "*.cc" -o -name "*.h")
		@rm -rf .clang-format
gcov_report: clean add_coverage ${GCOV_OBJ}
		@$(CXX) $(CXXFLAGS)  $(GCOV_OBJ) $(LDFLAGS) -o test
		@./test
		@-mkdir report
		lcov --branch-coverage --ignore-errors mismatch,mismatch,empty,inconsistent,usage,unused --no-external -t "test" -q -o test.info -c -d . 
		lcov --remove test.info "tests/*" "container/*"  -o test.info
		genhtml --ignore-errors mismatch -o report test.info
		open report/index.html
		rm -rf *.gcda *.gcno *.out
add_coverage:
	$(eval CXXFLAGS += -fprofile-arcs -ftest-coverage -O0)
add_sanitaizer:
	$(eval CXXFLAGS += -fsanitize=address)
	$(eval LDFLAGS +=	-fsanitize=address -lasan)

