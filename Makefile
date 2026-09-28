# CampusGuard - COS 214 Practical 5
# Builds with:  make
# Runs with:    make run   (or ./campusguard directly)
# Cleans with:  make clean

CXX      := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -g -I. -MMD -MP
TARGET   := campusguard
SRC      := $(shell find . -name '*.cpp')
OBJ      := $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: all
	./$(TARGET)

clean:
	find . -name '*.o' -delete
	find . -name '*.d' -delete
	rm -f $(TARGET)

-include $(OBJ:.o=.d)
.PHONY: all run clean
