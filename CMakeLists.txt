cmake_minimum_required(VERSION 3.15)
project(Raffinement)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(Raffinement
        cell.cpp
        cell.h
        cellule.cpp
        cellule.h
        maillage.cpp
        maillage.h
        main.cpp
        mesh.cpp
        mesh.h)
