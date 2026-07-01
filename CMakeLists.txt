cmake_minimum_required(VERSION 3.10)
project(TEXTTV C)

set(CMAKE_C_STANDARD 11)
set(CURSES_NEED_WIDE TRUE)
find_package(Curses REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(CURL REQUIRED)
pkg_check_modules(CJSON REQUIRED libcjson)

add_executable(myapp application.c getpage.c)

target_include_directories(myapp PRIVATE ${CJSON_INCLUDE_DIRS})
target_link_libraries(myapp PRIVATE ${CURSES_LIBRARIES} CURL::libcurl ${CJSON_LIBRARIES})

