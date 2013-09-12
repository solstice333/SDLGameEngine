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

class CursorFigure: public CircFigure {
   SDL_Rect* offset;
public:
   CursorFigure();
   CursorFigure(int x, int y, Surface& image, SDL_Surface* screen,
         SDL_Rect* offset);
   virtual void setFigure(int x, int y, Surface& image, SDL_Surface* screen,
         SDL_Rect* offset);
   virtual void handleInput(SDL_Event& event);
   virtual void move(vector<Figure*>& other, int deltaTicks);
   virtual void show(SDL_Rect* otherCamera = NULL);
};

#endif /* CURSORFIGURE_H_ */
