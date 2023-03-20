cmake_minimum_required(VERSION 3.20)

project(SDL2Test)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(
    SDL2

    GIT_REPOSITORY  https://github.com/libsdl-org/SDL.git
    GIT_TAG         release-2.26.4
    GIT_SHALLOW     TRUE
    GIT_PROGRESS    TRUE
)
FetchContent_Declare(
    SDL2_IMAGE

    GIT_REPOSITORY  https://github.com/libsdl-org/SDL_image.git
    GIT_TAG         release-2.6.3
    GIT_SHALLOW     TRUE
    GIT_PROGRESS    TRUE
)
set(SDL2IMAGE_INSTALL OFF)
set(BUILD_SHARED_LIBS FALSE)
FetchContent_MakeAvailable(SDL2 SDL2_IMAGE)

add_executable(SDL2Test
    src/basic_test.cpp
)
target_link_libraries(SDL2Test
    SDL2::SDL2-static
)

add_executable(SDL2ImageTest
    src/show_image.cpp
)
target_link_libraries(SDL2ImageTest
    SDL2::SDL2-static SDL2_image::SDL2_image-static
)