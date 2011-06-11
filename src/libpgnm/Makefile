SRC_DIR := src/
OBJ_DIR := obj/
BIN_DIR := bin/
DEP_DIR := dep/
LIB_DIR := lib/
INC_DIR := ./src 
CC:= g++ -ansi -g3 
SRC_FILES:=$(wildcard $(SRC_DIR)*.cpp)
OBJ_FILES:=$(patsubst $(SRC_DIR), $(OBJ_DIR),$(patsubst $(SRC_DIR)%.cpp,$(OBJ_DIR)%.o,$(SRC_FILES)))
DEFILES:=$(patsubst $(SRC_DIR), $(DEP_DIR),$(patsubst $(SRC_DIR)%.cpp,$(DEP_DIR)%.o,$(SRC_FILES)))
LIBRARY_TARGET := pgnm
.PHONY: all
all: library

.PHONY: library
library: static shared

.PHONY: static
static: $(OBJ_FILES)
	ar -r $(LIB_DIR)lib$(LIBRARY_TARGET).a $(OBJ_FILES)

.PHONY: shared
shared: $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -shared -o $(LIB_DIR)lib$(LIBRARY_TARGET).so
$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	$(CC) -c $< -I$(INC_DIR) -o $@
$(DEP_DIR)%.dep: $(SRC_DIR)%.cpp
	$(CC) -MM $< -MT "$@ $(patsubst $(DEP_DIR)%.dep,$(OBJ_DIR)%o,$@)" -I$(INC_DIR) -o $@

-include $(DEP_FILES)

.PHONY: install
install:
	cp $(LIB_DIR)* /usr/local/lib
	cp $(SRC_DIR)* /usr/local/include


.PHONY: prepare
prepare:
	mkdir -p $(DEP_DIR)
	mkdir -p $(OBJ_DIR)
	mkdir -p $(BIN_DIR)
	mkdir -p $(LIB_DIR)

.PHONY: clean
clean:
	rm -rf $(BIN_DIR)*
	rm -rf $(LIB_DIR)*
	rm -rf $(OBJ_DIR)*
	rm -rf $(DEP_DIR)*
