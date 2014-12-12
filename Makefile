# 2014 Walking Software

PROG = graphdb
JSON = sample2.json
DOXYGEN = doxygen
CXX = g++
CC = gcc
CFLAGS = -W -Wall -I../.. -pthread -g -O0 $(CFLAGS_EXTRA)
CXXFLAGS = -std=c++11

# Make does not offer a recursive wildcard function, so here's one:
rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

CSOURCES = $(call rwildcard,../webserver/,*.c)
CXXSOURCES = $(call rwildcard,./,*.cpp) $(call rwildcard,../rapidjson/,*.cpp) $(call rwildcard,../graphLibrary/src/*/,*.cpp)

$(PROG): $(CSOURCES)
	$(CC) -c $(CSOURCES) $(CFLAGS)
	$(CXX) -c $(CXXSOURCES) $(CXXFLAGS)
	$(CXX) -o $(PROG) ./*.o

clean:
	rm -rf $(PROG) *.exe *.dSYM *.obj *.exp *.o *.lib *.out

all: run
	cd Documents; doxygen Doxyfile

run: $(PROG)
	cd ./Documentation/; $(DOXYGEN) Doxyfile
	./graphdb $(JSON)

.PHONY: all run