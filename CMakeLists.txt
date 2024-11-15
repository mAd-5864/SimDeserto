cmake_minimum_required(VERSION 3.26)
project(SimDeserto)

set(CMAKE_CXX_STANDARD 17)

add_executable(SimDeserto src/main.cpp
        src/Utils.cpp
        src/Deserto.cpp
        src/Caravana.cpp
        src/Cidade.cpp
        src/Barbaro.cpp
        src/Item.cpp
        include/Utils.h
        include/Barbaro.h
        include/Caravana.h
        include/Cidade.h
        include/Deserto.h
        include/Item.h)
