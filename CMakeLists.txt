cmake_minimum_required(VERSION 3.5)

project(
    retouch
    LANGUAGES CXX
    VERSION 0.0.0.1
)

set(SRC_DIR  "${CMAKE_CURRENT_LIST_DIR}/src") 
set(EXTERNAL_SRC_DIR  "${SRC_DIR}/extern") 
set(CXXOPTS_SRC_DIR  "${EXTERNAL_SRC_DIR}/cxxopts") 
set(CXXOPTS_HPP  "${CXXOPTS_SRC_DIR}/cxxopts.hpp") 

if(NOT EXISTS ${EXTERNAL_SRC_DIR})
    message(${EXTERNAL_SRC_DIR} " NON esiste")
    file(MAKE_DIRECTORY ${EXTERNAL_SRC_DIR})
endif()

if(NOT EXISTS ${CXXOPTS_SRC_DIR})
    message(${CXXOPTS_SRC_DIR} " NON esiste")
    file(MAKE_DIRECTORY ${CXXOPTS_SRC_DIR})
endif()

if(NOT EXISTS ${CXXOPTS_HPP})
    message(${CXXOPTS_HPP} " NON esiste")
    execute_process(COMMAND wget -nv -O ${CXXOPTS_HPP} "https://raw.githubusercontent.com/jarro2783/cxxopts/master/include/cxxopts.hpp")
endif()


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB CXX_OPTS  "${CXXOPTS_SRC_DIR}/*.hpp")

include(
    GNUInstallDirs
)

include_directories(
    ${CXXOPTS_SRC_DIR}
)

add_custom_target(
    headers
    SOURCES ${CXX_OPTS}
)

add_executable(
    retouch
    ${headers}
    main.cpp
)

install(TARGETS retouch
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
