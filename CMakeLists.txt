cmake_minimum_required(VERSION 3.28)
project(denote)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Test
        REQUIRED)

# Eseguibile principale
add_executable(denote
        main.cpp
        BaseWindow.cpp
        NewNoteDialog.cpp
        Note.cpp
        NoteManager.cpp
        DeleteNoteDialog.cpp
        DeleteNoteDialog.h
        RenameNoteDialog.cpp
        FileManager.cpp
)

target_link_libraries(denote
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

# Eseguibile di test
enable_testing()
add_executable(denoteTests
        tests/main_tests.cpp
        NewNoteDialog.cpp
        Note.cpp
        NoteManager.cpp
        BaseWindow.cpp
        DeleteNoteDialog.cpp
        tests/TestNoteManager.cpp
        tests/TestBaseWindow.cpp
        tests/TestNewNoteDialog.cpp
        RenameNoteDialog.cpp
        FileManager.cpp
)

target_link_libraries(denoteTests
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Test
)

add_test(NAME TestNewNote COMMAND denoteTests)

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET denote POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:denote>/plugins/platforms/")
        add_custom_command(TARGET denote POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:denote>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets Test)
        add_custom_command(TARGET denote POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:denote>")
    endforeach ()
endif ()
