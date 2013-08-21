/*
 * Window.cpp
 *
 *  Created on: Aug 20, 2013
 *      Author: knavero
 */

#include "Window.h"
#include "../main/Exception.h"
#include <iostream>

using namespace std;

Window::Window(SDL_Surface*& screen, int initWidth, int initHeight) :
      screen(screen) {
   this->screen = SDL_SetVideoMode(initWidth, initHeight, 32,
   SDL_SWSURFACE);
   dims.w = this->screen->w;
   dims.h = this->screen->h;

   if (screen == NULL) {
      windowOK = false;
      throw SetVideoModeException();
   }
   else
      windowOK = true;

   SDL_WM_SetCaption("Window Event Test", NULL);

   windowed = true;
}

void Window::toggleFullscreen() {
   if (windowed) {
      screen = SDL_SetVideoMode(screen->w, screen->h, 32,
      SDL_SWSURFACE | SDL_FULLSCREEN);
      if (screen == NULL) {
         windowOK = false;
         throw SetVideoModeException();
      }

      windowed = false;
   }
   else if (!windowed) {
      screen = SDL_SetVideoMode(screen->w, screen->h, 32,
      SDL_SWSURFACE);
      if (screen == NULL) {
         windowOK = false;
         throw SetVideoModeException();
      }

      windowed = true;
   }
}

void Window::handleEvents(SDL_Event& event) {
   if (!windowOK)
      throw WindowException();
   if (event.type == SDL_KEYDOWN) {
      switch (event.key.keysym.sym) {
      case SDLK_1:
         screen = SDL_SetVideoMode(1366, 768, 32, SDL_SWSURFACE);
         break;
      case SDLK_2:
         screen = SDL_SetVideoMode(1360, 768, 32, SDL_SWSURFACE);
         break;
      case SDLK_3:
         screen = SDL_SetVideoMode(1024, 768, 32, SDL_SWSURFACE);
         break;
      case SDLK_4:
         screen = SDL_SetVideoMode(800, 600, 32, SDL_SWSURFACE);
         break;
      case SDLK_5:
         screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);
         break;
      case SDLK_6:
         toggleFullscreen();
         break;
      default:
         break;
      }

      if (screen == NULL) {
         windowOK = false;
         throw SetVideoModeException();
      }
      cout << "screen dimensions: " << screen->w << "x" << screen->h << endl;
   }
}
