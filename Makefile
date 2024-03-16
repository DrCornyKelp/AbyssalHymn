all:
	cls
	g++ -I include -I libraries/include -L libraries/lib -o main src/object2D.cpp src/hud.cpp src/sprite.cpp src/game.cpp src/block.cpp src/event_trigger.cpp src/player.cpp src/decoration_static.cpp src/decoration_dynamic.cpp src/audio.cpp src/stages.cpp src/stage1.cpp src/npc_dialogue.cpp main.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer
	./main.exe