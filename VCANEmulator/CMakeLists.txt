cmake_minimum_required(VERSION 3.16)

project(VCANEmulator VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick SerialBus)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appVCANEmulator
    main.cpp
)

qt_add_qml_module(appVCANEmulator
    URI VCANEmulator
    VERSION 1.0
    QML_FILES
        Main.qml
        SOURCES canbusdatamanager.h canbusdatamanager.cpp
        QML_FILES SpeedControl.qml
        QML_FILES RPMControl.qml
        QML_FILES GearControl.qml
        QML_FILES BatteryControl.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appVCANEmulator PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appVCANEmulator
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appVCANEmulator
    PRIVATE Qt6::Quick Qt6::SerialBus
)

include(GNUInstallDirs)
install(TARGETS appVCANEmulator
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
