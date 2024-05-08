all: ClearScreen AbyssalHymn

ClearScreen:
	clear

AbyssalHymn:
	g++ -I libraries/SDL2/include \
		-L libraries/SDL2/lib \
		-I libraries/SFML/include \
		-L libraries/SFML/lib \
		\
		-I include \
		-I src/map_data \
		\
		-o AbyssalHymn \
		\
		src/configuration.cpp \
		src/object2D.cpp \
		src/audio_object.cpp \
		src/player.cpp \
		src/hud.cpp \
		src/item.cpp \
		src/door.cpp \
		src/block.cpp \
		src/projectile.cpp \
		src/decoration.cpp \
		src/bubble.cpp \
		src/particle_effect.cpp \
		\
		src/enemy.cpp \
		src/enemy/slime.cpp \
		src/enemy/skeleton.cpp \
		\
		src/UI/menu.cpp \
		src/UI/button.cpp \
		src/UI/section.cpp \
		src/map.cpp \
		src/world.cpp \
		src/scene.cpp \
		src/input.cpp \
		src/audio.cpp \
		src/camera.cpp \
		src/renderer.cpp \
		src/collision.cpp \
		src/block_template.cpp \
		\
		main.cpp \
		CONSOLE.cpp \
		EDITOR.cpp \
		-lmingw32 \
		-lSDL2main \
		-lSDL2 \
		-lSDL2_image \
		-lsfml-system \
		-lsfml-audio \
		-ffast-math
	./AbyssalHymn.exe

clean:
	del AbyssalHymn

# Add <-mwindows> so when you run AbyssalHymn.exe
# it doesnt open a terminal
# (unless you need debugging and stuff ofc)