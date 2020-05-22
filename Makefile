.PHONY: build build-and-run clean


OUT_DIR ?= out/
SRC_DIR ?= src/
DEPS_DIR ?= deps/
EXEC_NAME ?= elastic

C++ ?= g++
C++_OPTIONS ?= -O3
C++_OPTIONS := $(C++_OPTIONS) -std=c++2a -Wall -Wextra -Werror -Wno-error=unused-variable -Wno-error=unused-parameter
C++ := $(C++) $(C++_OPTIONS)

LINKER ?= g++
LINKER_OPTIONS ?= -O3
LINKER_OPTIONS := $(LINKER_OPTIONS) -pthread -licutu -licuuc
LINKER := $(LINKER) $(LINKER_OPTIONS)

OBJECTS := $(patsubst $(SRC_DIR)%.cpp,$(OUT_DIR)%.o,$(wildcard $(SRC_DIR)*.cpp) $(wildcard $(SRC_DIR)*/*.cpp) $(wildcard $(SRC_DIR)*/*/*.cpp))

build: $(OUT_DIR)$(EXEC_NAME)

build-and-run: $(OUT_DIR)$(EXEC_NAME)
	./$(OUT_DIR)$(EXEC_NAME)

clean:
	find out -type f -delete
	find deps -type f -delete


$(OUT_DIR)$(EXEC_NAME): $(OBJECTS)
	$(LINKER) $+ $(LINKER_OPTIONS) -o $@

$(OUT_DIR)%.o: $(SRC_DIR)%.cpp
	mkdir $@a -p
	rmdir $@a
	mkdir $(DEPS_DIR)$*.da -p
	rmdir $(DEPS_DIR)$*.da
	$(C++) -MMD -MF $(DEPS_DIR)$*.d -MT $@ -c $< -o $@


-include deps/*.d
