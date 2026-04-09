.PHONY:
all: build/01-list build/02-list build/03-list

build/01-list: examples/list/01-list.c
	mkdir -p build && cc examples/list/01-list.c -o build/01-list

build/02-list: examples/list/02-list-multifile.c examples/list/02-list-multifile.h
	mkdir -p build && cc examples/list/02-list-multifile.c -o build/02-list

build/03-list: examples/list/03-list-dbg.c
	mkdir -p build && cc examples/list/03-list-dbg.c -o build/03-list
