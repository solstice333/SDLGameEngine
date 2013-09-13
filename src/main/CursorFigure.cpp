/*
 * CursorFigure.cpp
 *
 *  Created on: Sep 12, 2013
 *      Author: knavero
 */

#include "CursorFigure.h"

CursorFigure::CursorFigure() :
      offset(NULL), gf(NULL) {
}

CursorFigure::CursorFigure(int x, int y, Surface& image, SDL_Surface* screen,
      SDL_Rect* offset) :
      CircFigure(x, y, image, screen, GRAVITY_DISABLED), offset(offset), grabbable(
            false), grabstate(false), gf(NULL) {
}

void CursorFigure::setFigure(int x, int y, Surface& image, SDL_Surface* screen,
      SDL_Rect* offset) {
   Figure::setFigure(x, y, image, screen, GRAVITY_DISABLED);
   this->offset = offset;
   grabbable = grabstate = false;
   gf = NULL;
}

void CursorFigure::setGrabState(bool grabstate) {
   this->grabstate = grabstate;
}

bool CursorFigure::getGrabState() {
   return grabstate;
}

GrabbableFigure* CursorFigure::getGrabbableFigure() {
   return gf;
}

void CursorFigure::handleInput(SDL_Event& event) {
   if (event.type == SDL_MOUSEMOTION) {
      p.x = event.button.x + offset->x;
      p.y = event.button.y + offset->y;
   }
   if (event.type == SDL_MOUSEBUTTONDOWN) {
      if (event.button.button == SDL_BUTTON_LEFT && grabbable)
         grabstate = true;
   }
}

void CursorFigure::move(vector<Figure*>& other, int deltaTicks) {
   int x, y;
   SDL_GetMouseState(&x, &y);
   p.x = static_cast<double>(x) + offset->x;
   p.y = static_cast<double>(y) + offset->y;

   int count = 0;

   if (isCollided(other, count)
         && typeid(*other[count]) == typeid(GrabbableFigure) && count != -1) {
      grabbable = true;
      gf = static_cast<GrabbableFigure*>(other[count]);
   }
   else
      grabbable = false;
}

void CursorFigure::show(SDL_Rect* otherCamera) {
   applySurface(static_cast<int>(p.x) - r - offset->x,
         static_cast<int>(p.y) - r - offset->y, *image, screen, &cl[0]);
}
