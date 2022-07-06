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

include_directories(openings/include)
add_subdirectory(openings)


find_package(SFML 2 COMPONENTS graphics window system REQUIRED)
if(SFML_FOUND)
  message(${SFML_INCLUDE_DIR})
  include_directories(SYSTEM ${SFML_INCLUDE_DIR})

  include_directories(simulator/include)
  add_subdirectory(simulator)
endif()
find_package(OpenGL REQUIRED)

add_subdirectory(imgui)
add_subdirectory(graphics)


include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
