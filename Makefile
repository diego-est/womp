CC=g++

all:
	meson setup build --wipe
	cd build && meson compile

format:
	clang-format -i src/*.cpp
	clang-format -i src/*.hpp

.PHONY: all
