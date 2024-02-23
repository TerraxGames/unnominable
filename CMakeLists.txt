cmake_minimum_required(VERSION 3.28.0)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

add_compile_options(-Wall)

project(unnominable
        VERSION 0.1.0.0)
add_executable(${PROJECT_NAME}
        src/log.cpp
        src/log.hpp
        src/main.cpp
        src/main.hpp
        src/math.hpp
        src/objects.cpp
        src/objects.hpp
        src/render.cpp
        src/render.hpp
        src/shader.cpp
        src/shader.hpp
        src/texture.cpp
        src/texture.hpp
        src/types.cpp
        src/types.hpp
        src/util.cpp
        src/util.hpp)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/sdl2)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_gfx REQUIRED)
find_package(SDL2_ttf REQUIRED)

add_library(GLAD STATIC "${CMAKE_SOURCE_DIR}/lib/glad/src/gl.c")
include_directories("${CMAKE_SOURCE_DIR}/lib/glad/include/")

include_directories("${CMAKE_SOURCE_DIR}/lib/termstylist/include/")

include_directories("${CMAKE_SOURCE_DIR}/lib/include/")

target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::Main SDL2::Image SDL2::GFX SDL2::TTF GLAD)