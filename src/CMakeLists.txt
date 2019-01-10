cmake_minimum_required(VERSION 3.8)

include("${CMAKE_CURRENT_SOURCE_DIR}/CMake/HunterGate.cmake")
set(HUNTER_STATUS_DEBUG TRUE)
HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.23.49.tar.gz"
    SHA1 "777200954f3851322932f67c782fe92990b32ab2"
)

set(DDCUT_VERSION 3.0.0)
project(ddcut VERSION ${DDCUT_VERSION})

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
else(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -lstdc++fs -Wdeprecated-declarations")
    set(CMAKE_BUILD_TYPE Release)
endif(MSVC)

include(${CMAKE_CURRENT_SOURCE_DIR}/CMake/NodeJS.cmake)
nodejs_init()

add_definitions(-DDDCUT_VERSION="${DDCUT_VERSION}")

file(GLOB DDCUT_SRC
     "${CMAKE_CURRENT_SOURCE_DIR}/DDCutDaemon.cpp"
	 "${CMAKE_CURRENT_SOURCE_DIR}/Common/*.cpp"
	 "${CMAKE_CURRENT_SOURCE_DIR}/Files/*.cpp"
	 "${CMAKE_CURRENT_SOURCE_DIR}/Ghost/*.cpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/Logging/Logger.cpp"
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

if (WIN32)
    find_library(OS_SPECIFIC_LIBS setupapi)
else(WIN32)
    set(OS_SPECIFIC_LIBS "")
endif(WIN32)

hunter_add_package(minizip)
find_package(minizip CONFIG REQUIRED)

hunter_add_package(ZLIB)
find_package(ZLIB CONFIG REQUIRED)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(RestClient)
add_subdirectory(Settings)
add_subdirectory(DDUpdater)

add_nodejs_module(${PROJECT_NAME} ${DDCUT_SRC} ${OS_SPECIFIC_FILES} "${CMAKE_CURRENT_SOURCE_DIR}/NodeWrapper.cpp")
target_compile_definitions(${PROJECT_NAME} PRIVATE DDCUT_NODE)
target_link_libraries(${PROJECT_NAME} ${OS_SPECIFIC_LIBS} minizip::minizip ZLIB::zlib RestClient Settings)

set(TEST_TARGET_NAME DDCUT_TEST)
add_executable(${TEST_TARGET_NAME} ${DDCUT_SRC} "${CMAKE_CURRENT_SOURCE_DIR}/DDCutTest.cpp")
target_compile_definitions(${TEST_TARGET_NAME} PRIVATE DDCUT_TEST)
target_link_libraries(${TEST_TARGET_NAME} ${OS_SPECIFIC_LIBS} minizip::minizip ZLIB::zlib RestClient Settings)