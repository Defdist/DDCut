set(TARGET_NAME DDLogger)

# DDLogger
add_library(${TARGET_NAME} STATIC "Logger.cpp" "DDLogger.cpp")
target_compile_definitions(${TARGET_NAME} PRIVATE DD_LOGGER)

add_dependencies(${TARGET_NAME} DDCommon)
target_link_libraries(${TARGET_NAME} DDCommon)