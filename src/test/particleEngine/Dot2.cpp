/*
 * Dot.cpp
 *
 *  Created on: Aug 18, 2013
 *      Author: knavero
 */
#include "Dot2.h"

Dot2::Dot2(int x, int y, Surface& source, Surface& p1, Surface& p2, Surface& p3,
      Surface& p4, SDL_Surface* screen) :
      source(&source), screen(screen) {
   p.x = x;
   p.y = y;
   v.x = v.y = 0;

   this->p1 = &p1;
   this->p2 = &p2;
   this->p3 = &p3;
   this->p4 = &p4;

   for (int p = 0; p < TOTAL_PARTICLES; p++) {
      particles[p] = new Particle(x, y, this->p1, this->p2, this->p3, this->p4,
            screen);
   }

   if (source.getSDL_Surface()->w > source.getSDL_Surface()->h)
      r = source.getSDL_Surface()->w / 2;
   else
      r = source.getSDL_Surface()->h / 2;
}

void Dot2::handleInput(SDL_Event& event) {
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

void Dot2::move() {
   p.x += v.x;

   if ((p.x < r) || (p.x > screen->w - r))
      p.x -= v.x;

   p.y += v.y;
   if ((p.y < r) || (p.y > screen->h - r))
      p.y -= v.y;
}

void Dot2::show() {
   applySurface(p.x - r, p.y - r, *source, screen);
   showParticles();
}

void Dot2::showParticles() {
   for (int i = 0; i < TOTAL_PARTICLES; i++) {
      if (particles[i]->isDead()) {
         delete particles[i];
         particles[i] = new Particle(p.x - r, p.y - r, p1, p2, p3, p4, screen);
      }

      particles[i]->show();
   }
}

Dot2::~Dot2() {
   for (int i = 0; i < TOTAL_PARTICLES; i++) {
      delete particles[i];
   }
}
