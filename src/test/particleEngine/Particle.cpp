/*
 * Particle.cpp
 *
 *  Created on: Aug 22, 2013
 *      Author: knavero
 */

#include "Particle.h"
#include <iostream>

Particle::Particle(int x, int y, Surface* p1, Surface* p2, Surface* p3,
      Surface* p4, SDL_Surface* screen) :
      p1(p1), p2(p2), p3(p3), p4(p4), screen(screen) {
   //set offsets
   p.x = x + randRange(-5, 20);
   p.y = y + randRange(-5, 20);

   //init animation frame
   frame = randRange(0, 4);

   //set type
   switch (randRange(0, 2)) {
   case 0:
      type = this->p1;
      break;
   case 1:
      type = this->p2;
      break;
   case 2:
      type = this->p3;
      break;
   default:
      break;
   }
}

void Particle::show() {
   //show image
   applySurface(p.x, p.y, *type, screen);

   //show shimmer
   if (frame % 2 == 0)
      applySurface(p.x, p.y, *p4, screen);

   frame++;
}

bool Particle::isDead() {
   if (frame > 10)
      return true;
   return false;
}
