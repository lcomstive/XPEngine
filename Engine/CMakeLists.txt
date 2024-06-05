project(XPEngine)

add_subdirectory(Dependencies)

file(GLOB_RECURSE SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.c" "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp")
file(GLOB_RECURSE HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Include/Engine/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/Include/Engine/*.hpp")

if(NOT BUILD_SHARED_LIBS)
	add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES})
else()
	add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${HEADER_FILES})

	target_compile_definitions(${PROJECT_NAME} PUBLIC  BUILD_SHARED_LIBS)
	target_compile_definitions(${PROJECT_NAME} PRIVATE ENGINE_EXPORT_DLL)
endif()

set_target_properties(
	${PROJECT_NAME} PROPERTIES
	VERSION ${VERSION_STRING}
)

# Group source files inside IDE
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/Source"  PREFIX "Source"  FILES ${SOURCE_FILES})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/Include" PREFIX "Include" FILES ${HEADER_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC
	Include
	${ENGINE_DEPENDENCY_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME} PUBLIC ${ENGINE_DEPENDENCY_LIBS})