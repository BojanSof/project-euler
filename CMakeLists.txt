cmake_minimum_required(VERSION 3.18)

project(
    "ProjectEuler"
    VERSION 0.1
    DESCRIPTION "Solutions to Project Euler problems"
    LANGUAGES CXX
)

list(APPEND CMAKE_MODULE_PATH
    "${CMAKE_CURRENT_LIST_DIR}/cmake"
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY  ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${PROJECT_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(problem-31-coin-sums)
add_subdirectory(problem-182-rsa-encryption)
add_subdirectory(problem-869-prime-guessing)
