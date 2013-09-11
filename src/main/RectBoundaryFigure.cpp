/*
 * RectBoundaryFigure.cpp
 *
 *  Created on: Sep 10, 2013
 *      Author: knavero
 */

#include "RectBoundaryFigure.h"

RectBoundaryFigure::RectBoundaryFigure() {
}

RectBoundaryFigure::RectBoundaryFigure(int x, int y, Surface& image,
      SDL_Surface* screen, int levelWidth, int levelHeight, int numClips) :
      RectFigure(x, y, image, screen, GRAVITY_ENABLED, levelWidth, levelHeight,
            false, 5, 1, 1, numClips) {
}

void RectBoundaryFigure::setFigure(int x, int y, Surface& image,
      SDL_Surface* screen, int levelWidth, int levelHeight, int numClips) {
   Figure::setFigure(x, y, image, screen, GRAVITY_ENABLED, levelWidth,
         levelHeight, false, 5, 1, 1, numClips);
}
