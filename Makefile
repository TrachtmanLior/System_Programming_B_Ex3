#written by Lior Trachtman: 211791041
#EMAIL: lior16122000@gmail.com
CXX = g++
CXXFLAGS = -Wall -g -Wno-builtin-declaration-mismatch

.PHONY: all clean catan test tidy valgrind

DEMO_OBJECTS = Board.o Catan.o Demo.o DevelopmentCard.o Player.o Resources.o Road.o Settlement.o Tile.o
TEST_OBJECTS = TestCounter.o Test.o Board.o Catan.o DevelopmentCard.o Player.o Resources.o Road.o Settlement.o Tile.o

all: catan test

catan: $(DEMO_OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o catan

test: $(TEST_OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o test

tidy:
	clang-tidy Board.cpp Catan.cpp Demo.cpp DevelopmentCard.cpp Player.cpp Resources.cpp Road.cpp Settlement.cpp Tile.cpp -checks=bugprone-*,g++-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --

valgrind: catan
	valgrind --leak-check=full --track-origins=yes ./catan

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o catan test

#HOW TO RUN VALGRIND : valgrind --leak-check=full --track-origins=yes ./your_program
#HOW TO RUN CLANG:  clang-format -i Asset.cpp
