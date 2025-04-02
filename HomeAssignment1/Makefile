PROJECT = ascii85

TESTPROJECT = $(PROJECT)-test

PYTESTPROJECT = $(PROJECT)-pytest

LIBPROJECT = $(PROJECT).a

GTESTPATH = -I/usr/src/googletest/googletest/include

GMOCKPATH = -I/usr/src/googletest/googlemock/include

TESTLIBPATH = -L/usr/src/googletest/build/lib

OBJECTS = base85.o

TEST-OBJECTS = base85-test.o

PYTEST-OBJECTS = base85-pytest.o

DEPS = (wildcard *.h)

A = ar

AFLAGS = rsv

CXX = g++

CXXFLAGS = -I. -std=c++17 -Werror -Wpedantic -Wall -g -fPIC $(GTESTPATH) $(GMOCKPATH)

LDXXFLAGS = $(CXXFLAGS) -L. -l:$(LIBPROJECT)

LDGTESTFLAGS = $(LDXXFLAGS) $(TESTLIBPATH) -lgtest_main -lgtest -lgmock -lpthread

.PHONY: default

default: all;

%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)
	
$(LIBPROJECT): $(OBJECTS)
	$(A) $(AFLAGS) $@ $^

$(PROJECT): main.o $(LIBPROJECT)
	$(CXX) -o $@ main.o $(LDXXFLAGS)

$(TESTPROJECT): $(LIBPROJECT) $(TEST-OBJECTS) 
	$(CXX) -o $@ $(TEST-OBJECTS) $(LDGTESTFLAGS)
	
$(PYTESTPROJECT): $(LIBPROJECT) $(PYTEST-OBJECTS) 
	$(CXX) -o $@ $(PYTEST-OBJECTS) $(LDGTESTFLAGS)
	
test: $(TESTPROJECT)

pytest: $(PYTESTPROJECT)
	python3 testing_files.py

all: $(PROJECT)

.PHONY: clean

clean:
	rm -f *.o

cleanall: clean
	rm -f $(PROJECT)
	rm -f $(LIBPROJECT)
	rm -f $(TESTPROJECT)
	rm -f $(PYTESTPROJECT)
	rm -f *.txt
