cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 30)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(
    retouch
    LANGUAGES CXX
    VERSION 0.0.0.1
)

set(SRC_DIR  "${CMAKE_CURRENT_LIST_DIR}/src") 
set(EXTERNAL_SRC_DIR  "${SRC_DIR}/extern") 
set(CXXOPTS_SRC_DIR  "${EXTERNAL_SRC_DIR}/cxxopts") 
set(CXXOPTS_HPP  "${CXXOPTS_SRC_DIR}/cxxopts.hpp")
set(JSONXX_SRC_DIR  "${EXTERNAL_SRC_DIR}/jsonxx")
set(JSONXX_CC  "${JSONXX_SRC_DIR}/jsonxx.cc")
set(JSONXX_H  "${JSONXX_SRC_DIR}/jsonxx.h")
set(GLOB_SRC_DIR  "${EXTERNAL_SRC_DIR}/glob")
set(GLOB_HPP  "${GLOB_SRC_DIR}/glob.hpp")



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

if(NOT EXISTS ${GLOB_SRC_DIR})
    message(${GLOB_SRC_DIR} " NON esiste")
    file(MAKE_DIRECTORY ${GLOB_SRC_DIR})
endif()

if(NOT EXISTS ${GLOB_HPP})
    message(${GLOB_HPP} " NON esiste")
    execute_process(COMMAND wget -nv -O ${GLOB_HPP} "https://raw.githubusercontent.com/p-ranav/glob/master/single_include/glob/glob.hpp")
endif()

if(NOT EXISTS ${JSONXX_SRC_DIR})
    message(${JSONXX_SRC_DIR} " NON esiste")
    file(MAKE_DIRECTORY ${JSONXX_SRC_DIR})
endif()

if(NOT EXISTS ${JSONXX_CC})
    message(${JSONXX_CC} " NON esiste")
    execute_process(COMMAND wget -nv -O ${JSONXX_CC} "https://raw.githubusercontent.com/hjiang/jsonxx/master/jsonxx.cc")
endif()

if(NOT EXISTS ${JSONXX_H})
    message(${JSONXX_H} " NON esiste")
    execute_process(COMMAND wget -nv -O ${JSONXX_H} "https://raw.githubusercontent.com/hjiang/jsonxx/master/jsonxx.h")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB CXX_OPTS
  "${CXXOPTS_SRC_DIR}/*.hpp"
  "${GLOB_SRC_DIR}/*.hpp"
  "${JSONXX_SRC_DIR}/*.h"
  "${JSONXX_SRC_DIR}/*.cc"
  "${SRC_DIR}/*.hpp"
  "${SRC_DIR}/*.h"
  "${SRC_DIR}/*.cpp"
)

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
