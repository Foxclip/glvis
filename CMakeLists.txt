cmake_minimum_required(VERSION 3.10)

project(glvis LANGUAGES CXX)
set (CMAKE_CXX_STANDARD 20)

set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "" FORCE)
set(GLFW_INSTALL OFF CACHE INTERNAL "" FORCE)

add_subdirectory(glfw)
add_subdirectory(glad)
add_subdirectory(tests)

add_library(${PROJECT_NAME})
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(GLAD_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/glad/include)
set(GLAD_SRC_DIR ${PROJECT_SOURCE_DIR}/glad/src)

target_sources(${PROJECT_NAME} PRIVATE
    ${SRC_DIR}/app.cpp
    ${SRC_DIR}/utils.cpp
)
target_include_directories(${PROJECT_NAME} PRIVATE
    ${INCLUDE_DIR}
)
if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE glfw opengl32)
else()
    find_package(OpenGL REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE glfw OpenGL::GL)
endif()
target_link_libraries(${PROJECT_NAME} PRIVATE glad)
