cmake_minimum_required(VERSION 3.20)

project(SDL2Test)

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

set(BUILD_SHARED_LIBS OFF)

set(SDL2IMAGE_INSTALL OFF)
set(SDL2IMAGE_VENDORED ON)

set(SDL2TTF_INSTALL OFF)
set(SDL2TTF_VENDORED ON)
FetchContent_MakeAvailable(sdl2 sdl2_image sdl2_ttf)

include_directories(lib/sdl2/include/)

add_executable(SDL2Test
    src/basic_test.cpp
)
target_link_libraries(SDL2Test
    SDL2::SDL2-static
    SDL2::SDL2main
)

add_executable(SDL2ImageTest
    src/show_image.cpp
)
target_link_libraries(SDL2ImageTest
    SDL2::SDL2-static
    SDL2::SDL2main
    SDL2_image::SDL2_image-static
)

add_executable(SDL2TTFTest
    src/render_ttf.cpp
)
target_link_libraries(SDL2TTFTest
    SDL2::SDL2-static
    SDL2::SDL2main
    SDL2_image::SDL2_image-static
    SDL2_ttf::SDL2_ttf-static
)

add_executable(SDL2OpenGLTest
    src/opengl_surface.cpp
)
target_include_directories(SDL2OpenGLTest PRIVATE
    lib/glew/include/
    ${glad_BINARY_DIR}/../../gladsources/glad_gl_core_41/include/
)
target_link_libraries(SDL2OpenGLTest
    SDL2::SDL2-static
    SDL2::SDL2main

    ${OPENGL_LIBRARY}
    glad_gl_core_41
)
