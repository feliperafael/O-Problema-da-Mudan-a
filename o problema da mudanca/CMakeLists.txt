cmake_minimum_required(VERSION 3.10)
project(mudanca)

include_directories(src)


file(GLOB_RECURSE FONTES "src/*.cpp")
add_executable(mudanca ${FONTES})    
