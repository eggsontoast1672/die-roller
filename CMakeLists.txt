# A OpenGL_GL_PREFERENCE variable may be set to specify the preferred way to
# provide legacy GL interfaces in case multiple choices are available. The
# value may be one of:
# 
# GLVND
# 
#     If the GLVND OpenGL and GLX libraries are available, prefer them. This
#     forces OPENGL_gl_LIBRARY to be empty.
# 
#     Changed in version 3.11: This is the default, unless policy CMP0072 is
#     set to OLD and no components are requested (since components correspond
#     to GLVND libraries).
cmake_minimum_required(VERSION 3.11)

project(DieRoller)

find_package(PkgConfig)

pkg_check_modules(GLEW REQUIRED glew)
pkg_check_modules(GLFW REQUIRED glfw3)

add_executable(roller src/main.c)

target_link_libraries(roller PRIVATE ${GLEW_LIBRARIES} ${GLFW_LIBRARIES})
