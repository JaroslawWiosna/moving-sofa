# https://stackoverflow.com/a/13673907
INCLUDES=-I/usr/sbin/include/libpng16 
CXXFLAGS=$(INCLUDES) -O3 -std=c++17 -Wswitch -Wextra -Wpedantic -Werror
DEBUG_CXXFLAGS=$(CXXFLAGS) -ggdb -O0
LIBS=-lpng16 -lgif
PROG=moving-sofa
DEBUG_PROG=$(PROG)_debug
OBJS= \
	  src/main.o \

.PHONY: all
all: $(PROG) Makefile

# TODO: Does %.cpp capture src/%.cpp?
%.cpp: %.hpp

$(PROG): $(OBJS) Makefile
	$(CXX) $(CXXFLAGS) -o $(PROG) $(OBJS) $(LIBS)

# %.o: %.cpp
# 	$(CXX) $(CXXFLAGS) -o $@ $<

.PHONY: run
run: $(PROG)
	./$(PROG)

.PHONY: debug
debug: Makefile
	$(CXX) $(DEBUG_CXXFLAGS) -o $(DEBUG_PROG) src/main.cpp $(LIBS)

.PHONY: run-debug
run-debug: debug
	/opt/rh/devtoolset-7/root/usr/bin/gdb --command=.gdbinit ./$(DEBUG_PROG)

.PHONY: run-debug-valgrind
run-debug-valgrind: debug
	/opt/rh/devtoolset-7/root/usr/bin/valgrind --leak-check=full ./$(DEBUG_PROG)

.PHONY: format
format: $(wildcard *.cpp) $(wildcard *.hpp) 
	/opt/rh/llvm-toolset-7/root/usr/bin/clang-format -i src/*.cpp 
	
.PHONY: clean
clean:
	rm -rf src/*.o
	rm -rf $(PROG)
	rm -rf $(DEBUG_PROG)
