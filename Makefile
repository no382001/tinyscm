CC=gcc
CXX=g++
CFLAGS=-g
CXXFLAGS=-g
LDFLAGS=-lgtest -lgtest_main -pthread
LCOVFLAGS=-fprofile-arcs -ftest-coverage 
RM=rm -f

all: tinylisp

tinylisp: gen_enum
	$(CC) $(CFLAGS) tinylisp.c -o tinylisp

test: gen_enum
	$(CXX) $(CXXFLAGS) func_test.cpp $(LDFLAGS) -o test && ./test

coverage: gen_enum
	$(CXX) $(CXXFLAGS) $(LCOVFLAGS) func_test.cpp $(LDFLAGS) -lgcov -o test_coverage \
	&& lcov -c -o coverage.info -d . && ./test_coverage && genhtml coverage.info -o cov_report

gen_enum:
	python3 gen_enum_map.py

clean:
	$(RM) *.o *.out error_map.h tinylisp test* coverage.info func_test.gcda func_test.gcno

help:
	@echo "Usage:"
	@echo "  make [target]"
	@echo "Targets:"
	@echo "  all      - builds the main application"
	@echo "  test     - builds and runs the tests"
	@echo "  gen_enum - Generates enum mappings"
	@echo "  clean    - removes all generated files"
	@echo "  coverage - generates code coverage report (not implemented)"
