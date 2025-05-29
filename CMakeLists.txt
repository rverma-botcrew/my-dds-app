cmake_minimum_required(VERSION 3.5)
project(my_dds_app LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# 1) Let CMake look under your custom DDS prefixes
list(APPEND CMAKE_PREFIX_PATH
  "$ENV{CYCLONE_INSTALL}"
  "$ENV{CXX_INSTALL}"
)
message(STATUS "CMAKE_PREFIX_PATH = ${CMAKE_PREFIX_PATH}")

# 2) Pull in Iceoryx C binding (installed via apt)
find_package(iceoryx_binding_c CONFIG REQUIRED)
# (if you also need iceoryx_posh directly, you can do:
#  find_package(iceoryx_posh CONFIG REQUIRED)
# )

# 3) Pull in CycloneDDS C++ wrapper
find_package(CycloneDDS-CXX CONFIG REQUIRED)

# 4) Where your IDL‐generated code lives
set(GEN_DIR "${CMAKE_CURRENT_BINARY_DIR}/gen")

# 5) Publisher
add_executable(publisher
  src/publisher.cpp
  ${GEN_DIR}/StringMessage.cpp
)
target_include_directories(publisher PRIVATE
  ${GEN_DIR}
  $ENV{CXX_INSTALL}/include
)
target_link_libraries(publisher PRIVATE
  iceoryx_binding_c::iceoryx_binding_c
  CycloneDDS-CXX::ddscxx
)

# 6) Subscriber
add_executable(subscriber
  src/subscriber.cpp
  ${GEN_DIR}/StringMessage.cpp
)
target_include_directories(subscriber PRIVATE 
  ${GEN_DIR}
  $ENV{CXX_INSTALL}/include
  )
target_link_libraries(subscriber PRIVATE
  iceoryx_binding_c::iceoryx_binding_c
  CycloneDDS-CXX::ddscxx
)
