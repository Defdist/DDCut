set(TARGET_NAME DDUpdater)

hunter_add_package(ZeroMQ)

find_package(ZeroMQ CONFIG REQUIRED)

add_subdirectory(Update-Installer)

add_executable(${TARGET_NAME} "Main.cpp" "DDUpdater.cpp")
include_directories(../RestClient)

add_dependencies(${TARGET_NAME} RestClient)
target_link_libraries(${TARGET_NAME} RestClient ZeroMQ::libzmq-static)