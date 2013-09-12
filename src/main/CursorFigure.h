/*
 * CursorFigure.h
 *
 *  Created on: Sep 12, 2013
 *      Author: knavero
 */

#ifndef CURSORFIGURE_H_
#define CURSORFIGURE_H_

#include "Figure.h"
#include "SDLAbstractionLayer.h"

class CursorFigure : public CircFigure {
public:
   CursorFigure();
   CursorFigure(int x, int y, Surface& image, SDL_Surface* screen);
   void setFigure(int x, int y, Surface& image, SDL_Surface* screen);
};

#endif /* CURSORFIGURE_H_ */
