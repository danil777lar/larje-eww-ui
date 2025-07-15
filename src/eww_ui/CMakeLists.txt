add_library(eww_ui STATIC
        Box.cpp
        EwwUIObject.cpp
    )

target_include_directories(eww_ui PUBLIC ${CMAKE_SOURCE_DIR}/include/eww_ui)
