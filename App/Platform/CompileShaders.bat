@echo off

set DIR=%~dp0..
set SHADERC=%DIR%/../Engine/Dependencies/sokol-tools-bin/bin/win32/sokol-shdc.exe
set SHADER_LANGS=glsl430:glsl300es:hlsl5:metal_macos:metal_ios:metal_sim

if not exist %DIR%\ShaderCache mkdir %DIR%\ShaderCache
if not exist %DIR%\ShaderCache\Shaders mkdir %DIR%\ShaderCache\Shaders

call %SHADERC% --input %DIR%/Assets/Shaders/triangle.glsl --output %DIR%/ShaderCache/Shaders/triangle.h -l %SHADER_LANGS% -e msvc
