cmake_minimum_required (VERSION 3.8)

project ("IdGenerator")

add_executable (IdGenerator "IdGenerator.cpp" "IdGenerator.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET IdGenerator PROPERTY CXX_STANDARD 20)
endif()

