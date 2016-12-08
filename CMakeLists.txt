cmake_minimum_required(VERSION 3.5)

project(LightGBMJni)

set(CMAKE_CXX_STANDARD 11)

include_directories(src/main/native/include
                   $ENV{JAVA_HOME}/include
                   $ENV{JAVA_HOME}/include/linux
                   )
set(SOURCE_FILES
    src/main/native/include/ILightGBMJava.h
    src/main/native/include/c_api.h
    src/main/native/include/handle.h
    src/main/native/lightgbmJava.cpp
   )

add_library(LightGBMJni SHARED ${SOURCE_FILES})
target_link_libraries(LightGBMJni _lightgbm)