//============================================================================
// Name        : SDLScrolling.cpp
// Author      : Kevin Navero
// Version     :
// Copyright   : 
// Description : SDL Scrolling Test
//============================================================================

#include <iostream>
#include "SDLAbstractionLayer.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int FRAMERATE = 30;

const int DOT_WIDTH = 20;
const int DOT_HEIGHT = 20;

const int LEVEL_WIDTH = 1191;
const int LEVEL_HEIGHT = 670;

const double FS = 9;
const double CS = 40;
const double CJS = 0.7;
const double FJS = 0.25;
const int G = 2;
const int CNC = 1;
const int FNC = 4;

const bool FOO = true;  //change this from true or false to choose between a stick figure
                        //or dot ("FOO = true" is the stick figure)

const Figure::Gravity gravEnDis = Figure::GRAVITY_ENABLED;
//const Figure::Gravity gravEnDis = Figure::GRAVITY_DISABLED;

/*
 * Description: This tests the scrolling, collision detection, static figures within the level,
 * and animation. User can switch const bool FOO to true/false and comment/uncomment const
 * Figure::Gravity gravEnDis for Enabling and Disabling gravity
 */
int main(int argc, char* argv[]) {
   SDL_Surface* screen = init(SCREEN_WIDTH, SCREEN_HEIGHT, "SDL Scrolling");

   Surface bgnd("images/bgnd.jpg");
   Surface dot("images/dot.png", Surface::CYAN);
   Surface foo("images/foo.png", Surface::CYAN);
   Surface rect("images/rectangle.png");

   RectFigure rf1(300, 525, rect, screen, Figure::GRAVITY_DISABLED, false, 0, 0,
         0, 1, LEVEL_WIDTH, LEVEL_HEIGHT);
   RectFigure rf2(500, 125, rect, screen, Figure::GRAVITY_DISABLED, false, 0, 0,
         0, 1, LEVEL_WIDTH, LEVEL_HEIGHT);
   CircFigure cf1(700, 525, dot, screen, Figure::GRAVITY_DISABLED, false, 0, 0,
         0, 1, LEVEL_WIDTH, LEVEL_HEIGHT);
   CircFigure cf2(900, 350, dot, screen, Figure::GRAVITY_DISABLED, false, 0, 0,
         0, 1, LEVEL_WIDTH, LEVEL_HEIGHT);

   RectFigure rf;
   CircFigure cf;

   if (FOO)
      rf.setFigure(100, 300, foo, screen, gravEnDis, true, FS, G,
            FJS, FNC, LEVEL_WIDTH, LEVEL_HEIGHT);
   else
      cf.setFigure(100, 300, dot, screen, gravEnDis, true, CS, G,
            CJS, CNC, LEVEL_WIDTH, LEVEL_HEIGHT);

   bool quit = false;
   SDL_Event event;
   Timer timer;
   vector<Figure*> collisions;
   collisions.push_back(&rf1);
   collisions.push_back(&rf2);
   collisions.push_back(&cf1);
   collisions.push_back(&cf2);

   while (!quit) {
      timer.start();

      if (SDL_PollEvent(&event)) {
         if (event.type == SDL_QUIT) {
            quit = true;
            break;
         }

         if (FOO)
            rf.handleInput(event);
         else
            cf.handleInput(event);
      }

      if (FOO) {
         rf.move(collisions);
         applySurface(0, 0, bgnd, screen, rf.getCameraClip());
         rf.show(rf.getCameraClip());

         rf1.show(rf.getCameraClip());
         rf2.show(rf.getCameraClip());
         cf1.show(rf.getCameraClip());
         cf2.show(rf.getCameraClip());

      }
      else {
         cf.move(collisions);
         applySurface(0, 0, bgnd, screen, cf.getCameraClip());
         cf.show();

         rf1.show(cf.getCameraClip());
         rf2.show(cf.getCameraClip());
         cf1.show(cf.getCameraClip());
         cf2.show(cf.getCameraClip());
      }

      flip(screen);

      timer.delayFrame(FRAMERATE);
   }

   cleanUp();

   return 0;
}
