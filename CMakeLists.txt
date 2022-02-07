cmake_minimum_required(VERSION 3.16)
project(vatsim-mgr)

set(CMAKE_CXX_STANDARD 14)

add_executable(vatsim-mgr main.cpp utils.cpp utils.h download.cpp download.h)

find_package(PkgConfig)
pkg_check_modules(libcurl REQUIRED IMPORTED_TARGET libcurl>=7.68.0)
target_link_libraries(vatsim-mgr PUBLIC PkgConfig::libcurl)