include(./Platform/CompileShaders.cmake)

# Application
project(App)

if(APPLE)
	enable_language(OBJC)
endif()

file(GLOB_RECURSE SOURCE_FILES Source/*.cpp)
file(GLOB_RECURSE HEADER_FILES Include/*.hpp)

if(APPLE)
	file(GLOB_RECURSE OBJC_FILES Source/*.m Source/*.mm)
	list(APPEND SOURCE_FILES ${OBJC_FILES})
endif()

if(NOT ANDROID)
	add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES} ${SHADER_HEADERS} ${SHADER_FILES})
else()
	add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${HEADER_FILES} ${SHADER_HEADERS} ${SHADER_FILES})
	target_link_libraries(${PROJECT_NAME} AndroidAppGlue)
endif()

add_dependencies(${PROJECT_NAME} AppShaders)
target_link_libraries(${PROJECT_NAME} XPEngine)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ShaderCache)

set(APP_RESOURCES_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

if(APPLE)
	set(APP_RESOURCES_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.app/Contents/Resources)

	# Configure Mac OS app bundle
	set_target_properties(
		${PROJECT_NAME} PROPERTIES
		BUNDLE TRUE
		MACOSX_BUNDLE TRUE
		MACOSX_BUNDLE_GUI_IDENTIFIER "com.madissia.${PROJECT_NAME}"
		MACOSX_BUNDLE_BUNDLE_NAME "XPApp"
		MACOSX_BUNDLE_COPYRIGHT "© 2024 Madissia Technologies"
		MACOSX_BUNDLE_EXECUTABLE_NAME ${PROJECT_NAME}
		MACOSX_BUNDLE_BUNDLE_VERSION ${VERSION_STRING_LONG}
		MACOSX_BUNDLE_SHORT_VERSION_STRING ${VERSION_STRING}
		MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Platform/Apple.plist.in
	)
endif()

if(ENGINE_WEB_PLATFORM)
	set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "index")
endif()

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND echo Copying assets to output folder
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_CURRENT_SOURCE_DIR}/Assets ${APP_RESOURCES_DIR}/Assets

	# Shaders are compiled into the source code, don't need raw shaders copied
	COMMAND ${CMAKE_COMMAND} -E remove_directory ${APP_RESOURCES_DIR}/Assets/Shaders
)

# Group source files inside IDE
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/Source"  PREFIX "Source" FILES ${SOURCE_FILES})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/Include" PREFIX "Include" FILES ${INCLUDE_FILES})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/Assets/Shaders" PREFIX "Shaders" FILES ${SHADER_FILES})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/ShaderCache/Shaders" PREFIX "Shaders/Cached" FILES ${SHADER_HEADERS})