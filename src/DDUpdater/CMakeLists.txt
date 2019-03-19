set(TARGET_NAME DDUpdater)

#hunter_add_package(ZeroMQ)

#find_package(ZeroMQ CONFIG REQUIRED)

add_subdirectory(Update-Installer)

add_library(${TARGET_NAME} SHARED "DDUpdater.cpp" "tinyxml2.cpp")
target_compile_definitions(${TARGET_NAME} PRIVATE DD_UPDATER)

add_dependencies(${TARGET_NAME} RestClient DDCommon DDLogger)
target_link_libraries(${TARGET_NAME} RestClient DDCommon DDLogger)