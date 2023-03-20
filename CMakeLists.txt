cmake_minimum_required(VERSION 3.20)

project(SDL2Test)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

add_executable(SDL2Test
    06_extension_libraries_and_loading_other_image_formats/06_extension_libraries_and_loading_other_image_formats.cpp
)
target_include_directories(SDL2Test PRIVATE
    ${SDL2_INCLUDE_DIRS}
)
target_link_libraries(SDL2Test
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
)
