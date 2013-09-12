/*
 * CursorFigure.cpp
 *
 *  Created on: Sep 12, 2013
 *      Author: knavero
 */

#include "CursorFigure.h"

CursorFigure::CursorFigure() {
}

CursorFigure::CursorFigure(int x, int y, Surface& image, SDL_Surface* screen) :
      CircFigure(x, y, image, screen, GRAVITY_DISABLED) {
}

void CursorFigure::setFigure(int x, int y, Surface& image, SDL_Surface* screen) {
   Figure::setFigure(x, y, image, screen, GRAVITY_DISABLED);
}
