cmake_minimum_required(VERSION 3.5)

project(retouch LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB CXX_OPTS  "./extern/cxxopts/include/*.hpp")

include(
    GNUInstallDirs
)

include_directories(
    ./extern/cxxopts/include
)

add_custom_target(
    headers
    SOURCES ${CXX_OPTS}
)

add_executable(
    retouch
    ${headers}
    main.cpp
    opzioni.h opzioni.cpp
)

install(TARGETS retouch
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
