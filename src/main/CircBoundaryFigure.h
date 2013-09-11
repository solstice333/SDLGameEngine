/*
 * CircBoundaryFigure.h
 *
 *  Created on: Sep 10, 2013
 *      Author: knavero
 */

#ifndef CIRCBOUNDARYFIGURE_H_
#define CIRCBOUNDARYFIGURE_H_

#include "Figure.h"

class CircBoundaryFigure: public CircFigure {
public:
   CircBoundaryFigure();
   CircBoundaryFigure(int x, int y, Surface& image, SDL_Surface* screen,
         int levelWidth, int levelHeight, int numClips);
   void setFigure(int x, int y, Surface& image, SDL_Surface* screen,
         int levelWidth, int levelHeight, int numClips);
};

#endif /* CIRCBOUNDARYFIGURE_H_ */
