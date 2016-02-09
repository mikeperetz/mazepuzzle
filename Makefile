
OBJS = main.o mazegen.o disjointsets.o png.o rgbapixel.o
EXENAME = maze

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LINK = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi

all : $(EXENAME) clean_objs

$(EXENAME) : $(OBJS)
	$(LINK) $(OBJS) $(LDFLAGS) -o $(EXENAME)

main.o : main.cpp disjointsets.o mazegen.o png.o rgbapixel.o 
	$(CXX) $(CXXFLAGS) main.cpp

mazegen.o : mazegen.h mazegen.cpp png.o disjointsets.o
		$(CXX) $(CXXFLAGS) mazegen.cpp

disjointsets.o : disjointsets.h disjointsets.cpp 
	$(CXX) $(CXXFLAGS) disjointsets.cpp

png.o : png.cpp png.h rgbapixel.o
	$(CXX) $(CXXFLAGS) png.cpp

rgbapixel.o: rgbapixel.h rgbapixel.cpp
	$(CXX) $(CXXFLAGS) rgbapixel.cpp
	

clean_objs : 
	rm -f *.o

clean :
	rm -f *.o $(EXENAME)

