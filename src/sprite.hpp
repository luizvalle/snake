#ifndef __GRAPHICAL_ELEMENT_HPP__
#define __GRAPHICAL_ELEMENT_HPP__

#include <SDL2/SDL.h>

struct Sprite {
    virtual void render(SDL_Renderer *renderer) const = 0;
};

#endif
