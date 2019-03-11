cmake_minimum_required(VERSION 3.12)
project(BookClubServer)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost 1.69 REQUIRED COMPONENTS system)

set(SOURCE_FILES main.cpp BookClubEntity.hpp json.hpp md5.hpp util.hpp validate.hpp DatabaseManager.cpp DatabaseManager.h BookClubMannger.cpp BookClubMannger.h BookClubConfig.h)

INCLUDE_DIRECTORIES(
        ${CMAKE_SOURCE_DIR}/ormpp
        ${CMAKE_SOURCE_DIR}/iguana
        ${CMAKE_SOURCE_DIR}/cinatra
)

add_executable(BookClubServer ${SOURCE_FILES})

target_link_libraries(BookClubServer mysqlclient sqlite3 pq ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${EXTRA_LIB} ws2_32 wsock32 -lstdc++fs)