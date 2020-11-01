cmake_minimum_required(VERSION 3.16)
project(CinematecaPortuguesa)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

link_libraries(ws2_32 wsock32)

set(ADERENTES ./Aderentes)
set(CINEMATECA ./Cinemateca)
set(DATETIME ./DateTime)
set(EVENTO ./Evento)
set(SALA ./Sala)
set(UI ./UI)
set(UTILS ./Utils)

include_directories($(ADERENTES))
include_directories($(CINEMATECA))
include_directories($(DATETIME))
include_directories($(EVENTO))
include_directories($(SALA))
include_directories($(UI))
include_directories($(UTILS))

set(
        SOURCE_FILES
            ${UI}/UI.h
            ${UI}/UI.cpp

            ${UTILS}/utils.h
            ${UTILS}/utils.cpp
        
            ${ADERENTES}/Aderente.h
            ${ADERENTES}/Aderente.cpp

            ${CINEMATECA}/Cinemateca.h
            ${CINEMATECA}/Cinemateca.cpp

            ${DATETIME}/Date.h
            ${DATETIME}/Date.cpp
            ${DATETIME}/Time.h
            ${DATETIME}/Time.cpp

            ${EVENTO}/Evento.h
            ${EVENTO}/Evento.cpp

            ${SALA}/Sala.h
            ${SALA}/Sala.cpp

            main.cpp
)

add_executable(CinematecaPortuguesa ${SOURCE_FILES})