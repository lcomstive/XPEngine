# Shader Compilation
file(GLOB_RECURSE SHADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Assets/Shaders/*.glsl)
set(SHADER_HEADERS)

foreach(shader ${SHADER_FILES})
	string(REGEX REPLACE "[.]glsl$" ".h" header ${shader})
	string(REGEX REPLACE "Assets/Shaders" "ShaderCache/Shaders" header ${header})
	list(APPEND SHADER_HEADERS ${header})
endforeach()

set(SHADER_LANGS "glsl430:glsl300es:hlsl5:metal_macos:metal_ios:metal_sim")
set(SHADER_COMPILER ${CMAKE_CURRENT_SOURCE_DIR}/../Engine/Dependencies/sokol-tools-bin/bin)
if(WIN32)
	set(SHADER_COMPILER ${SHADER_COMPILER}/win32/sokol-shdc.exe)
elseif(APPLE)
	if(CMAKE_SYSTEM_PROCESSOR STREQUAL "arm64")
		set(SHADER_COMPILER ${SHADER_COMPILER}/osx_arm64/sokol-shdc)
	else()
		set(SHADER_COMPILER ${SHADER_COMPILER}/osx/sokol-shdc)
	endif()
else()
	set(SHADER_COMPILER ${SHADER_COMPILER}/linux/sokol-shdc)
endif()

foreach(shader header IN ZIP_LISTS SHADER_FILES SHADER_HEADERS)
	add_custom_command(OUTPUT ${header} ${header}.fake # Look for a fake file so shaders are ALWAYS recompiled
		COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_SOURCE_DIR}/ShaderCache/Shaders
		COMMAND ${SHADER_COMPILER} --input "${shader}" --output "${header}" -l ${SHADER_LANGS}
	)
endforeach()

add_custom_target(AppShaders SOURCES ${SHADER_HEADERS})

