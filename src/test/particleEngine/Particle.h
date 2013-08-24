/*
 * Particle.h
 *
 *  Created on: Aug 22, 2013
 *      Author: knavero
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "../../main/SDLAbstractionLayer.h"

class Particle {
private:
   Position p;
   int frame;
   Surface* type;
   Surface* p1;
   Surface* p2;
   Surface* p3;
   Surface* p4;
   SDL_Surface* screen;

public:
   Particle(int x, int y, Surface* p1, Surface* p2, Surface* p3, Surface* p4,
         SDL_Surface* screen);
   void show();
   bool isDead();
};

#endif /* PARTICLE_H_ */
