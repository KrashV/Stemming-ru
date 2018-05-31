cmake_minimum_required(VERSION 3.0)
project(russian_stemming_algorythm)

file(GLOB_RECURSE SOURCE_FILES source/*.cpp src/*.h)

add_executable(russian_stemming_algorythm ${SOURCE_FILES})
# set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT russian_stemming_algorythm)