//============================================================================
// Name        : SDLResizableWindowsAndWindowEvents.cpp
// Author      : Kevin Navero
// Version     :
// Copyright   : 
// Description :
//============================================================================

#include <iostream>
#include "SDL/SDL.h"
#include "../main/Exception.h"
#include "Window.h"

using namespace std;

void init();

void init() {
   if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
      throw InitException();
}

/*
int main() {
   SDL_Surface* screen = NULL;
   init();
   Window w(screen, 640, 480);

   Surface bg("images/bgnd1.jpg");

   bool quit = false;
   SDL_Event event;
   Timer timer;

   while (!quit) {
      timer.start();

      if(SDL_PollEvent(&event)) {
         if(event.type == SDL_QUIT) {
            quit = true;
            break;
         }

         w.handleEvents(event);
      }

      applySurface(0, 0, bg, screen);
      flip(screen);

      timer.delayFrame(40);
   }

   cleanUp();

	return 0;
}
*/
