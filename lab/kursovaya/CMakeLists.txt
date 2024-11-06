cmake_minimum_required(VERSION 3.29)
project(kursovaya)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(kursovaya
        main.cpp
        Polynomial.cpp)

# Указываем директорию заголовочных файлов для цели `kursovaya`
target_include_directories(kursovaya PRIVATE .)
