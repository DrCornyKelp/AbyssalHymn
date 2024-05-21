cmake_minimum_required(VERSION 3.29)
project(AbyssalHymn)

set(CMAKE_CXX_STANDARD 20)

include_directories(
    libraries/SDL2/include
    libraries/SFML/include
    include
    map_data
)

link_directories(
    libraries/SDL2/lib
    libraries/SFML/lib
)

set(ASSETS ${PROJECT_SOURCE_DIR}/res)
file(COPY ${ASSETS} DESTINATION ${CMAKE_BINARY_DIR})
set(MAP_DATA ${PROJECT_SOURCE_DIR}/map_data)
file(COPY ${MAP_DATA} DESTINATION ${CMAKE_BINARY_DIR})
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
