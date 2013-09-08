/*
 * TempFigure.cpp
 *
 *  Created on: Sep 5, 2013
 *      Author: knavero
 */

#include "TempFigure.h"

TempFigure::TempFigure() {}

TempFigure::TempFigure(int x, int y, Surface& image, SDL_Surface* screen,
      int levelWidth, int levelHeight) :
      RectFigure(x, y, image, screen, GRAVITY_DISABLED, levelWidth, levelHeight,
            false, 5, 1, 1, 1, POINT), marker(ACTIVE) {
}

void TempFigure::setFigure(int x, int y, Surface& image, SDL_Surface* screen,
      int levelWidth, int levelHeight) {
   Figure::setFigure(x, y, image, screen, GRAVITY_DISABLED, levelWidth, levelHeight,
            false, 5, 1, 1, 1, POINT);
   marker = ACTIVE;
}

void TempFigure::resolveCollision(Figure* other, double timeStep,
      enum Component dir) {
   switch (this->resolution) {
   case (POINT):
      switch (other->getResolution()) {
      case (PLAYER):
         this->marker = REMOVE;
         break;
      default:
         break;
      }
      break;
   default:
      break;
   }
}

void TempFigure::show(SDL_Rect* otherCamera) {
   if (marker == INACTIVE)
      return;
   else if (marker == REMOVE) {
      bool animationDone = false;
      marker = INACTIVE;

      if (animationDone)
         //TODO: Add animation and sound for this
         //do a special animation if needed for however many frames
         return;
   }
   else if (marker == ACTIVE) {
      if (numClips > 0) {
         if (v.x < 0) {
            status = LEFT;
            animationFrame += AFVALUE;
         }
         else if (v.x > 0) {
            status = RIGHT;
            animationFrame += AFVALUE;
         }
         else
            animationFrame = 0;

         if (animationFrame >= numClips)
            animationFrame = 0;

         if (leader) {
            if (status == LEFT)
               applySurface((int) p.x - camera->x, (int) p.y - camera->y,
                     *image, screen, &cl[static_cast<int>(animationFrame)]);
            else if (status == RIGHT)
               applySurface((int) p.x - camera->x, (int) p.y - camera->y,
                     *image, screen, &cr[static_cast<int>(animationFrame)]);

            if (particleEffects)
               showParticles(camera);
         }
         else {
            if (status == LEFT)
               applySurface((int) p.x - otherCamera->x,
                     (int) p.y - otherCamera->y, *image, screen,
                     &cl[static_cast<int>(animationFrame)]);
            else if (status == RIGHT)
               applySurface((int) p.x - otherCamera->x,
                     (int) p.y - otherCamera->y, *image, screen,
                     &cr[static_cast<int>(animationFrame)]);

            if (particleEffects)
               showParticles(otherCamera);
         }
      }
   }
   else
      throw InvalidMarkerException();
}
