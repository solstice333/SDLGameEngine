//============================================================================
// Name        : SDLResizableWindowsAndWindowEvents.cpp
// Author      : Kevin Navero
// Version     :
// Copyright   : 
// Description :
//============================================================================

#include <iostream>
#include <SDL/SDL.h>
#include "../../main/Exception.h"
#include "Window.h"

using namespace std;

/*
 * Description: window management for resizing and fullscreen. Integrate into the api in
 * late dev stages
 */
/*
int main(int argc, char* argv[]) {
   SDL_Surface* screen = init(640, 480, "SDL Resizing Test");
   Window w(screen);

   Surface bg("images/bgnd1.jpg");

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

         w.handleEvents(event);
      }

      if (w.error()) {
         cout << "Error: Window error exiting" << endl;
         return 1;
      }

      applySurface((screen->w - bg.getSDL_Surface()->w) / 2,
            (screen->h - bg.getSDL_Surface()->h) / 2, bg, screen);
      flip(screen);

      timer.delayFrame(40);
   }

   cleanUp();

   return 0;
}
*/
