cmake_minimum_required(VERSION 3.10)
project(hex)

IF(NOT CMAKE_BUILD_TYPE)
  SET(CAMKE_BUILD_TYPE Release)
ENDIF()

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
aux_source_directory(src DIR_SRCS)
set(HEX_MATH ${DIR_SRCS})

include_directories(
${PROJECT_SOURCE_DIR}/inc
)
link_directories(
${PROJECT_SOURCE_DIR}/lib
)

add_executable(${PROJECT_NAME} ${HEX_MATH})
target_link_libraries(${PROJECT_NAME} sid)
