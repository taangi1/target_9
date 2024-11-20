cmake_minimum_required(VERSION 3.16)

project(target_9 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(SOURCES
    src/main.cpp
    src/mainwindow.cpp
    src/gamelogic.cpp
)

set(HEADERS
    include/mainwindow.h
    include/gamelogic.h
    include/stack.h
)

set(UI_FILES
    ui/mainwindow.ui
)

set(CMAKE_AUTOUIC_SEARCH_PATHS
    ui/
)

# Main app executable

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${UI_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(target_9 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Testing executable

enable_testing()

set(TEST_SOURCES
    tests/test_gamelogic_makeMove.cpp
    src/gamelogic.cpp
)

add_executable(GameLogicTestRunner ${TEST_SOURCES})

target_include_directories(GameLogicTestRunner PRIVATE include)

target_link_libraries(GameLogicTestRunner gtest gtest_main)

add_test(NAME GameLogicTest COMMAND GameLogicTestRunner)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.target_9)
endif()
set_target_properties(target_9 PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS target_9
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(target_9)
endif()
