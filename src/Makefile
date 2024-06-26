GCC = gcc -Wall -Werror -Wextra -std=c11
GCOV = -fprofile-arcs -ftest-coverage
TESTN = test_g

C_FILES = test/*.c 
H_FILES = test/test_me.h

CLANG = clang-format -style=Google
OS=$(shell uname -s)

OS_NAME := $(shell uname)
ifeq ($(OS_NAME), Linux)
 ADDITIONAL_FLAGS = -lpthread -lm -D_GNU_SOURCE -lrt -lsubunit
else ifeq ($(OS_NAME), Darwin)
 ADDITIONAL_FLAGS :=
endif

ifeq ($(OS),Darwin)
  	OPEN = open
	LC = -lcheck
	VALGRIND = open -a 'Docker' && cd .. && cd materials/build/Valgrind && bash run.sh
endif
ifeq ($(OS),Linux)
	OPEN = xdg-open
	LC = -lcheck -lsubunit -lrt -lpthread -lm -D_GNU_SOURCE
	VALGRIND = make s21_string.a && cd test && gcc -g *.c ../s21_string.a -o test -lcheck -lcheck -lpthread -lm -D_GNU_SOURCE -lrt -lsubunit && valgrind -s --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./test && cd ..
endif

all: test

s21_string.a: s21_string.c s21_sprintf.c s21_sscanf.c s21_string.h s21_errno.h
	$(GCC) -c s21_string.c -o s21_string.o
	$(GCC) -c s21_sprintf.c -o s21_sprintf.o
	$(GCC) -c s21_sscanf.c -o s21_sscanf.o
	ar rcs s21_string.a s21_string.o s21_sprintf.o  s21_sscanf.o
	rm *.o

test: s21_string.a test_1
	./test1
	rm s21_string.a

test_1: $(H_FILES) $(C_FILES)
	$(GCC) $(C_FILES) s21_string.a -o test1 -lcheck $(ADDITIONAL_FLAGS)

install_brew:
	cd ~
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh

install_lcov:
	brew install lcov

clean_test:
	rm -rf *.gcda *.gcno $(TESTN)

gcov_report: clean
	$(GCC) $(GCOV) s21_*.c  $(C_FILES) -o $(TESTN) $(LC)
	./$(TESTN)
	lcov -t "test" -o $(TESTN).info -c -d .
	genhtml -o report $(TESTN).info
	$(OPEN) ./report/index.html
	make clean_test

valgrind:
	$(VALGRIND)

style:
	$(CLANG) -n *.c *.h
	$(CLANG) -i *.c *.h
	$(CLANG) -n */*.c *.h
	$(CLANG) -i */*.c *.h

clean:
	rm -rf s21_string.a *.o test1 *.gcno *.gcda report *.info g_test test_v
	rm -rf ./report
	rm -rf ../*.g*

rebuild: clean all