cmake_minimum_required(VERSION 3.21)

project(Prog2Prufung
    VERSION 1.0.0
    DESCRIPTION "Prog2 Prüfung - Dungeon Crawler"
    LANGUAGES CXX C
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Visual Studio: Ordnerstruktur in der Projektmappe aktivieren
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Ausgabe aller Binaries in einen gemeinsamen Ordner (pro Konfiguration)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# ---------------------------------------------------------------------------
# raylib (wird automatisch heruntergeladen und mitgebaut)
# ---------------------------------------------------------------------------
include(FetchContent)

set(RAYLIB_VERSION 5.5)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG        ${RAYLIB_VERSION}
    GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(raylib)

# raylib in der VS-Projektmappe in einen eigenen Ordner verschieben
set_target_properties(raylib PROPERTIES FOLDER "ThirdParty")
if(TARGET glfw)
    set_target_properties(glfw PROPERTIES FOLDER "ThirdParty")
endif()
if(TARGET update_mappings)
    set_target_properties(update_mappings PROPERTIES FOLDER "ThirdParty")
endif()

# ---------------------------------------------------------------------------
# Hauptprogramm
# ---------------------------------------------------------------------------
set(SOURCES
    Prog2Prüfung.cpp
    Character.cpp
    ItemArmor.cpp
    ItemBase.cpp
    ItemEquippable.cpp
    ItemSword.cpp
    ItemTrinket.cpp
    ItemWeapon.cpp
    Map.cpp
    MapGenerator.cpp
    PlayerCharacter.cpp
    Tile.cpp
    TileBlocked.cpp
    TileExit.cpp
    TileStart.cpp
    TileTraversable.cpp
    TileTreasure.cpp
    utils.cpp
    WindowsConsole.cpp
)

set(HEADERS
    Prog2Prüfung.h
    Character.h
    Equipmentcontainer.h
    Inventory.h
    ItemArmor.h
    ItemBase.h
    ItemContainer.h
    ItemEquippable.h
    ItemSword.h
    ItemTrinket.h
    ItemWeapon.h
    Map.h
    MapGenerator.h
    Movement.h
    PlayerCharacter.h
    Tile.h
    TileBlocked.h
    TileExit.h
    TileStart.h
    TileTraversable.h
    TileTreasure.h
    utils.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE winmm)
endif()

# Header/Quellen in VS in Filtern gruppieren
source_group("Header Files" FILES ${HEADERS})
source_group("Source Files" FILES ${SOURCES})

# ---------------------------------------------------------------------------
# MSVC-spezifische Einstellungen
# ---------------------------------------------------------------------------
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        /W4             # Hohe Warnstufe
        /utf-8          # Quelldateien als UTF-8 (Umlaute in Kommentaren/Dateinamen)
        /MP             # Paralleles Kompilieren
        /permissive-    # Standardkonformer Modus
        /Zc:__cplusplus # Korrekter __cplusplus-Wert
    )
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        _CRT_SECURE_NO_WARNINGS
        NOMINMAX
    )
    # Konsolenanwendung (Ausgabe über cout / ANSI-Escapes)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        WIN32_EXECUTABLE OFF
        VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    )
endif()

# Prog2Prufung als Startprojekt in Visual Studio setzen
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
