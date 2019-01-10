set(TARGET_NAME Settings)

#JsonCPP
hunter_add_package(jsoncpp)
find_package(jsoncpp CONFIG REQUIRED)

# Settings
add_library(${TARGET_NAME} STATIC "SettingManager.cpp")
target_link_libraries(${TARGET_NAME} jsoncpp_lib_static)