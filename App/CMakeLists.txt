project(App)
enable_language(OBJC)

file(GLOB_RECURSE SOURCE_FILES Source/*.cpp)
file(GLOB_RECURSE HEADER_FILES Include/*.hpp)

if(APPLE)
	file(GLOB_RECURSE OBJC_FILES Source/*.m Source/*.mm)
	list(APPEND SOURCE_FILES ${OBJC_FILES})
endif()

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(${PROJECT_NAME} XPEngine)