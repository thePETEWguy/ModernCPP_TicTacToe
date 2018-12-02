# ModernCPP_TicTacToe
A tic tac toe game written in C++ which uses SDL2 library and SDL2_gfx, compiled on Ubuntu 18.04 with clang compiler using CMake

### Prerequisites
To compile the game, you must have CMake, clang, SDL2 and SDL2_gfx installed on your system.

#### Installing necessary libraries on Ubuntu

* CMake: ```sudo apt-get install cmake```
* Clang: ```sudo apt-get install clang```
* SDL2: ```sudo apt-get install libsdl2-2.0```<br>
For development: ```sudo apt-get install libsdl2-dev```
* SDL2_gfx: download the latest version from [here](http://www.ferzkopp.net/wordpress/2016/01/02/sdl_gfx-sdl2_gfx/)
After downloading SDL2_gfx, extract it, and enter the extracted directory and write the following commands:
  ```
  ./configure
  make
  make install
  ```

### Compiling TicTacToe
```
mkdir build && cd build
cmake ..
./TicTacToe
```
