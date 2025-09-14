cmake_minimum_required(VERSION 3.10)
project(dsa_project)

# Require C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(INCLUDE_PATHS 
    /home/rupesh-kumar-s/Downloads/asio-1.36.0/include 
    /home/rupesh-kumar-s/crow/include
)

add_executable(dsa_project main.cpp)

target_include_directories(dsa_project PUBLIC ${INCLUDE_PATHS})

# Link filesystem if using GCC < 9
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 9.0)
    target_link_libraries(dsa_project PRIVATE stdc++fs)
endif()

# Windows-specific networking libs (ignored on Ubuntu)
if (WIN32)
    target_link_libraries(dsa_project PRIVATE ws2_32 mswsock)
endif()
