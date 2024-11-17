cmake-configure:
	cmake -S . -B build -Wno-dev

build: cmake_configure
	cmake --build build

build-verbose: cmake_configure
	cmake --build build -v

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all cmake_configure build clean
