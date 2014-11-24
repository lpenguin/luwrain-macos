# Luwrain native bindings for Mac OS X

## Building

### Dependencies
* XCode Command Line Tools
* [Gradle](http://www.gradle.org/) (for java build)
* [CMake](http://www.cmake.org/) (for native bindings)

### Java plugin (jar)
```
gradle build
```
Output will be in `build/libs/luwrain-macos.jar`
### Native library (dylib)
```
cd jni
mkdir -p build
cd build
cmake ..
make
```
Output will be in `jni/lib/libluwrainmacos.dylib`
