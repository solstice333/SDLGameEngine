/*
 * Dot.cpp
 *
 *  Created on: Aug 18, 2013
 *      Author: knavero
 */
#include "Dot.h"

Dot::Dot() {
}

Dot::Dot(int x, int y, Surface& source, SDL_Surface* screen) :
      source(&source), screen(screen) {
   p.x = p.y = v.x = v.y = 0;

   if (source.getSDL_Surface()->w > source.getSDL_Surface()->h)
      r = source.getSDL_Surface()->w / 2;
   else
      r = source.getSDL_Surface()->h / 2;
}

void Dot::setDot(int x, int y, Surface& source, SDL_Surface* screen) {
   this->source = &source;
   this->screen = screen;
   p.x = x;
   p.y = y;
   v.x = v.y = 0;

   if (source.getSDL_Surface()->w > source.getSDL_Surface()->h)
      r = source.getSDL_Surface()->w / 2;
   else
      r = source.getSDL_Surface()->h / 2;
}

void Dot::setPosition(int x, int y) {
   p.x = x;
   p.y = y;
}

void Dot::setPosition(Position p) {
   this->p.x = p.x;
   this->p.y = p.y;
}

Position Dot::getPosition() {
   return p;
}

void Dot::handleInput(SDL_Event& event) {
   if (event.type == SDL_KEYDOWN) {
      switch (event.key.keysym.sym) {
      case SDLK_UP:
         v.y -= source->getSDL_Surface()->h / 2;
         break;
      case SDLK_DOWN:
         v.y += source->getSDL_Surface()->h / 2;
         break;
      case SDLK_LEFT:
         v.x -= source->getSDL_Surface()->w / 2;
         break;
      case SDLK_RIGHT:
         v.x += source->getSDL_Surface()->w / 2;
         break;
      default:
         break;
      }
   }
   else if (event.type == SDL_KEYUP) {
      switch (event.key.keysym.sym) {
      case SDLK_UP:
         v.y += source->getSDL_Surface()->h / 2;
         break;
      case SDLK_DOWN:
         v.y -= source->getSDL_Surface()->h / 2;
         break;
      case SDLK_LEFT:
         v.x += source->getSDL_Surface()->w / 2;
         break;
      case SDLK_RIGHT:
         v.x -= source->getSDL_Surface()->w / 2;
         break;
      default:
         break;
      }
   }
}

void Dot::move() {
   p.x += v.x;

   if ((p.x < r) || (p.x > screen->w - r))
      p.x -= v.x;

   p.y += v.y;
   if ((p.y < r) || (p.y > screen->h - r))
      p.y -= v.y;
}

void Dot::show() {
   applySurface(p.x - r, p.y - r, *source, screen);
}
