CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++11 -Iinclude 
LDFLAGS := -lsqlite3

TARGET := build/app
SRCDIR := src
OBJDIR := build/obj

SRCDIR := src
OBJDIR := build/obj

SRCS := $(wildcard $(SRCDIR)/*.cpp)
OBJS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	mkdir -p build
	$(CXX) $(OBJS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: all
	./$(TARGET)

clean:
	rm -rf build

.PHONY: all run clean
