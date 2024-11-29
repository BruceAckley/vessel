CFLAGS += -Wno-sign-conversion

configure:
	cmake -S . -B build -Wno-dev

configure-dev:
	cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DJUCE_ENABLE_MODULE_SOURCE_GROUPS=ON -Wno-dev

build:
	cmake --build build

build-verbose:
	cmake --build build -v

test: build
	./build/tests/AudioPluginTest --gtest_color=yes --gtest_print_time=1

clean:
	rm -rf ./build

.PHONY: all cmake_configure build clean
