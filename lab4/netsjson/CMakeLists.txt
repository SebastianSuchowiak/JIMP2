
project(simplejson)

set(HEDEAR_FILES SimpleJson.h)
set(SOURCE_FILES SimpleJson.cpp)

add_library(libsimplejson STATIC ${SOURCE_FILES})
target_include_directories(libsimplejson PUBLIC .)

add_executable(simplejson ${SOURCE_FILES} main.cpp)

target_link_libraries(simplejson libsimplejson)