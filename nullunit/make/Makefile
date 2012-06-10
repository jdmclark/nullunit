# Example Makefile for compiling NullUnit.
# ----------------------------------------
# This Makefile is only intended as an example.
# It must be modified (or re-written) to suit
# your platform, project, and build system.
#
# Targets:
#	make all - Build the library and run tests
#	make nullunit - Build the library
#	make test - Build the library and test suite
#	make clean - Removes temporary files.

BASE_PATH = ..
OBJ_PATH = $(BASE_PATH)/obj
BIN_PATH = $(BASE_PATH)/bin
LIB_PATH = $(BASE_PATH)/lib

NU_OUTPUT = $(LIB_PATH)/nullunit.a
TEST_OUTPUT = $(BIN_PATH)/test

CPPFLAGS += -I$(BASE_PATH)/include
CXXFLAGS += -std=c++0x -Wall -Wextra -Wno-unused-variable -Wno-unused-parameter

NU_SOURCE_FILES = $(wildcard $(BASE_PATH)/src/*.cpp)
NU_HEADER_FILES = $(wildcard $(BASE_PATH)/src/*.h)
NU_OBJECT_FILES = $(subst /src/,/obj/src/,$(NU_SOURCE_FILES:.cpp=.o))

TEST_SOURCE_FILES = $(wildcard $(BASE_PATH)/test/*.cpp)
TEST_HEADER_FILES = $(wildcard $(BASE_PATH)/test/*.h)
TEST_OBJECT_FILES = $(subst /test/,/obj/test/,$(TEST_SOURCE_FILES:.cpp=.o))

LIB_HEADER_FILES = $(wildcard $(BASE_PATH)/include/nullunit/*.h) \
		$(wildcard $(BASE_PATH)/include/nullunit/internal/*.h)

.DEFAULT: all
.PHONY: all
all: test
	./$(TEST_OUTPUT)

.PHONY: test
test: directory_structure $(TEST_OUTPUT)

.PHONY: nullunit
nullunit: directory_structure $(NU_OUTPUT)

.PHONY: directory_structure
directory_structure:
	mkdir -p $(BIN_PATH) $(LIB_PATH) $(OBJ_PATH)/src $(OBJ_PATH)/test

.PHONY: clean
clean:
	rm -rf $(BIN_PATH) $(LIB_PATH) $(OBJ_PATH)

$(TEST_OUTPUT): $(NU_OUTPUT) $(TEST_OBJECT_FILES)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ $(NU_OUTPUT) -o $@

$(NU_OUTPUT): $(NU_OBJECT_FILES)
	$(AR) $(ARFLAGS) $@ $^

$(OBJ_PATH)/src/%.o: $(BASE_PATH)/src/%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(OBJ_PATH)/test/%.o: $(BASE_PATH)/test/%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

# Header dependencies:
$(NU_SOURCE_FILES) : $(NU_HEADER_FILES)
$(TEST_SOURCE_FILES) : $(NU_HEADER_FILES) $(TEST_HEADER_FILES)

