/*
 * TempFigure.h
 *
 *  Created on: Sep 5, 2013
 *      Author: knavero
 */

#ifndef TEMPFIGURE_H_
#define TEMPFIGURE_H_

#include "SDLAbstractionLayer.h"
#include "Figure.h"
#include "Exception.h"

class TempFigure: public RectFigure {
public:
   enum Marker {
      ACTIVE, REMOVE, INACTIVE
   };

private:
   Marker marker;

public:
   TempFigure(int x, int y, Surface& image, SDL_Surface* screen,
         int levelWidth = -1, int levelHeight = -1);

   virtual void resolveCollision(Figure* other, double timeStep, Component dir);
   virtual void show(SDL_Rect* otherCamera = NULL);
};

#endif /* TEMPFIGURE_H_ */
