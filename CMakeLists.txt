cmake_minimum_required(VERSION 3.16)
project(vatsim-manager)

set(CMAKE_CXX_STANDARD 14)

add_executable(vatsim-manager main.cpp utils.cpp utils.h download.cpp download.h clientstate.cpp clientstate.h global.h)

find_package(PkgConfig)
pkg_check_modules(libcurl REQUIRED IMPORTED_TARGET libcurl>=7.68.0)
pkg_check_modules(jsoncpp REQUIRED IMPORTED_TARGET jsoncpp>=1.7.4)
target_link_libraries(vatsim-manager PUBLIC PkgConfig::libcurl PkgConfig::jsoncpp)