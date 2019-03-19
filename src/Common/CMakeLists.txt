set(TARGET_NAME DDCommon)

# DDCommon
add_library(${TARGET_NAME} STATIC "FileUtility.cpp" "LockUtility.cpp" "OSUtility.cpp" "ThreadManager.cpp")