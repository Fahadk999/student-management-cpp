CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++11 -Iinclude -IDatabaseManager/include
LDFLAGS := -lsqlite3

TARGET := build/app
SRCDIR := src
DBDIR := DatabaseManager
OBJDIR := build/obj

SRCS := $(wildcard $(SRCDIR)/*.cpp) \
        $(wildcard $(DBDIR)/*.cpp)

OBJS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(filter $(SRCDIR)/%.cpp,$(SRCS))) \
        $(patsubst $(DBDIR)/%.cpp,$(OBJDIR)/%.o,$(filter $(DBDIR)/%.cpp,$(SRCS)))

all: $(TARGET)

$(TARGET): $(OBJS)
	mkdir -p build
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(DBDIR)/%.cpp
	mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: all
	./$(TARGET)

clean:
	rm -rf build

.PHONY: all run clean
