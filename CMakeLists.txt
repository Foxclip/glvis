cmake_minimum_required(VERSION 3.10)

project(glvis LANGUAGES CXX)

set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "" FORCE)
set(GLFW_INSTALL OFF CACHE INTERNAL "" FORCE)
add_subdirectory(glfw)

add_executable(${PROJECT_NAME}
    main.cpp
    glad/src/glad.c
)

target_include_directories(${PROJECT_NAME} PRIVATE
    glad/include
)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE glfw opengl32)
else()
    find_package(OpenGL REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE glfw OpenGL::GL)
endif()
