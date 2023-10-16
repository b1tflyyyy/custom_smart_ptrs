CXX = clang++

OPT = -O0

CXXFLAFS = -Wall -Wextra -std=c++17 -v
DEPFLAGS = -MP -MD

BINARY = unique_ptr_sample.out
SRCS = *.cpp

OBJECTS = $(patsubst %.cpp, %.o, $(SRCS))
DEPFILES = $(patsubst %.cpp, %.d, $(SRCS))

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(DEPFLAGS) $(OPT) -o $@ $(OBJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(DEPFLAGS) $(OPT) -c $< -o $@ 

clean:
	rm -rf *.o *.d

fclean: 
	rm -rf *.o *.d *.out

re: fclean all
