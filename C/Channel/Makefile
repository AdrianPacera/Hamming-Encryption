CC		:= gcc
CFLAGS	:= -Wall -Wextra -g

BIN		:= output
SRC		:= src
INCLUDE	:= include
LIB		:= lib

LIBRARIES	:=

ifeq ($(OS),Windows_NT)
EXECUTABLE	:= main.exe
RM = rm -f
else
RM = rm -f
EXECUTABLE	:= main
endif

SOURCEDIRS	:= $(shell find $(SRC) -type d)
INCLUDEDIRS	:= $(shell find $(INCLUDE) -type d)
LIBDIRS		:= $(shell find $(LIB) -type d)

CINCLUDES	:= $(patsubst %,-I%, $(INCLUDEDIRS:%/=%))
CLIBS		:= $(patsubst %,-L%, $(LIBDIRS:%/=%))

SOURCES		:= $(wildcard $(patsubst %,%/*.c, $(SOURCEDIRS)))
ALLOBJECTS  := $(SOURCES:.c=.o)
DEPS        := $(SOURCES:.c=.d)
TESTOBJECTS :=  $(filter-out src/main.o, $(ALLOBJECTS))
RELEASEOBJECTS := $(filter-out src/main_test.o, $(ALLOBJECTS))

INCLUDETEST	:= -I/c/Users/42194/OneDrive/Documents/Fontys/Unity-master/src
LIBUNITY := /c/Users/42194/OneDrive/Documents/Fontys/Unity-master/src/libunity.a

.SUFFIXES=.c .h

all: $(BIN)/$(EXECUTABLE) $(BIN)/main_test

.PHONY: clean
clean:
	-$(RM) $(BIN)/$(EXECUTABLE) $(BIN)/main_test
	-$(RM) $(ALLOBJECTS)
	-$(RM) $(DEPS)

run: all
	./$(BIN)/$(EXECUTABLE)

src/%.o: src/%.c
	$(CC) $(CFLAGS) $(CINCLUDES) $(INCLUDETEST) -c $^ -o $@ $(LIBRARIES)

$(BIN)/$(EXECUTABLE): $(RELEASEOBJECTS)
	$(CC) $(CFLAGS) $(CINCLUDES) $(CLIBS) $^ -o $@ $(LIBRARIES)

$(BIN)/main_test: $(TESTOBJECTS)
	$(CC) $(CFLAGS) $(CINCLUDES) $^ -o $@ $(LIBRARIES) $(LIBUNITY)