add_executable(layout-default main.cpp)
target_link_libraries(layout-default PRIVATE eww_ui)

add_custom_command(TARGET layout-default POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_SOURCE_DIR}/bin/larjeuid/layouts"
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:layout-default> "${CMAKE_SOURCE_DIR}/bin/larjeuid/layouts/")