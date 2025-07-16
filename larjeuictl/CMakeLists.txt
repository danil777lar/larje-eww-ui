add_executable(larjeuictl
        main.cpp
        WindowController.cpp
        WindowController.h
        Window.cpp
        Window.h)

add_custom_command(TARGET larjeuictl POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_SOURCE_DIR}/bin"
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:larjeuictl> "${CMAKE_SOURCE_DIR}/bin/")