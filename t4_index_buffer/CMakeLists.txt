project(t4_index_buffer)

set(SOURCE_FILES main.c)

add_executable(t4_index_buffer ${SOURCE_FILES} ${GLAD_SOURCE})

target_link_libraries(t4_index_buffer glfw OpenGL::GL)