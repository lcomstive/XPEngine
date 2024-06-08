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
	add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})
else()
	add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${HEADER_FILES})
	target_link_libraries(${PROJECT_NAME} AndroidAppGlue)
endif()

target_link_libraries(${PROJECT_NAME} XPEngine)

if(APPLE)
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