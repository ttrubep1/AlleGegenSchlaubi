project(AlleGegenSchlaubi)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  find_package(KDE4 REQUIRED)
else()
  set(KDE4_KDECORE_LIBS"")
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(COMPILE_FLAGS "-Wall -W -Wconversion -Wshadow -Wwrite-strings -pthread -rdynamic -std=gnu++0x -fexceptions -O2 -fPIC")
set(CMAKE_CXX_FLAGS ${COMPILE_FLAGS})

set(AlleGegenSchlaubi_SRCS punkteab.cpp fragebearbeiten.cpp steuerfenster.cpp fragenliste.cpp frage.cpp main.cpp)
set(AlleGegenSchlaubi_RES icons.qrc)
set(AlleGegenSchlaubi_UI steuerfenster.ui fragebearbeiten.ui quizfenster.ui)

qt4_automoc(${AlleGegenSchlaubi_SRCS})
qt4_add_resources(AlleGegenSchlaubi_RES_H ${AlleGegenSchlaubi_RES})
qt4_wrap_ui(AlleGegenSchlaubi_UI_H ${AlleGegenSchlaubi_UI})

add_executable(AlleGegenSchlaubi ${AlleGegenSchlaubi_SRCS} ${AlleGegenSchlaubi_RES_H} ${AlleGegenSchlaubi_UI_H})
target_link_libraries(AlleGegenSchlaubi ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${KDE4_KDECORE_LIBS})
install(TARGETS AlleGegenSchlaubi RUNTIME DESTINATION bin)
