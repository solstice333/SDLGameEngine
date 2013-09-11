/*
 * RectBoundaryFigure.h
 *
 *  Created on: Sep 10, 2013
 *      Author: knavero
 */

#ifndef RECTBOUNDARYFIGURE_H_
#define RECTBOUNDARYFIGURE_H_

#include "Figure.h"

class RectBoundaryFigure: public RectFigure {
public:
   RectBoundaryFigure();
   RectBoundaryFigure(int x, int y, Surface& image, SDL_Surface* screen,
         int levelWidth, int levelHeight, int numClips);
   void setFigure(int x, int y, Surface& image, SDL_Surface* screen,
         int levelWidth, int levelHeight, int numClips);
};

#endif /* RECTBOUNDARYFIGURE_H_ */
