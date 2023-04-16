cmake_minimum_required(VERSION 3.20)

project(SDL2Test)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(
    sdl2

    URL         https://github.com/libsdl-org/SDL/releases/download/release-2.26.5/SDL2-2.26.5.zip
    URL_HASH    MD5=0664f3980570c4641128866e6c9f2e29
    SOURCE_DIR  ${CMAKE_SOURCE_DIR}/vendor/sdl2
)

FetchContent_Declare(
    sdl2_image

    URL         https://github.com/libsdl-org/SDL_image/releases/download/release-2.6.3/SDL2_image-2.6.3.zip
    URL_HASH    MD5=ecedb5078bbd31e7d1552e2b1443d2f6
    SOURCE_DIR  ${CMAKE_SOURCE_DIR}/vendor/sdl2_image
)

FetchContent_Declare(
    sdl2_ttf

    URL         https://github.com/libsdl-org/SDL_ttf/releases/download/release-2.20.2/SDL2_ttf-2.20.2.zip
    URL_HASH    MD5=7258258fdb2a4adb0072d337f94305f9
    SOURCE_DIR  ${CMAKE_SOURCE_DIR}/vendor/sdl2_ttf
)

FetchContent_Declare(
    fmt

    URL         https://github.com/fmtlib/fmt/releases/download/9.1.0/fmt-9.1.0.zip
    URL_HASH    MD5=6133244fe8ef6f75c5601e8069b37b04
    SOURCE_DIR  ${CMAKE_SOURCE_DIR}/vendor/fmt
)

FetchContent_Declare(
    glew

    URL         https://github.com/nigels-com/glew/releases/download/glew-2.2.0/glew-2.2.0.zip
    URL_HASH    MD5=970535b75b1b69ebd018a0fa05af63d1
    SOURCE_DIR  ${CMAKE_SOURCE_DIR}/vendor/glew
)
FetchContent_GetProperties(glew)
if (NOT ${glew_POPULATED})
    FetchContent_Populate(glew)
    add_subdirectory(${CMAKE_SOURCE_DIR}/vendor/glew/build/cmake)
endif()

set(BUILD_SHARED_LIBS FALSE)

set(SDL2IMAGE_INSTALL OFF)
set(SDL2IMAGE_VENDORED ON)

set(SDL2TTF_INSTALL OFF)
set(SDL2TTF_VENDORED ON)
FetchContent_MakeAvailable(sdl2 sdl2_image sdl2_ttf fmt)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

add_executable(SDL2FrameworkTest
    ${SRC_DIR}/core/main.cpp
    ${SRC_DIR}/core/context.cpp
    ${SRC_DIR}/util/time.cpp
    ${SRC_DIR}/app.cpp
    ${SRC_DIR}/triangle.cpp

    ${INCLUDE_DIR}/core/context.h
    ${INCLUDE_DIR}/util/time.h
    ${INCLUDE_DIR}/util/game_object.h
    ${INCLUDE_DIR}/util/vector.h
    ${INCLUDE_DIR}/config.h
    ${INCLUDE_DIR}/app.h
    ${INCLUDE_DIR}/triangle.h
)
target_link_libraries(SDL2FrameworkTest
    SDL2::SDL2-static
    SDL2::SDL2main
    SDL2_ttf::SDL2_ttf-static

    ${OPENGL_LIBRARY}
    glew_s
    fmt::fmt
)
target_include_directories(SDL2FrameworkTest SYSTEM PRIVATE
    ${CMAKE_SOURCE_DIR}/vendor/sdl2/include/
    ${CMAKE_SOURCE_DIR}/vendor/glew/include/
    ${CMAKE_SOURCE_DIR}/vendor/fmt/include/
)
target_include_directories(SDL2FrameworkTest PRIVATE
    ${INCLUDE_DIR}
)
target_compile_options(SDL2FrameworkTest PRIVATE
    -Wall -pedantic
)
