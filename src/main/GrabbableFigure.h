/*
 * GrabbableFigure.h
 *
 *  Created on: Sep 10, 2013
 *      Author: knavero
 */

#ifndef GRABBABLEFIGURE_H_
#define GRABBABLEFIGURE_H_

#include "RectBoundaryFigure.h"

/*
 * TODO: the idea here is that the Player can extend his/her arm in a grappling hook
 * fashion and then grab the GrabbableFigure object and then pull himself/herself towards
 * that object
 */
class GrabbableFigure: public RectBoundaryFigure {
public:
   GrabbableFigure();
   GrabbableFigure(int x, int y, Surface& image, SDL_Surface* screen,
         int levelWidth, int levelHeight, int numClips);
};

#endif /* GRABBABLEFIGURE_H_ */
