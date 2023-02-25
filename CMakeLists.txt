cmake_minimum_required(VERSION 3.24)
project(processes C)
set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS "-Wall -Wextra")

include_directories(${CMAKE_SOURCE_DIR}/Include)
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/Source)
add_executable(processes main.c
        ${SOURCE_DIR}/Logger.c
        ${SOURCE_DIR}/Queue.c
        ${SOURCE_DIR}/Reader.c Include/TermDefines.h Include/terminalPrint.h Source/terminalPrint.c Include/Analyzer.h Include/Printer.h Include/CpuStat.h Include/ProcStat.h)
