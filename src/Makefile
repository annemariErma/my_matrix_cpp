SHELL = /bin/sh
CFLAGS= -g -std=c++17 -Wall -Werror -Wextra -lstdc++
SANIT = -fsanitize=address
CC = gcc #-lstdc++
TST_LIBS := -lgtest -lpthread

OS = $(shell uname)
ifeq ($(OS), Darwin) # MAC
OPEN= open ./report/index.html
LIBS = -L /usr/local/lib
CC +=-D MacOS
LEAK_CHECK=CK_FORK=no leaks --atExit -- ./my_matrix
endif

ifeq ($(OS), Linux) # LINUX
OPEN= #xdg-open report/index.html
LIBS=  -lsubunit -lpthread -lrt
CC += -D Linux
LEAK_CHECK=valgrind --log-file="report.txt" --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose  -s ./my_matrix
endif

all: clean my_matrix_oop.a test gcov_report

my_matrix_oop.a: clean my_matrix.cc my_matrix_oop.h
	$(CC) $(CFLAGS) -c my_matrix.cc -lm -o my_matrix.o
	ar rc my_matrix_oop.a my_matrix.o
	ranlib my_matrix_oop.a

test: clean my_matrix_oop.a test.o
	$(CC)  test.o -L. my_matrix_oop.a -o my_matrix $(TST_LIBS) $(CFLAGS)
	./my_matrix

my_matrix.o:
	$(CC) $(CFLAGS) -c my_matrix.cc -g

test.o: clean
	$(CC) $(CFLAGS) -c test.cpp -lgtest -lgmock -lpthread -o test.o

clean:
	@rm -Rf *.o *.a *.gcno *.gcda *.info report my_matrix test my_test .clang-format report.txt report.txt--leak-check=full *.dSYM

leaks: clean test
	$(LEAK_CHECK)

gcov_report: clean
	@$(CC) -fprofile-arcs -ftest-coverage --coverage my_matrix.cc test.cpp -o my_matrix $(TST_LIBS) $(CFLAGS)
	@./my_matrix
	@lcov -t my_test -o test.info -c -d .
	@genhtml -o report test.info
	@$(OPEN)

 clang_check:
	@cp ../materials/linters/.clang-format .
	clang-format -n *.cc *.cpp *.h
	@rm .clang-format

 clang_format:
	@cp ../materials/linters/.clang-format .
	clang-format -i *.cc *.cpp *.h
	@rm .clang-format

cppcheck:
	cppcheck *.cc *.cpp *.h

