cmake_minimum_required(VERSION 3.5)

project(MagicCube VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS OpenGLWidgets) 
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Gui) 
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS OpenGL)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS SerialBus)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS HttpServer)

set(PROJECT_SOURCES
        main.cpp
        ug_mainwindow.cpp
        ug_mainwindow.h
        ug_openglwidget.cpp
        ug_openglwidget.h
        ug_cube.cpp
        ug_cube.h
        ug_magiccube.cpp
        ug_magiccube.h
        ug_panel.cpp
        ug_panel.h
        ug_axis.cpp
        ug_axis.h
        ug_modbustcp.cpp
        ug_modbustcp.h
        ug_httpserver.cpp
        ug_httpserver.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(MagicCube
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
		res.qrc
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET MagicCube APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(MagicCube SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(MagicCube
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(MagicCube PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(MagicCube PRIVATE Qt${QT_VERSION_MAJOR}::OpenGLWidgets)
target_link_libraries(MagicCube PRIVATE Qt${QT_VERSION_MAJOR}::Gui)
target_link_libraries(MagicCube PRIVATE Qt${QT_VERSION_MAJOR}::OpenGL)
target_link_libraries(MagicCube PRIVATE Qt${QT_VERSION_MAJOR}::SerialBus)
target_link_libraries(MagicCube PRIVATE Qt${QT_VERSION_MAJOR}::HttpServer)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.MagicCube)
endif()
set_target_properties(MagicCube PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS MagicCube
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(MagicCube)
endif()
