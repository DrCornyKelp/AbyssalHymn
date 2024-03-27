all: AbyssalHymn

AbyssalHymn:
	g++ -I include \
		-I libraries/include \
		-L libraries/lib \
		-o AbyssalHymn \
		src/object2D.cpp \
		src/sprite.cpp \
		src/player.cpp \
		src/hud.cpp \
		src/game.cpp \
		src/item.cpp \
		src/block.cpp \
		src/projectile.cpp \
		src/decoration.cpp \
		src/npc_dialogue.cpp \
		\
		src/enemy.cpp \
		src/enemy/slime.cpp \
		src/enemy/skeleton.cpp \
		\
		src/map.cpp \
		src/map/map1.cpp \
		\
		src/audio.cpp \
		src/scene.cpp \
		src/input.cpp \
		src/camera.cpp \
		src/renderer.cpp \
		src/collision.cpp \
		\
		main.cpp \
		-lmingw32 \
		-lSDL2main \
		-lSDL2 \
		-lSDL2_image \
		-lSDL2_mixer \
		-ffast-math
	cls
	./AbyssalHymn.exe

clean:
	del AbyssalHymn