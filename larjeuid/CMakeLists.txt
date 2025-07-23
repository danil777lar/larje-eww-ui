add_executable(larjeuid
        main.cpp
        WindowController.cpp
        WindowController.h
        Window.cpp
        Window.h)

add_custom_command(TARGET larjeuid POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_SOURCE_DIR}/bin/larjeuid"
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:larjeuid> "${CMAKE_SOURCE_DIR}/bin/larjeuid/")