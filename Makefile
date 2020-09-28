.PHONY: all clean default_target test build run cmake

default_target: all

all: clean cmake build

cmake:
	mkdir build && cd build && cmake ..

build:
	cd build && make

run:
	./build/isabot

clean:
	rm ./build -fr

test:
	echo "no tests"
