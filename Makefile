all: AbyssalHymn

AbyssalHymn:
	g++ -I include \
		-I libraries/include \
		-L libraries/lib \
		-o AbyssalHymn \
		src/object2D.cpp \
		src/hud.cpp \
		src/sprite.cpp \
		src/game.cpp \
		src/block.cpp \
		src/player.cpp \
		src/decoration.cpp \
		src/audio.cpp \
		src/projectile.cpp \
		src/enemy.cpp \
		src/enemy/slime.cpp \
		src/item.cpp \
		src/map.cpp \
		src/map/map1.cpp \
		src/npc_dialogue.cpp \
		src/renderer.cpp \
		src/input.cpp \
		src/camera.cpp \
		src/scene.cpp \
		main.cpp \
		-lmingw32 \
		-lSDL2main \
		-lSDL2 \
		-lSDL2_image \
		-lSDL2_mixer
	cls
	./AbyssalHymn.exe

clean:
	del AbyssalHymn