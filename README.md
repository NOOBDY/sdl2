# SDL2 Experiment

Simple project is using SDL2 + OpenGL + CMake.This project is mainly a
proof-of-concept and not a complete project.

## Dependency Handling

The build system utilizes `cmake`. For handling 3rd-party dependencies
this project uses `FetchContent` to get all needed packages.

All dependencies are statically linked so no need to have preinstalled
library files on target machines.

## Building Project

```bash
cmake -B build
cmake --build build
```

or if you are on an older version of CMake,

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

Note that this step needs to download files from GitHub and compile them from
source so this process can take quite awhile.

## Executing

There are 4 executables:

* `SDL2Test`: A simple SDL test to create a blank window.
* `SDL2ImageTest`: Read an image from a hard-coded path.
* `SDL2TTFTest`: Render TTF fonts from a hard-coded path.
* `SDL2OpenGLTest`: Render a triangle with basic OpenGL 4.1 code.

For the hard-coded relative paths to work, the program has to be run in `build/`
