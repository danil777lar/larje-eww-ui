add_executable(widget-clock main.cpp)
target_link_libraries(widget-clock PRIVATE eww_ui)

add_custom_command(TARGET widget-clock POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_SOURCE_DIR}/bin/widgets"
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:widget-clock> "${CMAKE_SOURCE_DIR}/bin/widgets/")