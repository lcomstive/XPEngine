project(App)

file(GLOB_RECURSE SOURCE_FILES Source/*.cpp)
file(GLOB_RECURSE HEADER_FILES Include/*.hpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(${PROJECT_NAME} XPEngine)