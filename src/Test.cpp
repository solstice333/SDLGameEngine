//============================================================================
// Name        : SDLReviseFigureClass.cpp
// Author      : Kevin Navero
// Version     :
// Copyright   : 
// Description : Revising Figure class to include inheritance
//============================================================================

#include <iostream>
#include <string>
#include <vector>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include "SDLAbstractionLayer.h"

using namespace std;

const int WIDTH = 640;
const int HEIGHT = 480;
const int FPS = 40;
const double SPEED = 25;
const int GRAVITY = 2;
const double JUMPSTRENGTH = 1.5;
const bool CHOOSE_SQUARE = false; //change this to true or false to switch from having
                                 //user control with a circle or square

//uncomment or comment the two lines below if you want to disable or enable gravity for the
//user controlled objects
const Figure::Gravity G = Figure::GRAVITY_ENABLED;
//const Figure::Gravity G = Figure::GRAVITY_DISABLED;

int main(int argc, char* argv[]) {
   SDL_Surface* screen = init(WIDTH, HEIGHT, "Test");

   Surface s("images/square.bmp");
   Surface r("images/rectangle.png");
   Surface c("images/dot.bmp", Surface::CYAN);

   RectFigure sFig(0, 0, s, screen, G, SPEED, GRAVITY,
         JUMPSTRENGTH);
   RectFigure rFig(300, 100, r, screen, Figure::GRAVITY_DISABLED);
   RectFigure rFig1(500, -100, r, screen, Figure::GRAVITY_DISABLED);
   CircFigure cFig(100, 400, c, screen, Figure::GRAVITY_DISABLED, SPEED,
         GRAVITY, JUMPSTRENGTH);
   CircFigure cFig1(10, 10, c, screen, G, SPEED, GRAVITY,
         JUMPSTRENGTH);

   vector<Figure*> collisions;
   collisions.push_back(&rFig);
   collisions.push_back(&rFig1);
   collisions.push_back(&cFig);

   SDL_Event event;
   bool quit = false;
   Timer t;

   while (!quit) {
      if (SDL_PollEvent(&event)) {
         if (event.type == SDL_QUIT) {
            quit = true;
            break;
         }

         if (CHOOSE_SQUARE)
            sFig.handleInput(event);
         else
            cFig1.handleInput(event);
      }

      if (CHOOSE_SQUARE)
         sFig.move(collisions);
      else
         cFig1.move(collisions);

      fillScreen(screen, Surface::WHITE);
      rFig.show();
      rFig1.show();
      cFig.show();

      if (CHOOSE_SQUARE)
         sFig.show();
      else
         cFig1.show();

      flip(screen);

      t.delayFrame(FPS);
   }

   cleanUp();

   return 0;
}
