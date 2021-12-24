project(t2_triangle)

set(SOURCE_FILES main.c)

add_executable(t2_triangle ${SOURCE_FILES} ${GLAD_SOURCE})

target_link_libraries(t2_triangle glfw OpenGL::GL)