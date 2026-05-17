CXX = g++
LDFLAGS = 
INCLDFLAGS = 
DEBUGFLAGS = -g
STDFLAG = -std=c++17
CXXFLAGS = -pedantic -Wfatal-errors -Wconversion -Wredundant-decls -Wshadow -Wall -Wextra

APP = bin/nbasic
SRCDIR = src
SRC = $(shell find $(SRCDIR) -name "*.cpp")
OBJDIR = obj
OBJ = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRC))

all: $(OBJ)
	$(CXX) $(DEBUGFLAGS) -o $(APP) $^ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(STDFLAG) $(DEBUGFLAGS) -c $(INCLDFLAGS) $< -o $@

run: 
	$(APP)

debug: 
	gdb $(APP)

clean:
	rm $(OBJDIR)/*.o

init:
	mkdir obj
	mkdir obj/compiler
	mkdir obj/parser
	mkdir obj/tokenizer
	mkdir obj/interpreter
	mkdir bin
