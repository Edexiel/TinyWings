# CMake generated Testfile for 
# Source directory: /home/lemome/Projets/tinywings/cmake-build-release/_deps/raylib-src/src
# Build directory: /home/lemome/Projets/tinywings/cmake-build-release/_deps/raylib-build/src
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(pkg-config--static "/home/lemome/Projets/tinywings/cmake-build-release/_deps/raylib-src/src/../cmake/test-pkgconfig.sh" "--static")
set_tests_properties(pkg-config--static PROPERTIES  _BACKTRACE_TRIPLES "/home/lemome/Projets/tinywings/cmake-build-release/_deps/raylib-src/src/CMakeLists.txt;212;add_test;/home/lemome/Projets/tinywings/cmake-build-release/_deps/raylib-src/src/CMakeLists.txt;0;")
subdirs("external/glfw")
