cmake_minimum_required(VERSION 3.20)

project(SDL2Test)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(
    sdl2

    GIT_REPOSITORY  https://github.com/libsdl-org/SDL.git
    GIT_TAG         release-2.26.4
    GIT_SHALLOW     TRUE
    GIT_PROGRESS    TRUE
    SOURCE_DIR      ${CMAKE_SOURCE_DIR}/vendor/sdl2
)

FetchContent_Declare(
    sdl2_image

    GIT_REPOSITORY  https://github.com/libsdl-org/SDL_image.git
    GIT_TAG         release-2.6.3
    GIT_SHALLOW     TRUE
    GIT_PROGRESS    TRUE
    SOURCE_DIR      ${CMAKE_SOURCE_DIR}/vendor/sdl2_image
)

FetchContent_Declare(
    sdl2_ttf

    GIT_REPOSITORY  https://github.com/libsdl-org/SDL_ttf.git
    GIT_TAG         release-2.20.2
    GIT_SHALLOW     TRUE
    GIT_PROGRESS    TRUE
    SOURCE_DIR      ${CMAKE_SOURCE_DIR}/vendor/sdl2_ttf
)

FetchContent_Declare(
    glad

    GIT_REPOSITORY  https://github.com/Dav1dde/glad.git
    GIT_TAG         v2.0.4
    GIT_SHALLOW     TRUE
    GIT_PROGRESS    TRUE
    SOURCE_DIR      ${CMAKE_SOURCE_DIR}/vendor/glad
)
FetchContent_GetProperties(glad)
if(NOT glad_POPULATED)
    FetchContent_Populate(glad)
    add_subdirectory(${glad_SOURCE_DIR}/cmake)
    glad_add_library(glad_gl_core_41 STATIC API gl:core=4.1)
endif()

set(SDL2IMAGE_INSTALL OFF)
set(SDL2TTF_INSTALL OFF)
set(BUILD_SHARED_LIBS FALSE)
FetchContent_MakeAvailable(sdl2 sdl2_image sdl2_ttf)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

add_executable(SDL2FrameworkTest
    ${SRC_DIR}/core/main.cpp
    ${SRC_DIR}/core/context.cpp
    ${SRC_DIR}/App.cpp

    ${INCLUDE_DIR}/core/context.h
    ${INCLUDE_DIR}/App.h
)
target_link_libraries(SDL2FrameworkTest
    SDL2::SDL2-static
    SDL2::SDL2main

    ${OPENGL_LIBRARY}
    glad_gl_core_41
)
target_include_directories(SDL2FrameworkTest SYSTEM PRIVATE
    ${glad_BINARY_DIR}/../../gladsources/include/
    ${CMAKE_SOURCE_DIR}/vendor/sdl2/include/
)
target_include_directories(SDL2FrameworkTest PRIVATE
    ${INCLUDE_DIR}
)
target_compile_options(SDL2FrameworkTest PRIVATE
    -Wall -pedantic
)
