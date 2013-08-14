//============================================================================
// Name        : SDLAnimation.cpp
// Author      : Kevin Navero
// Version     :
// Copyright   : 
// Description :
//============================================================================

#include <iostream>
#include "SDL/SDL.h"
#include "SDLAbstractionLayer.h"

using namespace std;

const int FRAMERATECAP = 40;
const double SPEED = 5;
const double JUMPSTRENGTH = 0.5;
const int GRAVITY = 1;
const int NUMCLIPS_DOT = 1;
const int NUMCLIPS_FOO = 4;
const bool CHOOSE_FOO = true;

/*
 * Description: this is a sanity test to verify constructors, setFigure methods, and collision
 * detection characteristics with the additional animation features. The user
 * can change the const bool CHOOSE_FOO to either true or false, to model CircFigure or
 * RectFigure animation capabilities.
 */
int main(int argc, char* argv[]) {
   SDL_Surface* screen = init(640, 640, "SDL Animation Testing");

   Surface foo("images/foo.png", Surface::CYAN);
   Surface dot("images/dot.png", Surface::CYAN);

   RectFigure fooFig;
   CircFigure circFig;

   //test constructors
   /*
   RectFigure fooFig(0, screen->h - foo.getSDL_Surface()->h, foo, screen,
            Figure::GRAVITY_ENABLED, SPEED, GRAVITY, JUMPSTRENGTH,
            NUMCLIPS_FOO);
   CircFigure circFig(0, screen->h - dot.getSDL_Surface()->h, dot, screen,
         Figure::GRAVITY_ENABLED, SPEED*4, GRAVITY, JUMPSTRENGTH * 2,
         NUMCLIPS_DOT);
         */

   if (CHOOSE_FOO)
      fooFig.setFigure(0, screen->h - foo.getSDL_Surface()->h, foo, screen,
            Figure::GRAVITY_ENABLED, SPEED, GRAVITY, JUMPSTRENGTH,
            NUMCLIPS_FOO);
   else
      circFig.setFigure(0, screen->h - dot.getSDL_Surface()->h, dot, screen,
            Figure::GRAVITY_ENABLED, SPEED*4, GRAVITY, JUMPSTRENGTH * 2,
            NUMCLIPS_DOT);

   Surface rectangle("images/rectangle.png");
   Surface circle("images/dot.png", Surface::CYAN);
   RectFigure rf(300, 200, rectangle, screen, Figure::GRAVITY_DISABLED);
   RectFigure rf1(500, 500, rectangle, screen, Figure::GRAVITY_DISABLED);
   CircFigure cf(250, 200, circle, screen, Figure::GRAVITY_DISABLED);
   CircFigure cf1(100, 600, circle, screen, Figure::GRAVITY_DISABLED);

   bool quit = false;
   SDL_Event event;
   Timer timer;
   vector<Figure*> coll;

   coll.push_back(&rf);
   coll.push_back(&rf1);
   coll.push_back(&cf);
   coll.push_back(&cf1);

   while (!quit) {
      timer.start();

      if (SDL_PollEvent(&event)) {
         if (event.type == SDL_QUIT) {
            quit = false;
            break;
         }

         if (CHOOSE_FOO)
            fooFig.handleInput(event);
         else
            circFig.handleInput(event);
      }

      if (CHOOSE_FOO)
         fooFig.move(coll);
      else
         circFig.move(coll);

      fillScreen(screen, Surface::WHITE);
      rf.show();
      rf1.show();
      cf.show();
      cf1.show();

      if (CHOOSE_FOO)
         fooFig.show();
      else
         circFig.show();

      flip(screen);

      timer.delayFrame(FRAMERATECAP);
   }

   return 0;
}
