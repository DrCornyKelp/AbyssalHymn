cmake_minimum_required(VERSION 3.29)
project(AbyssalHymn)

# Cpp 20
set(CMAKE_CXX_STANDARD 20)

include_directories(
    libraries/SDL2/include
    libraries/SFML/include
    include
    map_data
)

# Libraries
link_directories(
    libraries/SDL2/lib
    libraries/SFML/lib
)

# Assets
set(ASSETS ${PROJECT_SOURCE_DIR}/assets)
file(COPY ${ASSETS} DESTINATION ${CMAKE_BINARY_DIR})
# Map data
set(MAP_DATA ${PROJECT_SOURCE_DIR}/map_data)
file(COPY ${MAP_DATA} DESTINATION ${CMAKE_BINARY_DIR})
# Player data
set(PLAYER_DATA ${PROJECT_SOURCE_DIR}/player_data)
file(COPY ${PLAYER_DATA} DESTINATION ${CMAKE_BINARY_DIR})

add_executable(AbyssalHymn
    src/configuration.cpp
    src/object2D.cpp
    src/audio_object.cpp
    src/multiplayer.cpp
    src/player.cpp
    src/hud.cpp
    src/item.cpp
    src/door.cpp
    src/block.cpp
    src/projectile.cpp
    src/decoration.cpp
    src/bubble.cpp
    src/particle_effect.cpp
    src/enemy.cpp
    src/enemy/slime.cpp
    src/enemy/skeleton.cpp
    src/UI/menu.cpp
    src/UI/intro.cpp
    src/UI/pause.cpp
    src/UI/button.cpp
    src/UI/section.cpp
    src/map.cpp
    src/world.cpp
    src/input.cpp
    src/audio.cpp
    src/camera.cpp
    src/renderer.cpp
    src/collision.cpp
    src/block_template.cpp
    main.cpp
    CONSOLE.cpp
    EDITOR.cpp
)

target_link_libraries(AbyssalHymn
    mingw32
    SDL2main
    SDL2
    SDL2_image
    sfml-system
    sfml-audio
    openal32
)

add_custom_command( TARGET AbyssalHymn POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:AbyssalHymn>
                    ${PROJECT_SOURCE_DIR}/AbyssalHymn.exe)