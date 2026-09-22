cmake_minimum_required(VERSION 3.12)
project(Prog2Prüfung)

# CMakeList.txt: CMake-Projekt für "Prog2Prüfung". Schließen Sie die Quelle ein, und definieren Sie
# projektspezifische Logik hier.
#

# Fügen Sie der ausführbaren Datei dieses Projekts eine Quelle hinzu.
file(GLOB SOURCES "*.cpp" "*.h")
add_executable (Prog2Pruefung ${SOURCES})

# Force CMake to regenerate
set_property(DIRECTORY PROPERTY CMAKE_CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR})

# Set C++ Standard
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Prog2Pruefung PROPERTY CXX_STANDARD 20)
  set_property(TARGET Prog2Pruefung PROPERTY CXX_STANDARD_REQUIRED ON)
endif()

# Set MSVC Runtime Library
if (MSVC)
  set_property(TARGET Prog2Pruefung PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreadedDebug$<$<CONFIG:Release>:>")
  target_compile_options(Prog2Pruefung PRIVATE /W4)
endif()

# TODO: Fügen Sie bei Bedarf Tests hinzu, und installieren Sie Ziele.
