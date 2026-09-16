cmake_minimum_required(VERSION 3.16)
project(boolean_retrieval_engine VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(boolean_retrieval_engine
    src/main.cpp
    src/BooleanQuery.cpp
    src/DocumentReader.cpp
    src/IncidenceMatrix.cpp
    src/InvertedIndex.cpp
    src/LinkedList.cpp
    src/TextProcessor.cpp
)

target_include_directories(boolean_retrieval_engine PRIVATE include)

if (MSVC)
    target_compile_options(boolean_retrieval_engine PRIVATE /W4)
else()
    target_compile_options(boolean_retrieval_engine PRIVATE -Wall -Wextra -Wpedantic)
endif()
