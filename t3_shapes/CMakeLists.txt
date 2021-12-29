project(t3_shapes)

set(SOURCE_FILES main.c)

add_executable(t3_shapes ${SOURCE_FILES} ${GLAD_SOURCE})

target_link_libraries(t3_shapes glfw OpenGL::GL)