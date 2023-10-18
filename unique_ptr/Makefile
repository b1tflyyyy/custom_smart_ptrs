CXX = clang++

OPT = -O0
CPPV = c++20

CXXFLAFS = -Wall -Wextra -std=$(CPPV)
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

rec: fclean all clean
