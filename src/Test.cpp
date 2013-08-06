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
const double SPEED = 25;
const int GRAVITY = 1;
const double JUMPSTRENGTH = 1;
//const bool GRAVITY_ENABLED = true;

int main(int argc, char* argv[]) {
   SDL_Surface* screen = init(WIDTH, HEIGHT, "SDL Motion");

   /*
    Surface bgnd("images/bgnd.jpg");
    Surface left("images/x97_left.png", Surface::RED);
    Surface right("images/x97_right.png", Surface::RED);
    */

   vector<Figure> f;

   Surface rect("images/rectangle.png");

   Figure rectFig(500, 100, rect, screen, Figure::GRAVITY_DISABLED);
   Figure rectFig5(800, 250, rect, screen,
         Figure::GRAVITY_DISABLED);

   Surface circ("images/dot.bmp", Surface::CYAN);
   Figure circFig(900, screen->h - circ.getSDL_Surface()->h, circ, screen,
         Figure::GRAVITY_DISABLED);

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

   Figure squareFig(100, 0, square, screen, Figure::GRAVITY_ENABLED, SPEED,
         JUMPSTRENGTH);

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

      f.clear();
      f.push_back(rectFig);
      f.push_back(rectFig5);
      f.push_back(circFig);

      squareFig.move(f);

      rectFig5.show();
      rectFig.show();
      circFig.show();
      squareFig.show();

      flip(screen);

      fps.delayFrame(FPS);
   }

   cleanUp();

   return 0;
}
