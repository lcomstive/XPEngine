#!/bin/bash

DIR=$(dirname "$0")/..
UNAME=$(uname -s)
ARCH=$(uname -m)
SHADER_LANGS=glsl430:glsl300es:hlsl5:metal_macos:metal_ios:metal_sim

if [[ $(uname -s) == 'Darwin' ]]; then
	if [[ $(uname -m) == 'arm64' ]]; then
		SHADERC=$DIR/../Engine/Dependencies/sokol-tools-bin/bin/osx_arm64/sokol-shdc
	else
		SHADERC=$DIR/../Engine/Dependencies/sokol-tools-bin/bin/osx/sokol-shdc
	fi
else
	SHADERC=$DIR/../Engine/Dependencies/sokol-tools-bin/bin/linux/sokol-shdc
fi

mkdir -p $DIR/ShaderCache/Shaders

$SHADERC --input $DIR/Assets/Shaders/triangle.glsl --output $DIR/ShaderCache/Shaders/triangle.h -l $SHADER_LANGS
