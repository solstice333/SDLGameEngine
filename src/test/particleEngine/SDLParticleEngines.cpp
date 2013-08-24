//============================================================================
// Name        : SDLParticleEngines.cpp
// Author      : Kevin Navero
// Version     :
// Copyright   : 
// Description :
//============================================================================

#include <iostream>
#include <ctime>
#include "../../main/SDLAbstractionLayer.h"
#include "Particle.h"
#include "Dot2.h"

using namespace std;

/*
int main(int argc, char* argv[]) {
   SDL_Surface* screen = init(640, 480, "SDL Particle Engine Test");
   srand(time(NULL));

   Surface p1("images/blue.bmp", Surface::CYAN);
   Surface p2("images/green.bmp", Surface::CYAN);
   Surface p3("images/red.bmp", Surface::CYAN);
   Surface p4("images/shimmer.bmp", Surface::CYAN);
   Surface dot("images/dot.bmp", Surface::CYAN);

   Dot2 dfig(10, 10, dot, p1, p2, p3, p4, screen);

   SDL_Event event;
   bool quit = false;
   Timer timer;

   while (!quit) {
      timer.start();

      if (SDL_PollEvent(&event)) {
         if(event.type == SDL_QUIT) {
            quit = true;
            break;
         }

         dfig.handleInput(event);
      }

      dfig.move();

      fillScreen(screen, Surface::WHITE);
      dfig.show();
      flip(screen);

      timer.delayFrame(40);
   }

   cleanUp();

	return 0;
}
*/
