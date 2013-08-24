//============================================================================
// Name        : SDLGameSaves.cpp
// Author      : Kevin Navero
// Version     :
// Copyright   : 
// Description :
//============================================================================

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "Dot.h"
#include "SimpleLoadSave.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

/*
 * Description: game save test. Integrate into api further in the late dev stages
 */
/*
int main(int argc, char* argv[]) {
   SDL_Surface* screen = init(640, 480, "SDL Game Saves Test");

   Surface dotImage("images/dot.bmp", Surface::CYAN);

   Dot dot;
   Surface::Color bg = Surface::WHITE;

   try {
      if(!loadSavedGame(dot, bg, dotImage, screen))
         dot.setDot(10, 10, dotImage, screen);
   }
   catch (LoadSavedGameException& lsge) {
      dot.setDot(10, 10, dotImage, screen);
   }

   bool quit = false;
   SDL_Event event;
   Timer timer;

   while (!quit) {
      timer.start();

      if (SDL_PollEvent(&event)) {
         if (event.type == SDL_QUIT) {
            quit = true;
            break;
         }

         if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
            case SDLK_1:
               bg = Surface::BLUE;
               break;
            case SDLK_2:
               bg = Surface::CYAN;
               break;
            case SDLK_3:
               bg = Surface::GREEN;
               break;
            case SDLK_4:
               bg = Surface::WHITE;
               break;
            default:
               break;
            }
         }

         dot.handleInput(event);
      }

      dot.move();

      fillScreen(screen, bg);
      dot.show();

      flip(screen);

      timer.delayFrame(30);
   }

   saveGame(dot, bg);
   cleanUp();

   return 0;
}
*/
