cmake_minimum_required(VERSION 3.15)
project(Raffinement)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(Raffinement
        main.cpp

        Mesh/cell.cpp
        Mesh/cell.h

        Mesh/mesh.cpp
        Mesh/mesh.h

        Solver/solverfv.cpp
        Solver/solverfv.h

        Solver/Burgers/solverburgers.cpp
        Solver/Burgers/solverburgers.h
        Solver/Burgers/LaxFriedrichs/solverburgerslaxfriedrichs.cpp
        Solver/Burgers/LaxFriedrichs/solverburgerslaxfriedrichs.h
        Solver/Burgers/Godunov/solverburgersgodunov.cpp
        Solver/Burgers/Godunov/solverburgersgodunov.h

        Solver/Linear/solverlinear.cpp
        Solver/Linear/solverlinear.h
        Solver/Linear/Upwind/solverlinearupwind.cpp
        Solver/Linear/Upwind/solverlinearupwind.h
        Solver/Linear/LaxFriedrichs/solverlinearlaxfriedrichs.cpp
        Solver/Linear/LaxFriedrichs/solverlinearlaxfriedrichs.h)
