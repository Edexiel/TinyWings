cmake_minimum_required(VERSION 3.0)
project(TinyWings VERSION 0.1.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

if(LINUX)
    message(STATUS ">>> Linux ${CMAKE_SYSTEM}")
    # linux stuff here
    add_definitions(-DLINUX)
elseif(WIN32)
    add_definitions(-DWIN32)
    message(STATUS ">>> Not Linux ${CMAKE_SYSTEM}")
    # stuff that should happen on Win32
else()
    message(FATAL_ERROR ">>> Not supported platform ${CMAKE_SYSTEM}")
endif()

find_package(raylib 3.5 QUIET)


if (NOT raylib_FOUND)
  include(FetchContent)

  FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/3.5.0.zip
  )

  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED)
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)

    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

    # build raylib
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
  endif()
endif()


add_executable(${PROJECT_NAME} src/main.cpp)

target_include_directories (${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} raylib)