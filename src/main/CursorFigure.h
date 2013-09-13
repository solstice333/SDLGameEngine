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
#include "GrabbableFigure.h"

class CursorFigure: public CircFigure {
   //Don't try to clean this up. The data that this pointer points to will automatically
   //get deleted by the virtual destructors belonging to PlayerFigure
   SDL_Rect* offset;

   //Don't try to clean this up. The data that this pointer points to will automatically
   //get deleted by the virtual destructors belonging to GrabbableFigure
   GrabbableFigure* gf;

   bool grabbable;
   bool grabstate;

public:
   CursorFigure();
   CursorFigure(int x, int y, Surface& image, SDL_Surface* screen,
         SDL_Rect* offset);
   virtual void setFigure(int x, int y, Surface& image, SDL_Surface* screen,
         SDL_Rect* offset);
   void setGrabState(bool grabstate);
   bool getGrabState();
   GrabbableFigure* getGrabbableFigure();
   virtual void handleInput(SDL_Event& event);
   virtual void move(vector<Figure*>& other, int deltaTicks);
   virtual void show(SDL_Rect* otherCamera = NULL);
};

#endif /* CURSORFIGURE_H_ */
