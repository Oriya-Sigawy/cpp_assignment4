#214984932 oriyas.07@gmail.com
CC=g++
FLAGS= -Wall -g -Wextra
RAYLIB=raylib-5.0_linux_i386/lib/libraylib.a
.PHONY: all clean
all: tree test
test: Test.cpp
	$(CC) $(FLAGS) $^ -o $@
tree: main.o complex.o $(RAYLIB)
	$(CC) $(FLAGS) $^ -o tree
main.o: Main.cpp Tree.hpp Complex.hpp
	$(CC) $(FLAGS) -c $< -o $@ 
complex.o: Complex.cpp Complex.hpp
	$(CC) $(FLAGS) -c $< -o $@	
clean:
	rm -f *.o tree test