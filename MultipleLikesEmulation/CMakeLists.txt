cmake_minimum_required(VERSION 3.5)

project(MultipleLikesEmulation LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(MultipleLikesEmulation
    main.cpp
    user.hpp user.cpp
    poll.hpp poll.cpp
    answer.hpp answer.cpp
    database.hpp database.cpp)
