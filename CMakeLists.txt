cmake_minimum_required(VERSION 3.17)
project(dge)

include(FetchContent)
include(ExternalProject)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_VERBOSE_MAKEFILE TRUE)

# -- 3rd party dependencies --
include(cmake/ExternalProjects.cmake)

include_directories(

  ${glfw_INCLUDE_DIR}
  ${CMAKE_SOURCE_DIR}

  )

add_library(dge STATIC
  dge/dge.cpp
  dge/dge_scene/dge_scene.cpp
  dge/dge_system/dge_system.cpp
  dge/dge_system/glad/glad.c
  )

target_include_directories(dge PRIVATE
  dge/dge_system
  )

add_executable(dgesample0
  examples/dge_system/example0.cpp
  )

add_executable(dgesample1
  examples/dge_system/example1.cpp
  )


add_dependencies(dge glfw #[[glm]])
add_dependencies(dgesample0 dge)
add_dependencies(dgesample1 dge)

target_include_directories(dgesample0 PRIVATE
  dge/dge_scene
  dge/dge_system
  )

target_include_directories(dgesample1 PRIVATE
  dge/dge_scene
  dge/dge_system
  )


target_link_libraries(dge PRIVATE
  ${glfw_LIBRARY_DIR}/libglfw3.a
  )

target_link_libraries(dgesample0 PRIVATE
  ${CMAKE_BINARY_DIR}/libdge.a
  ${glfw_LIBRARY_DIR}/libglfw3.a
  )

target_link_libraries(dgesample1 PRIVATE
  ${CMAKE_BINARY_DIR}/libdge.a
  ${glfw_LIBRARY_DIR}/libglfw3.a
  )


message(STATUS ${CMAKE_BINARY_DIR}/lib/libcpr.a)
  #[[add_custom_command(
  TARGET dgesample0
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/src/matrix/resources $<TARGET_FILE_DIR:dgesample0>
  )
add_custom_command(
  TARGET dgesample0
  PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy ${learnopengl_REPOCNT_DIR}/src/7.in_practice/2.text_rendering/text.vs ${CMAKE_CURRENT_BINARY_DIR}
  )
add_custom_command(
  TARGET dgesample0
  PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy ${learnopengl_REPOCNT_DIR}/src/7.in_practice/2.text_rendering/text.fs ${CMAKE_CURRENT_BINARY_DIR}
  )]]
