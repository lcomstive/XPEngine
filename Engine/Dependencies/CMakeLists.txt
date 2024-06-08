set(ENGINE_DEPENDENCY_LIBS PARENT_SCOPE)
set(ENGINE_DEPENDENCY_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)

# sokol
list(APPEND ENGINE_DEPENDENCY_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/sokol)

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

set(ENGINE_DEPENDENCY_LIBS ${ENGINE_DEPENDENCY_LIBS} PARENT_SCOPE)
set(ENGINE_DEPENDENCY_INCLUDE_DIRS ${ENGINE_DEPENDENCY_INCLUDE_DIRS} PARENT_SCOPE)
