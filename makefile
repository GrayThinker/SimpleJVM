SRCDIR = src
OBJDIR = obj
INCDIR = include
rm = del /q

SRC:=$(wildcard $(SRCDIR)/*.cpp)
INC:=$(wildcard $(INCDIR)/*.hpp)
OBJ:=$(SRC:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

PATHFLAGS=-I ./include
CCFLAGS=-Wall -Wextra
CC=g++
TARGET=SJVM
BUILDDIR=.\build

$(TARGET): $(OBJ)
	$(CC) $^ -o $@

$(OBJ): $(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@echo $(CC) $<
	@$(CC) -c $(CCFLAGS) $(PATHFLAGS) $< -o $@

clean:
	@$(rm) .\$(OBJDIR)\*.o
	@$(rm) .\$(TARGET).exe