project(t1_create_window)

set(SOURCE_FILES main.c)

add_executable(t1_create_window ${SOURCE_FILES} ${GLAD_SOURCE})

target_link_libraries(t1_create_window glfw OpenGL::GL)