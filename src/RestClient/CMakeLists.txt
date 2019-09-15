set(TARGET_NAME RestClient)

# OpenSSL
#if (NOT "$ENV{OPENSSL_ROOT_DIR}" STREQUAL "")
#	set(OPENSSL_ROOT_DIR $ENV{OPENSSL_ROOT_DIR})
#endif()
#set(OPENSSL_USE_STATIC_LIBS ON)

#include(../CMake/FindOpenSSL.cmake)
#include_directories(${OPENSSL_INCLUDE_DIR})

# OpenSSL
hunter_add_package(OpenSSL)
find_package(OpenSSL REQUIRED)

message("OPENSSL_FOUND : " ${OPENSSL_FOUND})
message("OPENSSL_INCLUDE_DIR : " ${OPENSSL_INCLUDE_DIR})
message("OPENSSL_CRYPTO_LIBRARY : " ${OPENSSL_CRYPTO_LIBRARY})
message("OPENSSL_SSL_LIBRARY : " ${OPENSSL_SSL_LIBRARY})
message("OPENSSL_LIBRARIES : " ${OPENSSL_LIBRARIES})
message("OPENSSL_VERSION : " ${OPENSSL_VERSION})
message("OPENSSL_USE_STATIC_LIBS: ${OPENSSL_USE_STATIC_LIBS}")


# ASIO
add_definitions(-DASIO_STANDALONE)
include_directories(asio/asio/include)

#JsonCPP
hunter_add_package(jsoncpp)
find_package(jsoncpp CONFIG REQUIRED)


# RestClient
add_library(${TARGET_NAME} STATIC "RestClient.cpp" "DDRestClient.cpp" "FileDownloader.cpp")
target_compile_definitions(${TARGET_NAME} PRIVATE REST_CLIENT)
target_link_libraries(${TARGET_NAME} OpenSSL::Crypto OpenSSL::SSL jsoncpp_lib_static)