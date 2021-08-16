cmake_minimum_required(VERSION 3.6)

project(MatrixOperations)
set(SOURCE_DIR ${PROJECT_SOURCE_DIR})
set(DATFILES_DIR "${PROJECT_SOURCE_DIR}/DatFiles")

file(GLOB SOURCE_FILES
        "${SOURCE_DIR}/*.cpp"
        "${SOURCE_DIR}/*.h"
    )
add_subdirectory(${DATFILES_DIR})
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
