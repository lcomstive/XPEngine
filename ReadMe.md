# XPEngine

# Compiling
## Desktop platforms

## Android
### Android Studio
 - *"Open File or Project"*
 - Open `App/Platform/Android` directory

### Command line
 - `cd App/Platform/Android`
 - `./gradlew build`
 - APK files will be in `App/Platform/Android/build/outputs/apk/<config>`

> One liner:
> ```git clone --recurse-submodules https://github.com/lcomstive/XPEngine && cd XPEngine/App/Platform/Android && ./gradlew build```

## iOS
### XCode
 - Use either the `ios` (*device*) or `ios-sim` (*simulator*) CMake preset with the `Xcode` generator (e.g. `cmake --preset ios-sim -B build`)
 - Open the Xcode project
 - Build and run in simulated iOS device

### Command line
> Use either the `ios` (*device*) or `ios-sim` (*simulator*) CMake preset with the `Xcode` generator (e.g. `cmake --preset ios-sim -B build`)

Building
```bash
git clone --recurse-submodules https://github.com/lcomstive/XPEngine
cd XPEngine
cmake --preset ios-sim -B build
cd build

# Build binary
xcodebuild -scheme App build
```

Running on simulator
```bash
cd XPEngine/build

# Boot device
xcrun simctl boot "<simulator name>"

# Install on device
xcrun simctl install ./bin/App.app

# Run app on device
xcrun simctl launch booted com.madissia.App
```

# Credit & Third Party
| Name | License |
|:----:|:--------|
| [Sokol](https://github.com/floooh/sokol) | [zlib/libpng](https://github.com/floooh/sokol/blob/master/LICENSE) |

# License
This software is released under the [MIT License](./License.md)