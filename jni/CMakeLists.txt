cmake_minimum_required(VERSION 2.8.4)
project(jnitest1native)

set(CMAKE_VERBOSE_MAKEFILE on )
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

FIND_LIBRARY(APP_SERVICES_LIBRARY ApplicationServices )
include_directories(${APP_SERVICES_LIBRARY}/Frameworks/SpeechSynthesis.framework/Headers)
include_directories(/System/Library/Frameworks/JavaVM.framework/Headers)

execute_process(COMMAND bash ${CMAKE_CURRENT_SOURCE_DIR}/native-gen.sh)

set(SOURCE_FILES src/sources/carbon_tts.cpp)
set(JNI_SOURCES ${SOURCE_FILES} src/sources/org_luwrain_os_speech_CarbonTts.cpp src/sources/org_luwrain_os_Terminal.cpp)


add_library(luwrainmacos SHARED ${JNI_SOURCES})
add_executable(talker ${SOURCE_FILES} src/sources/main.cpp)
include_directories(src/headers src/headers/generated)

target_link_libraries(luwrainmacos ${APP_SERVICES_LIBRARY})
target_link_libraries(talker ${APP_SERVICES_LIBRARY})


#macro(ADD_FRAMEWORK fwname appname)
#    find_library(FRAMEWORK_${fwname}
#        NAMES ${fwname}
#        PATHS ${CMAKE_OSX_SYSROOT}/System/Library
#        PATH_SUFFIXES Frameworks
#        NO_DEFAULT_PATH)

#    if( ${FRAMEWORK_${fwname}} STREQUAL FRAMEWORK_${fwname}-NOTFOUND)
#        MESSAGE(ERROR ": Framework ${fwname} not found")
#        find_library(FRAMEWORK_${fwname}
#            NAMES ${fwname}
#            PATHS ${CMAKE_OSX_SYSROOT}/System/Library/Frameworks/ApplicationServices.framework/
#            PATH_SUFFIXES Frameworks
#            NO_DEFAULT_PATH)
#        if( ${FRAMEWORK_${fwname}} STREQUAL FRAMEWORK_${fwname}-NOTFOUND)
#            MESSAGE(ERROR ": Framework ${fwname} not found. Trying to find in ApplictionServices.framework")
#        else()
#            TARGET_LINK_LIBRARIES(${appname} "${FRAMEWORK_${fwname}}/${fwname}")
#            MESSAGE(STATUS "Framework ${fwname} found at ${FRAMEWORK_${fwname}}")
#        endif()
#    else()
#        TARGET_LINK_LIBRARIES(${appname} "${FRAMEWORK_${fwname}}/${fwname}")
#        include_directories(${FRAMEWORK_${fwname}}/${fwname}/Headers)
#        MESSAGE(STATUS "Framework ${fwname} found at ${FRAMEWORK_${fwname}}")
#    endif()
#endmacro(ADD_FRAMEWORK)
