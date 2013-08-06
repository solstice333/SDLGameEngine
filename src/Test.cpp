//============================================================================
// Name        : SDLMotion.cpp
// Author      : Kevin Navero
// Version     :
// Copyright   : 
// Description :
//============================================================================

#include <iostream>
#include <string>
#include <sstream>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include "SDLAbstractionLayer.h"

using namespace std;

const int WIDTH = 1191;
const int HEIGHT = 670;
const int FPS = 50;
const double SPEED = 35;
const int GRAVITY = 2;
const double JUMPSTRENGTH = 25;
//const bool GRAVITY_ENABLED = true;

int main(int argc, char* argv[]) {
   SDL_Surface* screen = init(WIDTH, HEIGHT, "SDL Motion");

   /*
    Surface bgnd("images/bgnd.jpg");
    Surface left("images/x97_left.png", Surface::RED);
    Surface right("images/x97_right.png", Surface::RED);
    */

   vector<Figure> f;
   vector<Figure> empty;

   Surface rect("images/rectangle.png");
   Figure rectFig(100, 5, rect, screen, Figure::GRAVITY_ENABLED);
   Figure rectFig2(1000, 5, rect, screen, Figure::GRAVITY_ENABLED);

   Surface circ("images/dot.bmp", Surface::CYAN);
   Figure circFig(900, 240, circ, screen, Figure::GRAVITY_ENABLED);

   f.push_back(rectFig);
   f.push_back(rectFig2);
   f.push_back(circFig);

   /*
    Figure slug;

    if (GRAVITY_ENABLED)
    slug.setFigure(350, screen->h - right.getSDL_Surface()->h, left, right,
    screen, Figure::GRAVITY_ENABLED, SPEED, GRAVITY, JUMPSTRENGTH);
    else
    slug.setFigure(350, screen->h - right.getSDL_Surface()->h, left, right,
    screen, Figure::GRAVITY_DISABLED, SPEED, GRAVITY, JUMPSTRENGTH);
    */

   Surface square("images/square.bmp");
   SDL_Rect clip;
   clip.w = 20;
   clip.h = 20;

   Figure squareFig(getHorizontalMiddlePosition(square, screen),
         getVerticalMiddlePosition(square, screen), square, screen,
         Figure::GRAVITY_ENABLED, SPEED);

   Timer fps;

   bool quit = false;
   SDL_Event event;

   while (!quit) {
      fps.start();

      while (SDL_PollEvent(&event)) {
         if (event.type == SDL_QUIT) {
            quit = true;
            break;
         }

         squareFig.handleInput(event);
      }

      //applySurface(0, 0, bgnd, screen);
      fillScreen(screen, Surface::WHITE);
      rectFig.move(empty);
      rectFig2.move(empty);
      circFig.move(empty);

      f.clear();
      f.push_back(rectFig);
      f.push_back(rectFig2);
      f.push_back(circFig);

      squareFig.move(f);

      rectFig.show();
      rectFig2.show();
      circFig.show();
      squareFig.show();

      flip(screen);

      fps.delayFrame(FPS);
   }

   cleanUp();

   return 0;
}
