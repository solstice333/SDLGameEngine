/*
 * CursorFigure.cpp
 *
 *  Created on: Sep 12, 2013
 *      Author: knavero
 */

#include "CursorFigure.h"

CursorFigure::CursorFigure() :
      offset(NULL) {
}

CursorFigure::CursorFigure(int x, int y, Surface& image, SDL_Surface* screen,
      SDL_Rect* offset) :
      CircFigure(x, y, image, screen, GRAVITY_DISABLED), offset(offset) {
}

void CursorFigure::setFigure(int x, int y, Surface& image, SDL_Surface* screen,
      SDL_Rect* offset) {
   Figure::setFigure(x, y, image, screen, GRAVITY_DISABLED);
   this->offset = offset;
}

void CursorFigure::handleInput(SDL_Event& event) {
   if (event.type == SDL_MOUSEMOTION) {
      p.x = event.button.x + offset->x;
      p.y = event.button.y + offset->y;
   }
}

void CursorFigure::move(vector<Figure*>& other, int deltaTicks) {
   //TODO change collision detection to detect only GrabbableFigures
   int x, y;
   SDL_GetMouseState(&x, &y);
   p.x = static_cast<double>(x) + offset->x;
   p.y = static_cast<double>(y) + offset->y;

   int count = 0;

   if (isCollided(other, count) && count != -1) {
      cout << "collided" << endl;
      cout << "count: " << count << endl;
   }
}

void CursorFigure::show(SDL_Rect* otherCamera) {
   applySurface(static_cast<int>(p.x) - r - offset->x,
         static_cast<int>(p.y) - r - offset->y, *image, screen, &cl[0]);
}
