cmake_minimum_required(VERSION 3.15)

project(svg-parser VERSION 0.1 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_FLAGS "-O3 -march=native -mtune=native -Wall -Wextra -Werror -flto")

#add_compile_options(-fsanitize=address)
#add_link_options(-fsanitize=address)


set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")

set(SOURCES
    src/main.c
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR})
