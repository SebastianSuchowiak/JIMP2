project(lab12)

target_include_directories(iterable PRIVATE ${iterable})

add_subdirectory_if_exists(treeiterators)
add_subdirectory_if_exists(tree)
add_subdirectory_if_exists(timerecorder)
add_subdirectory_if_exists(academiateacherhash)
add_subdirectory_if_exists(academiasequentialgenerator)
