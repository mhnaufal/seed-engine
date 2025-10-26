#pragma once

#include <SDL3/SDL_mouse.h>

namespace seed {
using MouseCode = int;

namespace Mouse {
enum : MouseCode {
    // NOTE: from SDL3
    ButtonLeft = SDL_BUTTON_LEFT,
    ButtonRight = SDL_BUTTON_RIGHT,
    ButtonMiddle = SDL_BUTTON_MIDDLE,
    ButtonSide1 = SDL_BUTTON_X1,
    ButtonSide2 = SDL_BUTTON_X2,
};
}
}