cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 20)

project("EngineWrapper")

include_directories(headers)

set(
  SOURCES 
  ./headers/args.h
  ./headers/engine.h
  ./headers/subject.h
  ./headers/wrapper.h
  ./src/main.cpp)

add_executable(exec ${SOURCES})

