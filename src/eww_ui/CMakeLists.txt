add_library(eww_ui STATIC
        EwwUIObject.cpp
        EwwUIObjectContainer.cpp
        EwwProperties.cpp

        Box.cpp
        Label.cpp
    )

target_include_directories(eww_ui PUBLIC ${CMAKE_SOURCE_DIR}/include/eww_ui)
