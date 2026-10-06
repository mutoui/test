cmake_minimum_required(VERSION 3.16)

project(helloworld VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

qt_add_executable(helloworld
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.h
    src/content.cpp
    src/content.h
    src/fivephasewidget.cpp
    src/fivephasewidget.h
)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT helloworld)

target_link_libraries(helloworld PRIVATE Qt6::Widgets)

set_target_properties(helloworld PROPERTIES
    WIN32_EXECUTABLE ON
)

# Visual Studio F5 时能找到 Qt DLL
if(MSVC)
    get_filename_component(_qt_prefix "${Qt6_DIR}/../../.." ABSOLUTE)
    set_target_properties(helloworld PROPERTIES
        VS_DEBUGGER_ENVIRONMENT "PATH=${_qt_prefix}/bin;$ENV{PATH}"
        VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:helloworld>"
    )
endif()
