# Makefile

CXX = g++
CXXFLAGS = -Wall -std=c++17
TARGET = bard
SRCS = Bard.cpp
OBJS = $(SRCS:.cpp=.o)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp LinkedList.h
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET)
