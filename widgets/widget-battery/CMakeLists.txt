add_executable(widget-battery main.cpp)
target_link_libraries(widget-battery PRIVATE eww_ui)

add_custom_command(TARGET widget-battery POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_SOURCE_DIR}/bin/widgets"
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:widget-battery> "${CMAKE_SOURCE_DIR}/bin/widgets/")