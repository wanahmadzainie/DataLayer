cmake_minimum_required(VERSION 3.28)
project(DataLayer)

set(CMAKE_CXX_STANDARD 20)

add_executable(DataLayer
        DataPump.cpp
        Parameters.h
        Matrix.h
        Matrix.cpp
        MemTrack.h
        MemTrack.cpp
        ProgramArguments.h
        ProgramArguments.cpp
        MatrixAllocation.h
        MatrixAllocation.cpp
        common.h
        common.cpp
        Persistence.h
        Persistence.cpp
        Offload.cpp
        MainTest.cpp
        InterfaceKernel.cpp
        InterfaceKernel.h
        InterfaceOrchestration.cpp
        InterfaceOrchestration.h
        luxyd-ai-ioctl.c
        luxyd-ai-ioctl.h
)
