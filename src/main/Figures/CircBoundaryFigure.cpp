/*
 * CircBoundaryFigure.cpp
 *
 *  Created on: Sep 10, 2013
 *      Author: knavero
 */

#include "CircBoundaryFigure.h"

CircBoundaryFigure::CircBoundaryFigure() : CircFigure() {
}

CircBoundaryFigure::CircBoundaryFigure(int x, int y, Surface& image,
      SDL_Surface* screen, int levelWidth, int levelHeight, int numClips) :
      CircFigure(x, y, image, screen, GRAVITY_ENABLED, levelWidth, levelHeight,
            false, 5, 1, 1, numClips) {
}

void CircBoundaryFigure::setFigure(int x, int y, Surface& image,
      SDL_Surface* screen, int levelWidth, int levelHeight, int numClips) {
   CircFigure::setFigure(x, y, image, screen, GRAVITY_ENABLED, levelWidth,
         levelHeight, false, 5, 1, 1, numClips);
}
