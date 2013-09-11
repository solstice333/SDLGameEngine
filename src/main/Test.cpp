//============================================================================
// Name        : SDLScrolling.cpp
// Author      : Kevin Navero
// Version     :
// Copyright   : 
// Description : SDL Scrolling Test
//============================================================================
#include <iostream>
#include "SDLAbstractionLayer.h"
#include "Exception.h"
#include "Figure.h"
#include "RectBoundaryFigure.h"
#include "CircBoundaryFigure.h"
#include "TempFigure.h"
#include "PlayerFigure.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

using namespace std;

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 550;

const int FRAMERATE = 30;

const int DOT_WIDTH = 20;
const int DOT_HEIGHT = 20;

const int LEVEL_WIDTH = 1191;
const int LEVEL_HEIGHT = 670;

const double FS = 200;
const double CS = 1200;
const double CJS = 11;
const double FJS = 7;
const double G = 4;
const int CNC = 1;
const int FNC = 4;

const bool OTHER_LEADER = false;
const double OTHER_SPEED = 0;
const double OTHER_GRAVITY = 0;
const double OTHER_JUMPSTRENGTH = 0;
const int OTHER_NUMCLIPS = 1;

const string TTF_PATH = "fonts/lazy.ttf";
const int FONT_SIZE = 28;
const Surface::Color FONT_COLOR = Surface::BLACK;

const bool FOO = true; //change this from true or false to choose between a stick figure
//or dot ("FOO = true" is the stick figure)

const Figure::Gravity gravEnDis = Figure::GRAVITY_ENABLED;
//const Figure::Gravity gravEnDis = Figure::GRAVITY_DISABLED;

const bool TEST_GRAPHICS = true;
const bool TEST_STRING_INPUT = false;

/*
 * TODO
 * Rebel - remove an object from collision map
 * and thus the scene
 *
 * Kevin - not necessary anymore since the Figures are set to INACTIVE? No need
 * to completely free memory from Figures that aren't shown anymore. Not until the
 * end of the level anyways. Any thoughts on this?
 */
/*
 void removeIndex(vector<Figure*>& vec, int i) {
 //also free the memory assoicated with the pointer too
 vec.erase(vec.begin() + i);
 }
 */

/*Description: This tests the scrolling, collision detection, static figures within the level,
 *and animation. User can switch const bool FOO to true/false and comment/uncomment const
 *Figure::Gravity gravEnDis for Enabling and Disabling gravity
 */
int main(int argc, char* argv[]) {
   if (TEST_GRAPHICS) {
      SDL_Surface* screen = init(SCREEN_WIDTH, SCREEN_HEIGHT, "SDL Scrolling");
      vector<Figure*> collisions;

      Surface bgnd("images/bgnd.jpg");
      Surface dot("images/dot.png", Surface::CYAN);
      Surface foo("images/Cyan_Final.png", Surface::BLACK);
      Surface rect("images/rectangle.png");
      Surface coin("images/coin.png", Surface::CYAN);

      Surface red("images/red.bmp", Surface::CYAN);
      Surface blue("images/blue.bmp", Surface::CYAN);
      Surface green("images/green.bmp", Surface::CYAN);
      Surface shimmer("images/shimmer.bmp", Surface::CYAN);

      RectBoundaryFigure rf1(300, 525, rect, screen, LEVEL_WIDTH, LEVEL_HEIGHT,
            OTHER_NUMCLIPS);
      RectBoundaryFigure rf2(500, 125, rect, screen, LEVEL_WIDTH, LEVEL_HEIGHT,
            OTHER_NUMCLIPS);
      CircBoundaryFigure cf1(700, 525, dot, screen, LEVEL_WIDTH, LEVEL_HEIGHT,
            OTHER_NUMCLIPS);
      CircBoundaryFigure cf2(900, 350, dot, screen, LEVEL_WIDTH, LEVEL_HEIGHT,
            OTHER_NUMCLIPS);

      TempFigure coin1(600, 325, coin, screen, LEVEL_WIDTH, LEVEL_HEIGHT);

      PlayerFigure rf;
      CircFigure cf;

      if (FOO) {
         rf.setFigure(100, LEVEL_HEIGHT - foo.getSDL_Surface()->h / 2, foo,
               screen, FS, G, FJS, FNC, LEVEL_WIDTH, LEVEL_HEIGHT, &red, &green,
               &blue, &shimmer);

         collisions.push_back(&rf);
      }
      else {
         cf.setFigure(100, 300, dot, screen, gravEnDis, LEVEL_WIDTH,
               LEVEL_HEIGHT, true, CS, G, CJS, CNC);

         collisions.push_back(&cf);
      }

      //Test constructors
      /*
       RectFigure rf(100, 300, foo, screen, gravEnDis, true, FS, G, FJS, FNC,
       LEVEL_WIDTH, LEVEL_HEIGHT, &red, &green, &blue, &shimmer);
       CircFigure cf(100, 300, dot, screen, gravEnDis, true, CS, G, CJS, CNC,
       LEVEL_WIDTH, LEVEL_HEIGHT, &red, &green, &blue, &shimmer);
       */

      bool quit = false;
      SDL_Event event;
      Timer timer;

      collisions.push_back(&rf1);
      collisions.push_back(&rf2);
      collisions.push_back(&cf1);
      collisions.push_back(&cf2);
      collisions.push_back(&coin1);

      Music m("resources/tristam.mp3");

      timer.start();

      if (Mix_PlayingMusic() == 0)
         if (Mix_PlayMusic(m.getMix_Music(), -1) < 0)
            throw SoundException();

      Mix_VolumeMusic(32); //0 to 128

      while (!quit) {
         if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
               quit = true;

            if (FOO)
               rf.handleInput(event);
            else
               cf.handleInput(event);
         }

         if (FOO) {
            rf.move(collisions, timer.getTicks());
            timer.start();

            applySurface(0, 0, bgnd, screen, rf.getCameraClip());
            rf.show(rf.getCameraClip());

            rf1.show(rf.getCameraClip());
            rf2.show(rf.getCameraClip());
            cf1.show(rf.getCameraClip());
            cf2.show(rf.getCameraClip());

            coin1.move(collisions, 0);
            coin1.show(rf.getCameraClip());
         }
         else {
            cf.move(collisions, timer.getTicks());
            timer.start();

            applySurface(0, 0, bgnd, screen, cf.getCameraClip());
            cf.show();

            rf1.show(cf.getCameraClip());
            rf2.show(cf.getCameraClip());
            cf1.show(cf.getCameraClip());
            cf2.show(cf.getCameraClip());
         }

         flip(screen);
      }

      Mix_HaltMusic();
   }

   cleanUp();

   return 0;
}
