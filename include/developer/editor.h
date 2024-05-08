#ifndef EDITOR_H
#define EDITOR_H

#include <world.h>
#include <developer/console.h>

struct BlockEditor
{
    int index = 0,
        type = 0,
        page = 0;
    bool front = 1;

    // Note: these are not indexes, they are sizes
    void normalize(int maxPath, int maxPage, int maxType = 7);
};

struct EditorArrow
{ SDL_Texture *up, *down, *left, *right; };

class Editor
{
private:
    Console *console;
    World *world;
    Map *map_cur;
    Input *input;
    Player *player;
    Collision *collision;

    // Editor Action
    bool minimize = false;

    // Editor Component
    SDL_Texture *EditBack;
    EditorArrow EditArrow;
    SDLTexture1D EditNumber;

    // EDITOR FOR EACH STUFF
    int2D DragLast = {};

    int blockPerPage = (CFG->WIDTH - 32) / 96;
    BlockEditor BlockEdit;
    SDL_Texture *EditLetterType,
                *EditLetterFront,
                *EditLetterBack,
                *EditLetterDel,
                *EditLetterGlob,
                *EditLetterSave,
                *EditLetterLoad;

public:
    bool open = 0;

    ~Editor();
    Editor(Console *consl, World *w, Input *i, Player *p, Collision *c);

    void blockEditor();

    void update();
};

#endif