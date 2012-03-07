DIR := ./
CC:= g++
LINK_LIBS := -lpgnm -lchessengine
BINARY_TARGET := debugExample
INCLUDE_DIR := ./../src -I./../3rdparty/libpgnm/src
LIBS_DIR := -L./../lib -L./../3rdparty/libpgnm/lib
.PHONY: all
all: binary

.PHONY: binary
binary: $(OBJ_FILES)
	$(CC) main.cpp -I$(INCLUDE_DIR) $(LIBS_DIR) -static $(LINK_LIBS) -o $(DIR)$(BINARY_TARGET)

.PHONY: run
run: binary
	./$(DIR)$(BINARY_TARGET)


.PHONY: build_debug
build_debug: $(OBJ_FILES)
	$(CC) -g $(DEB_FLAGS) main.cpp  -I$(INCLUDE_DIR) $(LIBS_DIR) -static $(LINK_LIBS) -o $(DIR)$(BINARY_TARGET)

.PHONY: debug
debug: build_debug
	gdb ./$(DIR)$(BINARY_TARGET)
	
.PHONY: clean
clean:
	rm -rf $(DIR)*.o
	rm -rf $(DIR)*.dep
