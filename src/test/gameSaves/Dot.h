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

class Dot {
private:
   Position p;
   int r;
   Velocity v;
   Surface* source;
   SDL_Surface* screen;

public:
   Dot();
   Dot(int x, int y, Surface& source, SDL_Surface* screen);
   void setDot(int x, int y, Surface& source, SDL_Surface* screen);
   void setPosition(int x, int y);
   void setPosition(Position p);
   Position getPosition();

   void handleInput(SDL_Event& event);
   void move();
   void show();
};

#endif /* DOT_H_ */
