CC=gcc

# Directories
SRC_DIR=src
BIN_DIR=bin

all: singly_linked_list.o doubly_linked_list.o

singly_linked_list.o:
	${CC} -c -o ${BIN_DIR}/singly_linked_list.o ${SRC_DIR}/singly_linked_list.c

doubly_linked_list.o:
	${CC} -c -o ${BIN_DIR}/doubly_linked_list.o ${SRC_DIR}/doubly_linked_list.c

clean_sources:
	rm -f ${SRC_DIR}/*~

clean_binaries:
	rm -f ${BIN_DIR}/*~

clean: clean_sources clean_binaries

