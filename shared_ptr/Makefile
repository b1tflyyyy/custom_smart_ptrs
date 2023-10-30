CXX = clang++

OPT = -O0
CPPV = c++17

CXXFLAGS = -Wall -Wextra -std=$(CPPV)
DEPFLAGS = -MP -MD

BINARY = shared_ptr_sample.out
SRCS = *.cpp

OBJECTS = $(patsubst %.cpp, %.o, $(SRCS))
DEPFILES = $(patsubst %.cpp, %.d, $(SRCS))

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(DEPFLAGS) $(OPT) -o $@ $^

%.o: %.cpp
	@echo "\033[0;32m [OK] \033[0m \033[0;33m Compiling:\033[0m" $<
	$(CXX) $(CXXFLAGS) $(DEPFLAGS) $(OPT) -c $< -o $@

clean:
	@echo "\033[0;32m [CLEANING WITHOUT BINARY]\033[0m"
	rm -rf *.o *.d

fclean: 
	@echo "\033[0;32m [FULL CLEANING WITH BINARY]\033[0m"
	rm -rf *.o *.d *.out

re: fclean all

rec: fclean all clean
