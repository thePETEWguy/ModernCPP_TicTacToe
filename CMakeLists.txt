CMAKE_MINIMUM_REQUIRED(VERSION 3.10.2)

SET(APP_EXE TicTacToe)

SET(CMAKE_C_COMPILER "clang")
SET(CMAKE_CXX_COMPILER "clang++")

SET(CMAKE_CXX_STANDARD 14)

PROJECT(ModernCPP_TicTacToe)
ADD_EXECUTABLE(${APP_EXE} main.cpp)

ADD_SUBDIRECTORY(src)

FIND_PACKAGE(SDL2 REQUIRED)
INCLUDE_DIRECTORIES(include ${SDL2_INCLUDE_DIRS})

find_package(PkgConfig)
pkg_check_modules(SDL2_GFX SDL2_gfx)
include_directories(${SDL2_GFX_INCLUDE_DIRS})

TARGET_LINK_LIBRARIES(${APP_EXE}
                      SRC 
                      ${SDL2_LIBRARIES} ${SDL2_GFX_LIBRARIES})