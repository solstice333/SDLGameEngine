//============================================================================
// Name        : SDLAlphaBlending.cpp
// Author      : Kevin Navero
// Version     :
// Copyright   : 
// Description :
//============================================================================

#include <iostream>
#include "../../main/SDLAbstractionLayer.h"

using namespace std;

const int FPS = 20;

/*
 * Description: example for alpha blending. useful for when an enemy is killed during gameplay
 */
/*
int main(int argc, char* argv[]) {
   SDL_Surface* screen = init(640, 480, "SDL Alpha Blending");

   Surface back("images/fadein.png");
   Surface front("images/fadeout.png");

   bool quit = false;
   Timer timer;
   int alpha = SDL_ALPHA_OPAQUE;
   SDL_Event event;
   Uint8* keystates = SDL_GetKeyState(NULL);

   while (!quit) {
      if (SDL_PollEvent (&event)) {
         if (event.type == SDL_QUIT) {
            quit = true;
            break;
         }
      }

      if (keystates[SDLK_UP]) {
         if (alpha < SDL_ALPHA_OPAQUE)
            alpha += 1;
      }

      if (keystates[SDLK_DOWN]) {
         if (alpha > SDL_ALPHA_TRANSPARENT)
            alpha -= 1;
      }

      SDL_SetAlpha(front.getSDL_Surface(), SDL_SRCALPHA, alpha);
      applySurface(0, 0, back, screen); //Hold up to fade in (back message)
      applySurface(0, 0, front, screen);  //Hold down to fade out (front message)

      cout << "alpha: " << alpha << endl;

      flip(screen);
   }

   cleanUp();

   return 0;
}
*/
