/*
 * TempFigure.h
 *
 *  Created on: Sep 5, 2013
 *      Author: knavero
 */

#ifndef TEMPFIGURE_H_
#define TEMPFIGURE_H_

#include "SDLAbstractionLayer.h"
#include "PlayerFigure.h"
#include "Figure.h"
#include "Exception.h"

/*
 * Description: TempFigure is a convenience class for Figures that are meant to disappear
 * when collision occurs between the player Figure and the TempFigure
 */
class TempFigure: public RectFigure {
public:

   /*
    * Description: Marker holds the enum table between switching states within the
    * show() method
    */
   enum Marker {
      ACTIVE, REMOVE, INACTIVE
   };

private:

   /*
    * Description: Marker marker holds the state of the TempFigure associated to when
    * it's being shown to the screen
    */
   Marker marker;

   //TODO description here
   Chunk scratch;

public:

   /*
    * Description: default constructor
    */
   TempFigure();

   /*
    * Description: parameterized constructor
    * Parameter: int x is the x coordinate starting position of the Figure
    * Parameter: int y is the y coordinate starting position of the Figure
    * Parameter: Surface& image is the image to show
    * Parameter: SDL_Surface* screen is the software screen active in system memory
    * Parameter: int levelWidth is the width of the level. Default is -1.
    * Parameter: int levelHeight is the height of the level. Default is -1.
    */
   TempFigure(int x, int y, Surface& image, SDL_Surface* screen,
         int levelWidth = -1, int levelHeight = -1);

   /*
    * Description: setFigure sets a TempFigure with the specified parameters
    * Parameter: int x is the x coordinate starting position of the Figure
    * Parameter: int y is the y coordinate starting position of the Figure
    * Parameter: Surface& image is the image to show
    * Parameter: SDL_Surface* screen is the software screen active in system memory
    * Parameter: int levelWidth is the width of the level. Default is -1.
    * Parameter: int levelHeight is the height of the level. Default is -1.
    */
   virtual void setFigure(int x, int y, Surface& image, SDL_Surface* screen,
         int levelWidth = -1, int levelHeight = -1);

   /*
    * Description: resolves a collision for the TempFigure
    * Parameter: Figure* other is the pointer the Figure colliding with this TempFigure
    * Parameter: double timeStep is the delta ticks between the start of the timer to
    * this method call. This parameter is currently irrelevant to the execution steps of
    * this method, but added here to successfully override the parent method
    *
    * Parameter: Component dir describes specification of which axis (x or y) the collision
    * occurred on. This parameter is currently irrelevant to the execution steps of
    * this method, but added here to successfully override the parent method
    */
   virtual void resolveCollision(Figure* other, double timeStep, Component dir);

   /*
    * Description: shows the image to screen with the updated position
    * Parameter: SDL_Rect* otherCamera is the pointer to the SDL_Rect describing the relevant
    * camera to follow (usually the leader Figure i.e. the camera of the player Figure)
    */
   virtual void show(SDL_Rect* otherCamera = NULL);
};

#endif /* TEMPFIGURE_H_ */
