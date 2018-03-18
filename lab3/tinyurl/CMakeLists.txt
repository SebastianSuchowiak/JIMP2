
project(tinyurl)

set(HEDEAR_FILES Tinyurl.h)
set(SOURCE_FILES TinyUrl.cpp)

add_library(libtinyurl STATIC ${SOURCE_FILES})
target_include_directories(libtinyurl PUBLIC .)

add_executable(tinyurl ${SOURCE_FILES} main.cpp)

target_link_libraries(tinyurl libtinyurl)

