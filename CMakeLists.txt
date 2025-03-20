cmake_minimum_required(VERSION 3.28)
project(denote)

# Specifica la versione di Qt6
set(Qt6_DIR "C:/Qt/6.8.2/mingw_64/lib/cmake/Qt6")
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Test)

# Imposta le opzioni per C++ e i moduli di Qt
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)

# Aggiungi l'eseguibile principale
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
        Observer.h
        Observable.h
)

# Link dei moduli Qt
target_link_libraries(denote
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

# Aggiungi il target per i test
enable_testing()
add_executable(denoteTests
        tests/main_tests.cpp
        BaseWindow.cpp
        BaseWindow.h  # Aggiungi esplicitamente i file header
        NewNoteDialog.cpp
        NewNoteDialog.h
        Note.cpp
        NoteManager.cpp
        DeleteNoteDialog.cpp
        DeleteNoteDialog.h
        tests/TestNoteManager.cpp
        tests/TestBaseWindow.cpp
        tests/TestNewNoteDialog.cpp
        tests/TestFileManager.cpp
        RenameNoteDialog.cpp
        RenameNoteDialog.h
        FileManager.cpp
        FileManager.h
)

# Abilita AUTOMOC per il target denoteTests
set_target_properties(denoteTests PROPERTIES AUTOMOC ON)

# Link dei moduli Qt per i test
target_link_libraries(denoteTests
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Test
)

# Aggiungi i percorsi di inclusione per denoteTests
target_include_directories(denoteTests PRIVATE
        "${CMAKE_BINARY_DIR}"
        "${CMAKE_SOURCE_DIR}"
)

# Aggiungi dipendenza tra denoteTests e denote
add_dependencies(denoteTests denote)

# Gestione delle DLL di Qt per Windows
if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()

    # Specifica il percorso di Qt
    set(QT_INSTALL_PATH "C:/Qt/6.8.2/mingw_64")

    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET denote POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:denote>/plugins/platforms/")
        add_custom_command(TARGET denote POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:denote>/plugins/platforms/")
    endif ()

    # Copia le DLL di Qt nel target
    foreach (QT_LIB Core Gui Widgets Test)
        add_custom_command(TARGET denote POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:denote>")
    endforeach ()
endif ()