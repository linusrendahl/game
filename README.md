// SDL3 install https://www.youtube.com/watch?v=Wuj7JJ7QcHk
// makefile: clang main.c -o main `pkg-config --libs --cflags sdl2
// https://wiki.libsdl.org/SDL3/README/cmake
// cmake -S . -B build -DSDL_FRAMEWORK=ON -DCMAKE_OSX_ARCHITECTURES="arm64;x86_64"
// cmake --build build
// cmake --install build --prefix ~/SDL
// Move sdl3.framework to ~/Library/Frameworks/
// create maps in ascii files (easier to edit). load ascii to array > render for each character to tile.
// tiling POE: https://www.pathofexile.com/forum/view-thread/55091
// https://github.com/nickdiego/compiledb (recognize sdl in neovim/clang for code completions).

