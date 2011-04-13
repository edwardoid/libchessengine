SRC_DIR := ./src/
OBJ_DIR := ./obj/
BIN_DIR := ./bin/
DEP_DIR := ./dep/
LIB_DIR := ./lib/
INC_DIR := ./src/
DOC_DIR := ./doc/
TST_DIR := ./tests/
CC:= g++
DEB_FLAGS:= -g3 -gdwarf-2
SRC_FILES:=$(wildcard $(SRC_DIR)*.cpp)
OBJ_FILES:=$(patsubst $(SRC_DIR), $(OBJ_DIR),$(patsubst $(SRC_DIR)%.cpp,$(OBJ_DIR)%.o,$(SRC_FILES)))
DEFILES:=$(patsubst $(SRC_DIR), $(DEP_DIR),$(patsubst $(SRC_DIR)%.cpp,$(DEP_DIR)%.o,$(SRC_FILES)))
LIBRARY_TARGET := chessengine

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

.PHONY: prepare
prepare:
	mkdir -p $(DEP_DIR)
	mkdir -p $(OBJ_DIR)
	mkdir -p $(BIN_DIR)
	mkdir -p $(LIB_DIR)

.PHONY: doc
doc:
	doxygen

.PHONY: clean
clean:
	rm -rf $(BIN_DIR)*
	rm -rf $(LIB_DIR)*
	rm -rf $(OBJ_DIR)*
	rm -rf $(DEP_DIR)*
	rm -rf $(TST_DIR)test

.PHONY: test
test: all
	g++ $(DEB_FLAGS) $(TST_DIR)main.cpp -static  -lpgnm -lchessengine -L$(LIB_DIR) -I$(INC_DIR) -o $(BIN_DIR)test
	./$(BIN_DIR)test

.PHONY: install
install: static shared doc
	cp $(LIB_DIR)* /usr/local/lib
	cp $(SRC_DIR)*.h /usr/local/include
	cp -rf $(DOC_DIR)man/man3 /usr/local/man
	rm -rf /usr/local/man/man3/README*
	rm -rf /usr/local/man/man3/.svn
