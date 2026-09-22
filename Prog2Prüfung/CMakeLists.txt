cmake_minimum_required(VERSION 3.12)
project(Prog2Prüfung)

# CMakeList.txt: CMake-Projekt für "Prog2Prüfung". Schließen Sie die Quelle ein, und definieren Sie
# projektspezifische Logik hier.
#

# Include FetchContent für raylib
include(FetchContent)

# Laden raylib herunter
FetchContent_Declare(raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG 4.5.0
)

# Raylib-Optionen für minimalen Build
set(RAYLIB_VERSION 4.5.0)
set(BUILD_EXAMPLES OFF CACHE BOOL "Build the examples" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "Build the games" FORCE)
set(BUILD_TESTING OFF CACHE BOOL "Build testing" FORCE)

# Stille Ausgabe beim Download
message(STATUS "Raylib wird heruntergeladen und kompiliert...")

FetchContent_MakeAvailable(raylib)

# Fügen Sie der ausführbaren Datei dieses Projekts eine Quelle hinzu.
file(GLOB SOURCES "*.cpp" "*.h")
add_executable (Prog2Pruefung ${SOURCES})

# Link raylib
target_link_libraries(Prog2Pruefung PRIVATE raylib)
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
