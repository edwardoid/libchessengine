DIR := ./
CC:= g++
LINK_LIBS:= -lpgnm -lchessengine
BINARY_TARGET := example.exe
.PHONY: all
all: binary

.PHONY: binary
binary: $(OBJ_FILES)
	$(CC) main.cpp $(LINK_LIBS) -o $(DIR)$(BINARY_TARGET)

.PHONY: run
run: binary
	./$(DIR)$(BINARY_TARGET)


.PHONY: build_debug
build_debug: $(OBJ_FILES)
	$(CC) -g $(DEB_FLAGS) main.cpp $(LINK_LIBS) -o $(DIR)$(BINARY_TARGET)

.PHONY: debug
debug: build_debug
	gdb ./$(DIR)$(BINARY_TARGET)
	
.PHONY: clean
clean:
	rm -rf $(DIR)*.o
	rm -rf $(DIR)*.dep
