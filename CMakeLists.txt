# ########## Project setup ##########
CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
cmake_policy(SET CMP0048 NEW)
PROJECT(UUSHT VERSION 0.0)

PROJECT(UUSHT)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8.12)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR})

INCLUDE(./dependencies.cmake)

SET(UUSHT_executable_SRCS
  ${PROJECT_SOURCE_DIR}/src/main.c
  ${PROJECT_SOURCE_DIR}/src/serverstate.c
  ${PROJECT_SOURCE_DIR}/src/db.c
  ${PROJECT_SOURCE_DIR}/src/sha2.c
  ${PROJECT_SOURCE_DIR}/src/http.c
  ${PROJECT_SOURCE_DIR}/src/sockutil.c
  ${PROJECT_SOURCE_DIR}/src/strutil.c
)

SET_SOURCE_FILES_PROPERTIES(
  ${PROJECT_SOURCE_DIR}/src/sha2.c
  PROPERTIES COMPILE_FLAGS -fno-strict-aliasing)

include_directories(${PROJECT_BINARY_DIR})
include_directories(${PROJECT_INCLUDE_DIR})
# actual target:
ADD_EXECUTABLE(UUSHT ${UUSHT_executable_SRCS})

TARGET_LINK_LIBRARIES(UUSHT
  ${CURL_LIBRARIES}
  ${LIBPTHREAD_LIBRARIES}
  ${SQLITE_LIBRARIES}
  ${LibreSSL_LIBRARIES}
  -lbsd
)

#ADD_CUSTOM_COMMAND(
#  TARGET UUSHT
#  POST_BUILD
#  COMMAND cp -r ../intrinsic-assets ../build
#)

# add install target:
INSTALL(TARGETS UUSHT DESTINATION bin)
