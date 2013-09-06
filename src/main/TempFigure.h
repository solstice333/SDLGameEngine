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

class TempFigure : public Figure {
public:
   TempFigure(int x, int y, Surface& image, SDL_Surface* screen,
         Gravity gravityEnabled, bool leader = false, double speed = 5,
         double gravity = 1, double jumpStrength = 1, int numClips = 1,
         int levelWidth = -1, int levelHeight = -1, Surface* p1 = NULL,
         Surface* p2 = NULL, Surface* p3 = NULL, Surface* p4 = NULL,
         Figure::Resolves resolve = BOUNDARY);
   Marker show(SDL_Rect* otherCamera = NULL);

};

#endif /* TEMPFIGURE_H_ */
