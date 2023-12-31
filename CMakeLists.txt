cmake_minimum_required(VERSION 3.5)

project(bbb_info_app LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets LinguistTools REQUIRED)
find_package(Qt5Network REQUIRED)


set(TS_FILES bbb_info_app_zh_TW.ts)

set(PROJECT_SOURCES
        main.cpp
        #mainwindow.cpp
        #mainwindow.h
        #mainwindow.ui
        #data.h
        #server_lib.cpp
        #meeting_lib.cpp
        #attendee_lib.cpp
        #xml_reader_lib.cpp
        ${TS_FILES}
)

set(LIB_PATHS
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/data
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/ui
    )


include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/lib.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/deps.cmake)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(bbb_info_app
        ${PROJECT_SOURCES}
    )

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(bbb_info_app SHARED
            ${PROJECT_SOURCES} ui_lib data_lib
        )
    else()
        add_executable(bbb_info_app
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()



target_link_libraries(bbb_info_app PRIVATE ui_lib data_lib Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network)
