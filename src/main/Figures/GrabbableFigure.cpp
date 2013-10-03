/*
 * GrabbableFigure.cpp
 *
 *  Created on: Sep 10, 2013
 *      Author: knavero
 */

#include "GrabbableFigure.h"

GrabbableFigure::GrabbableFigure() : RectBoundaryFigure() {
}

GrabbableFigure::GrabbableFigure(int x, int y, Surface& image,
      SDL_Surface* screen, int levelWidth, int levelHeight, int numClips) :
      RectBoundaryFigure(x, y, image, screen, levelWidth, levelHeight, numClips) {
}

