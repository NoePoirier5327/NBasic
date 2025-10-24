CXX = g++
LDFLAGS = 
INCLDFLAGS = 
DEBUGFLAGS = -g
CXXFLAGS = -Wall -std=c++17

SRCDIR = src
SRC = $(wildcard $(SRCDIR)/*.cpp)
APP = ./bin/nbasic
OBJDIR = obj
OBJ = $(addprefix $(OBJDIR)/, $(notdir $(SRC:.cpp=.o)))

all: $(OBJ)
	$(CXX) $(DEBUGFLAGS) -o $(APP) $^ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(DEBUGFLAGS) -c $(INCLDFLAGS) $< -o $@

run: 
	$(APP)

debug: 
	gdb $(APP)

clean:
	rm $(OBJDIR)/*.o

init:
	mkdir obj
	mkdir bin
