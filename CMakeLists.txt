cmake_minimum_required(VERSION 3.20)

project(SDL2Test)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(
    sdl2

    GIT_REPOSITORY  https://github.com/libsdl-org/SDL.git
    GIT_TAG         release-2.26.4
    GIT_SHALLOW     TRUE
    GIT_PROGRESS    TRUE
)

FetchContent_Declare(
    sdl2_image

    GIT_REPOSITORY  https://github.com/libsdl-org/SDL_image.git
    GIT_TAG         release-2.6.3
    GIT_SHALLOW     TRUE
    GIT_PROGRESS    TRUE
)

FetchContent_Declare(
    sdl2_ttf

    GIT_REPOSITORY  https://github.com/libsdl-org/SDL_ttf.git
    GIT_TAG         release-2.20.2
    GIT_SHALLOW     TRUE
    GIT_PROGRESS    TRUE
)

set(SDL2IMAGE_INSTALL OFF)
set(SDL2TTF_INSTALL OFF)
set(BUILD_SHARED_LIBS FALSE)
FetchContent_MakeAvailable(sdl2 sdl2_image sdl2_ttf)

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
target_include_directories(SDL2ImageTest PRIVATE
    ${sdl2_image_SOURCE_DIR}/
)
target_link_libraries(SDL2ImageTest
    SDL2::SDL2-static
    SDL2::SDL2main
    SDL2_image::SDL2_image-static
)

add_executable(SDL2TTFTest
    src/render_ttf.cpp
)
target_include_directories(SDL2TTFTest PRIVATE
    ${sdl2_image_SOURCE_DIR}/
    ${sdl2_ttf_SOURCE_DIR}/
)
target_link_libraries(SDL2TTFTest
    SDL2::SDL2-static
    SDL2::SDL2main
    SDL2_image::SDL2_image-static
    SDL2_ttf::SDL2_ttf-static
)