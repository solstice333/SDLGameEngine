/*
 * Window.cpp
 *
 *  Created on: Aug 20, 2013
 *      Author: knavero
 */

#include "Window.h"
#include "../../main/Exception.h"
#include <iostream>

using namespace std;

Window::Window(SDL_Surface*& screen) :
      screen(screen) {
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
   //if the window focus changed
   else if (event.type == SDL_ACTIVEEVENT) {
      //if the window was iconfied or restored
      if (event.active.state & SDL_APPACTIVE) {
         //if the application is no longer active
         if (event.active.gain == 0) {
            SDL_WM_SetCaption("Window Event Test: Iconified", NULL);
            cout << "minimized" << endl;
         }
         else {
            SDL_WM_SetCaption("Window Event Test", NULL);
            cout << "restored" << endl;
         }
      }
   }
   //if something happened to the kb focus
   else if (event.active.state & SDL_APPINPUTFOCUS) {
      if (event.active.state & SDL_APPINPUTFOCUS) {
         if (event.active.gain == 0)
            SDL_WM_SetCaption("Window Event Test: Keyboard focus lost", NULL);
         else
            SDL_WM_SetCaption("Window Event Test", NULL);
      }
   }
   //if something happened to the mouse focus
   else if (event.active.state & SDL_APPMOUSEFOCUS) {
      if (event.active.gain == 0)
         SDL_WM_SetCaption("Window Event Test: Mouse Focus Lost", NULL);
      else
         SDL_WM_SetCaption("Window Event Test", NULL);
   }
   //if the window's screen has been altered (by another program outside of this one)
   else if (event.type == SDL_VIDEOEXPOSE) {
      //update the screen
      if (SDL_Flip(screen) == -1) {
         windowOK = false;
         //TODO continue implementing this here
      }
   }
}

bool Window::error() {
   return !windowOK;
}
