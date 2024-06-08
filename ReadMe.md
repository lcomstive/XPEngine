# XPEngine
Basic game engine (to be)

# Compiling
Requirements:
 - [CMake](https://cmake.org/)
 - A compiler (e.g. Visual Studio, XCode, GCC, Clang)
 - Android: JDK, Android SDK, Android NDK
	- Environment variables for `ANDROID_SDK` and `ANDROID_NDK` are required

## Desktop platforms
### CMake GUI
 - Clone this repo w/ submodules (through a GitHub client or `git clone --recurse-submodules https://...`)
 - Open `cmake`
 - Set `where is the source code` to the cloned repository directory
 - Set `where to build the binaries` to your directory of choice (e.g. `XPEngine/build`)
 - Press `Configure` (*bottom left*)
 - You will be asked to specify a generator, choose your preferred/installed
 - Press `Generate` (*next to 'Configure'*)
 - Press `Open Project` (*next to 'Generate'*)
 - Build the `App` project inside your IDE

### Command line
```bash
git clone --recurse-submodules https://github.com/lcomstive/XPEngine
cd XPEngine
cmake -B build .
cmake --build build
```

Output file(s) will be in `build/bin/<config>/`

## Android
### Android Studio
 - *"Open File or Project"*
 - Open `App/Platform/Android` directory
 - Build, or run on your selected device

### Command line
```bash
git clone --recurse-submodules https://github.com/lcomstive/XPEngine
cd XPEngine/App/Platform/Android
./gradlew build
```

APK files will be in `App/Platform/Android/build/outputs/apk/<config>/`

> `TODO: Figure out how to sign an APK`

## iOS
### XCode
 - Use either the `ios` (*device*) or `ios-sim` (*simulator*) CMake preset with the `Xcode` generator (e.g. `cmake --preset ios-sim -B build`)
 - Open the Xcode project
 - Build and run in simulated iOS device

### Command line
#### Building
```bash
git clone --recurse-submodules https://github.com/lcomstive/XPEngine
cd XPEngine
cmake --preset ios-sim -B build # or `--preset ios` if intended to run on physical device
cd build

# Build binary
xcodebuild -scheme App build
```

.app file will be in `build/bin/<config>/`

#### Running on simulator
```bash
cd XPEngine/build

# Boot device
xcrun simctl boot "<simulator name>"

# Install on device
xcrun simctl install ./bin/<config>/App.app

# Run app on device
xcrun simctl launch booted com.madissia.App
```

> `TODO: Figure out how to sign an iOS app and generate .ipa`

## Web
```bash
cd XPEngine

# Get Emscripten
git clone https://github.com/emscripten-core/emsdk
cd emsdk
./emsdk install latest && ./emsdk activate latest
cd ..

# Build XPEngine
export EMSDK=./emsdk
cmake --preset web -B build .
cmake --build build # defaults to debug, set to release by appending `--config Release`

# To quickly host you can use
./emsdk/upstream/emscripten/emrun ./build/bin/Debug/App.html
```

# Credit & Third Party
| Name | License |
|:----:|:--------|
| [Sokol](https://github.com/floooh/sokol) | [zlib/libpng](https://github.com/floooh/sokol/blob/master/LICENSE) |

# License
This software is released under the [MIT License](./License.md)