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
const double SPEED = 1;
const int GRAVITY = 1;
const double JUMPSTRENGTH = 2.5;
const bool GRAVITY_ENABLED = true;

int main(int argc, char* argv[]) {
   SDL_Surface* screen = init(WIDTH, HEIGHT, "SDL Motion");
   //Surface dot("images/lesson16/dot.bmp", Surface::WHITE);
   //Figure dotFigure(dot, dot, screen);

   Surface bgnd("images/bgnd.jpg");
   Surface left("images/x97_left.png", Surface::RED);
   Surface right("images/x97_right.png", Surface::RED);
   vector<Figure> v;

   Figure slug;

   if (GRAVITY_ENABLED)
      slug.setFigure(0, screen->h - right.getSDL_Surface()->h, left, right, screen,
           Figure::GRAVITY_ENABLED, SPEED, GRAVITY, JUMPSTRENGTH);
   else
      slug.setFigure(0, screen->h - right.getSDL_Surface()->h, left, right, screen,
            Figure::GRAVITY_DISABLED, SPEED, GRAVITY, JUMPSTRENGTH);

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

         //dotFigure.handleInput(event);
         slug.handleInput(event);

      }

      //fillScreen(screen, Surface::CYAN);
      //dotFigure.move();
      //dotFigure.show();

      applySurface(0, 0, bgnd, screen);
      slug.move(v);
      slug.show();

      flip(screen);

      if (fps.getTicks() < 1000 / FPS)
         SDL_Delay(1000 / FPS - fps.getTicks());
   }

   cleanUp();

   return 0;
}
