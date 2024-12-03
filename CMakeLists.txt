cmake_minimum_required(VERSION 3.26)
project(SimDeserto LANGUAGES CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ensure UTF-8 input and output encoding for GCC/Clang
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-finput-charset=UTF-8 -fexec-charset=UTF-8)
endif ()

# Ensure proper encoding for MSVC
if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_compile_options(/utf-8)
endif ()

add_executable(SimDeserto src/main.cpp
        src/Utils.cpp
        src/Deserto.cpp
        src/Caravana.cpp
        src/Cidade.cpp
        src/Barbaro.cpp
        src/Buffer.cpp
        src/Item.cpp
        include/Buffer.h
        include/Utils.h
        include/Barbaro.h
        include/Caravana.h
        include/Cidade.h
        include/Deserto.h
        include/Item.h
)
