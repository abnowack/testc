project(t6_dynamic_render)

set(SOURCE_FILES main.c)

add_executable(t6_dynamic_render ${SOURCE_FILES} ${GLAD_SOURCE})

target_link_libraries(t6_dynamic_render glfw OpenGL::GL)