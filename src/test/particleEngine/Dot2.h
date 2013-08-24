/*
 * Dot.h
 *
 *  Created on: Aug 18, 2013
 *      Author: knavero
 */

#ifndef DOT_H_
#define DOT_H_

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "../../main/SDLAbstractionLayer.h"
#include "Particle.h"

//adjust the amount of particles here
const int TOTAL_PARTICLES = 10;

class Dot2 {
private:
   Position p;
   int r;
   Velocity v;
   Particle* particles[TOTAL_PARTICLES];
   Surface* source;
   Surface* p1;
   Surface* p2;
   Surface* p3;
   Surface* p4;
   SDL_Surface* screen;

public:
   Dot2(int x, int y, Surface& source, Surface& p1, Surface& p2, Surface& p3,
         Surface& p4, SDL_Surface* screen);

   void handleInput(SDL_Event& event);
   void move();
   void showParticles();
   void show();

   ~Dot2();
};

#endif /* DOT_H_ */
