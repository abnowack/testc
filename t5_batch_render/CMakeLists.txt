project(t5_batch_render)

set(SOURCE_FILES main.c)

add_executable(t5_batch_render ${SOURCE_FILES} ${GLAD_SOURCE})

target_link_libraries(t5_batch_render glfw OpenGL::GL)