/*
 * GrabbableFigure.h
 *
 *  Created on: Sep 10, 2013
 *      Author: knavero
 */

#ifndef GRABBABLEFIGURE_H_
#define GRABBABLEFIGURE_H_

#include "RectBoundaryFigure.h"

class GrabbableFigure: public RectBoundaryFigure {
public:
   GrabbableFigure();
   GrabbableFigure(int x, int y, Surface& image, SDL_Surface* screen,
         int levelWidth, int levelHeight, int numClips);
};

#endif /* GRABBABLEFIGURE_H_ */
