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

const double FS = 150;
const double CS = 1200;
const double CJS = 11;
const double FJS = 10;
const double G = 4;
const int CNC = 1;
const int FNC = 4;

const string TTF_PATH = "fonts/lazy.ttf";
const int FONT_SIZE = 28;
const Surface::Color FONT_COLOR = Surface::BLACK;

const bool FOO = true; //change this from true or false to choose between a stick figure
//or dot ("FOO = true" is the stick figure)

const Figure::Gravity gravEnDis = Figure::GRAVITY_ENABLED;
//const Figure::Gravity gravEnDis = Figure::GRAVITY_DISABLED;

const bool TEST_GRAPHICS = true;
const bool TEST_STRING_INPUT = true;

/*Description: This tests the scrolling, collision detection, static figures within the level,
 *and animation. User can switch const bool FOO to true/false and comment/uncomment const
 *Figure::Gravity gravEnDis for Enabling and Disabling gravity
 */
int main(int argc, char* argv[]) {
   if (TEST_GRAPHICS) {
      SDL_Surface* screen = init(SCREEN_WIDTH, SCREEN_HEIGHT, "SDL Scrolling");

      Surface bgnd("images/bgnd.jpg");
      Surface dot("images/dot.png", Surface::CYAN);
      Surface foo("images/Cyan_Final.png", Surface::BLACK);
      Surface rect("images/rectangle.png");

      Surface red("images/red.bmp", Surface::CYAN);
      Surface blue("images/blue.bmp", Surface::CYAN);
      Surface green("images/green.bmp", Surface::CYAN);
      Surface shimmer("images/shimmer.bmp", Surface::CYAN);

      RectFigure rf1(300, 525, rect, screen, Figure::GRAVITY_DISABLED, false, 0,
            0, 0, 1, LEVEL_WIDTH, LEVEL_HEIGHT, &red, &shimmer);
      RectFigure rf2(500, 125, rect, screen, Figure::GRAVITY_DISABLED, false, 0,
            0, 0, 1, LEVEL_WIDTH, LEVEL_HEIGHT);
      CircFigure cf1(700, 525, dot, screen, Figure::GRAVITY_DISABLED, false, 0,
            0, 0, 1, LEVEL_WIDTH, LEVEL_HEIGHT);
      CircFigure cf2(900, 350, dot, screen, Figure::GRAVITY_DISABLED, false, 0,
            0, 0, 1, LEVEL_WIDTH, LEVEL_HEIGHT, &red, &green, &blue, &shimmer);

      RectFigure rf;
      CircFigure cf;

      if (FOO)
         rf.setFigure(100, 300, foo, screen, gravEnDis, true, FS, G, FJS, FNC,
               LEVEL_WIDTH, LEVEL_HEIGHT, &red, &green, &blue, &shimmer);
      else
         cf.setFigure(100, 300, dot, screen, gravEnDis, true, CS, G, CJS, CNC,
               LEVEL_WIDTH, LEVEL_HEIGHT);

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
      vector<Figure*> collisions;
      collisions.push_back(&rf1);
      collisions.push_back(&rf2);
      collisions.push_back(&cf1);
      collisions.push_back(&cf2);

      Music m("resources/tristam.mp3");

      timer.start();

      if (Mix_PlayingMusic() == 0)
         if (Mix_PlayMusic(m.getMix_Music(), -1) < 0)
            throw SoundException();

      Mix_VolumeMusic(32); //0 to 128

      while (!quit) {
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
            rf.move(collisions, timer.getTicks());
            timer.start();

            applySurface(0, 0, bgnd, screen, rf.getCameraClip());
            rf.show(rf.getCameraClip());

            rf1.show(rf.getCameraClip());
            rf2.show(rf.getCameraClip());
            cf1.show(rf.getCameraClip());
            cf2.show(rf.getCameraClip());

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

      if (TEST_STRING_INPUT) {
         quit = false;
         bool nameEntered = false;

         StringInput name(TTF_PATH, FONT_SIZE, FONT_COLOR, screen);
         Surface msg(TTF_PATH, FONT_SIZE, FONT_COLOR,
               "New High Score! Enter Name: ");

         fillScreen(screen, Surface::WHITE);
         applySurface(getHorizontalMiddlePosition(msg, screen), 100, msg,
               screen);
         flip(screen);

         while (!quit) {
            if (SDL_PollEvent(&event)) {
               if (event.type == SDL_QUIT) {
                  quit = true;
                  break;
               }

               if (!nameEntered) {
                  name.handleInput(event);

                  if (event.type == SDL_KEYDOWN
                        && event.key.keysym.sym == SDLK_RETURN) {
                     nameEntered = true;
                     msg.setSDL_Surface(TTF_PATH, FONT_SIZE, FONT_COLOR,
                           "Rank 1st: ");
                     quit = true;
                  }
               }

               fillScreen(screen, Surface::WHITE);
               applySurface(getHorizontalMiddlePosition(msg, screen), 100, msg,
                     screen);
               name.showCentered();

               flip(screen);

               if (nameEntered)
                  SDL_Delay(500);
            }
         }
      }
   }

   cleanUp();

   return 0;
}
