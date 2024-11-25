CFLAGS += -Wno-sign-conversion

configure:
	cmake -S . -B build -Wno-dev

configure-dev:
	cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DJUCE_ENABLE_MODULE_SOURCE_GROUPS=ON -Wno-dev

build: cmake_configure
	cmake --build build

build-verbose: cmake_configure
	cmake --build build -v

clean:
	rm -rf ./build

.PHONY: all cmake_configure build clean
