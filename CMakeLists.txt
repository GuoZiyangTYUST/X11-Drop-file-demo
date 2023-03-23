cmake_minimum_required(VERSION 3.5)

project(x11Test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(X11 REQUIRED)

#add all .c .h .cpp .hpp files to SOURCES
file(GLOB_RECURSE SOURCES Src/*.c Src/*.h Src/*.cpp Src/*.hpp)

add_executable(X11DropFile ${SOURCES})

target_link_libraries(X11DropFile ${X11_LIBRARIES})
