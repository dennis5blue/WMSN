BOOST = /home/share/boost1550
EIGEN = /home/share/eigen320
CC = g++
CFLAGS = -O
DFLAGS = -g -Wall

SOURCE = main.o \
	 map.o \
	 mapFactory.o \
	 utility.o

OBJECTS = ${SOURCE:.cpp=.o}

INCLUDE_PATH = -I ${BOOST}/include \
	       -I ${EIGEN}/include

LIB_PATH = -L ${BOOST}/lib

LIB_FLAGS = -lboost_program_options \
	    -lboost_regex \
	    -lboost_system \
	    -lboost_filesystem

.SUFFIXES:
.SUFFIXES: .cpp .o

all: main

main: ${OBJECTS}
	@echo buliding $@
	@-${CC} ${CFLAGS} ${INCLUDE_PATH} ${LIB_PATH} $^ -o $@ ${LIB_FLAGS}

%.o: %.cpp
	@echo making $@
	@-${CC} -c ${CFLAGS} ${DFLAGS} ${INCLUDE_PATH} ${LIB_PATH} $< -o $@ ${LIB_FLAGS}

.PHONY: clean
clean:
	@rm -f *.o main
