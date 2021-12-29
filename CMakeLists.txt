# set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
# set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(glfw-3.3.6)

find_package(OpenGL REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/glad/include)

set(GLAD_SOURCE ${PROJECT_SOURCE_DIR}/glad/src/glad.c)

add_subdirectory(t1_create_window)
add_subdirectory(t2_triangle)
add_subdirectory(t3_shapes)
add_subdirectory(t4_index_buffer)
add_subdirectory(t5_batch_render)
add_subdirectory(t6_dynamic_render)