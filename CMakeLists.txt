cmake_minimum_required(VERSION 3.8)
project(robowrestling-software C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BUILD_FLAGS "-Wuninitialized -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${BUILD_FLAGS}")

#option(BUILD_TESTS "BUILD_TESTS" ON)

# Add custom cmake finds
message(${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include_directories(strategy/include)
add_subdirectory(strategy)

find_package(SFML 2 COMPONENTS graphics window system REQUIRED)
if(SFML_FOUND)
  message(${SFML_INCLUDE_DIR})
  include_directories(SYSTEM ${SFML_INCLUDE_DIR})

  include_directories(simulator/include)
  add_subdirectory(simulator)
endif()



