.PHONY: all clean test s21_string.a check gcov_report
CC=gcc
LOGIN=rdontos
OS := $(shell uname -s)
 
ifeq ($(OS), Darwin)
	CC += -D OS_MAC
else
	CC += -D OS_LINUX
endif
 
default: all
 
all: clean s21_string.a test
 
test: s21_string.a
ifeq ($(OS), Darwin)
	$(CC) -o test test.c s21_string.a -lcheck
	./test
else
	$(CC) -o test test.c s21_string.a -lcheck -lsubunit -lrt -lpthread -lm
	./test
endif
 
s21_string.a: s21_string.o
	ar rcs s21_string.a s21_string.o
	ranlib $@
	cp $@ lib$@
	
s21_string.o: s21_string.c
	$(CC) -c -o s21_string.o s21_string.c

gcov_report:
ifeq ($(OS), Darwin)
	$(CC) --coverage -o testresult test.c s21_string.c -lcheck
	./testresult
else
	$(CC) -o testresult test.c s21_string.c -lcheck -lsubunit -lrt -lpthread -lm
	./testresult
endif
	lcov -t "testresult" -o testresult.info -c -d .
	genhtml -o report testresult.info
 
verification:
	cp ../materials/linters/CPPLINT.cfg .
	python3 ../materials/linters/cpplint.py --extension=c s21_string.* test.c
	CK_FORK=no leaks -atExit -- ./test

clean:
	rm -rf test *.a *.o *.out *.gc* *.info report testresult
 
rebuild: clean all
