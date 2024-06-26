set(ENGINE_DEPENDENCY_LIBS PARENT_SCOPE)
set(ENGINE_DEPENDENCY_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)

# sokol
list(APPEND ENGINE_DEPENDENCY_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/sokol)

# GLM
list(APPEND ENGINE_DEPENDENCY_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/glm)
 
# STB
list(APPEND ENGINE_DEPENDENCY_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/stb)

# Apple Frameworks
if(APPLE)
	if(NOT IOS)
		# Mac OS
		list(APPEND ENGINE_DEPENDENCY_LIBS "-framework Cocoa -framework QuartzCore -framework Metal -framework MetalKit")
	else()
		list(APPEND ENGINE_DEPENDENCY_LIBS "-framework Foundation -framework UIKit -framework Metal -framework MetalKit")
	endif()
endif()

if(LINUX)
	list(APPEND ENGINE_DEPENDENCY_LIBS "X11" "Xi" "Xcursor" "GL" "dl" "pthread")
endif()

if(MINGW OR MSYS)
	list(APPEND ENGINE_DEPENDENCY_LIBS "kernel32" "user32" "shell32" "d3d11" "dxgi")
endif()

# Android
if(ANDROID)
	list(APPEND ENGINE_DEPENDENCY_LIBS android log EGL)
endif()

# OpenGL
if("${GRAPHICS_BACKEND}" STREQUAL "GLCore")
	find_package(OpenGL REQUIRED)
	list(APPEND ENGINE_DEPENDENCY_LIBS OpenGL::opengl)
elseif("${GRAPHICS_BACKEND}" STREQUAL "GLES3" AND
		NOT ENGINE_WEB_PLATFORM)
	find_path(GLES3_INCLUDE_DIR GLES3/gl3.h HINTS ${ANDROID_NDK} REQUIRED)
	find_path(GLES3_LIBRARY libGLESv3.so HINTS ${GLES3_INCLUDE_DIR}/../lib REQUIRED)

	list(APPEND ENGINE_DEPENDENCY_LIBS ${GLES3_LIBRARY}/libGLESv3.so)
	list(APPEND ENGINE_DEPENDENCY_INCLUDE_DIRS ${GLES3_INCLUDE_DIR})
endif()

set(ENGINE_DEPENDENCY_LIBS ${ENGINE_DEPENDENCY_LIBS} PARENT_SCOPE)
set(ENGINE_DEPENDENCY_INCLUDE_DIRS ${ENGINE_DEPENDENCY_INCLUDE_DIRS} PARENT_SCOPE)
