#ifndef MAIN_HPP
#define MAIN_HPP

#include <SDL2/SDL.h>
#include "asset_loader.hpp"
#include "graphics.hpp"
#include "world.hpp"

static void DestroySDL();
static void InitSDL();
extern World world;

#endif // MAIN_HPP
