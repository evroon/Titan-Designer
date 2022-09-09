#pragma once

#include "core/definitions.h"

#if PLATFORM == WINDOWS
#include "sdl_mouse.h"
#else
#include "SDL2/SDL_mouse.h"
#endif

class Cursor;

class CursorManager {
   public:
    static void set_active_cursor(Cursor* p_cursor);

   private:
    static Cursor* active_cursor;
};

class Cursor {
   public:
    Cursor();
    ~Cursor();

    enum SystemCursorType { ARROW, IBEAM, WAIT, CROSSHAIR, WAITARROW, NO, HAND };

    void set_default();
    void set_cursor(SystemCursorType p_type);
    void activate();

    SDL_Cursor* get_SDL_cursor() const;

   private:
    SystemCursorType type;
    SDL_Cursor* cursor;
};
