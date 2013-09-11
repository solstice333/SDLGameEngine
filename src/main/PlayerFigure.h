/*
 * PlayerFigure.h
 *
 *  Created on: Sep 10, 2013
 *      Author: knavero
 */

#ifndef PLAYERFIGURE_H_
#define PLAYERFIGURE_H_

#include "Figure.h"
#include "RectBoundaryFigure.h"
#include "CircBoundaryFigure.h"

class PlayerFigure: public RectFigure {
public:
   PlayerFigure();

   PlayerFigure(int x, int y, Surface& image, SDL_Surface* screen,
         double speed, double gravity, double jumpStrength,
         int numClips, int levelWidth, int levelHeight,
         Surface * p1 = NULL, Surface* p2 = NULL, Surface* p3 = NULL,
         Surface* p4 = NULL);

   void setFigure(int x, int y, Surface& image, SDL_Surface* screen,
         double speed, double gravity, double jumpStrength,
         int numClips, int levelWidth, int levelHeight,
         Surface * p1 = NULL, Surface* p2 = NULL, Surface* p3 = NULL,
         Surface* p4 = NULL);

   virtual void resolveCollision(Figure* other, double timeStep, Component dir);
};

#endif /* PLAYERFIGURE_H_ */
