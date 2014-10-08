# @file CMakeLists.txt
#
# @author Tobias Triffterer
#
# @brief Steuerdatei für das Build-System
#
# @version 1.0.0
#
#
# AlleGegenSchlaubi - educational quiz game
# Copyright (C) 2014  Tobias Triffterer <tobias@ep1.ruhr-uni-bochum.de>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

project(AlleGegenSchlaubi)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)

set(OS_SPECIFIC_COMPILE_FLAGS "")

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  find_package(KDE4 REQUIRED)
  set(OS_SPECIFIC_COMPILE_FLAGS "-rdynamic")
else()
  set(KDE4_KDECORE_LIBS"")
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  set(OS_SPECIFIC_COMPILE_FLAGS "-mwindows")
  set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
endif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_SOURCE_DIR})

set(COMPILE_FLAGS "-Wall -W -Wconversion -Wshadow -Wwrite-strings -pthread -std=gnu++0x -fexceptions -O2 -fPIC ${OS_SPECIFIC_COMPILE_FLAGS}")
set(CMAKE_CXX_FLAGS ${COMPILE_FLAGS})

set(AlleGegenSchlaubi_SRCS quizknubbel.cpp quizfenster.cpp punkteab.cpp fragebearbeiten.cpp steuerfenster.cpp fragenliste.cpp frage.cpp main.cpp)
set(AlleGegenSchlaubi_RES icons.qrc)
set(AlleGegenSchlaubi_UI steuerfenster.ui fragebearbeiten.ui quizfenster.ui)

qt4_automoc(${AlleGegenSchlaubi_SRCS})
qt4_add_resources(AlleGegenSchlaubi_RES_H ${AlleGegenSchlaubi_RES})
qt4_wrap_ui(AlleGegenSchlaubi_UI_H ${AlleGegenSchlaubi_UI})

add_executable(AlleGegenSchlaubi ${AlleGegenSchlaubi_SRCS} ${AlleGegenSchlaubi_RES_H} ${AlleGegenSchlaubi_UI_H})
target_link_libraries(AlleGegenSchlaubi ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${KDE4_KDECORE_LIBS})
install(TARGETS AlleGegenSchlaubi RUNTIME DESTINATION bin)
