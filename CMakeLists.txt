cmake_minimum_required(VERSION 2.8)
project( SLA_Printer )
IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Release)
ENDIF()

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(${PROJECT_SOURCE_DIR}/include)

find_package(OpenCV REQUIRED )
add_executable(main src/main.cpp)

target_link_libraries(main ${OpenCV_LIBS} )
