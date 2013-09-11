/*
 * CircBoundaryFigure.h
 *
 *  Created on: Sep 10, 2013
 *      Author: knavero
 */

#ifndef CIRCBOUNDARYFIGURE_H_
#define CIRCBOUNDARYFIGURE_H_

#include "Figure.h"

/*
 * Description: CircBoundaryFigure is used for rigid circular Figures that
 * the Player Figure cannot phase through
 */
class CircBoundaryFigure: public CircFigure {
public:

   /*
    * Description: default CircBoundaryFigure constructor
    */
   CircBoundaryFigure();

   /*
    * Description: parameterized CircBoundaryFigure constructor
    * Parameter: int x is the horizontal coordinate
    * Parameter: int y is the vertical coordinate
    * Parameter: Surface& image is the sprite sheet containing the images to be blitted
    * to screen
    *
    * Parameter: SDL_Surface* screen is the pointer to screen
    * Parameter: int levelWidth is the level width
    * Parameter: int levelHeight is the level height
    * Parameter: int numClips is the number of clips (in the horizontal direction) of
    * which to clip the sprite sheet
    */
   CircBoundaryFigure(int x, int y, Surface& image, SDL_Surface* screen,
         int levelWidth, int levelHeight, int numClips);

   /*
    * Description: CircBoundaryFigure set method
    * Parameter: int x is the horizontal coordinate
    * Parameter: int y is the vertical coordinate
    * Parameter: Surface& image is the sprite sheet containing the images to be blitted
    * to screen
    *
    * Parameter: SDL_Surface* screen is the pointer to screen
    * Parameter: int levelWidth is the level width
    * Parameter: int levelHeight is the level height
    * Parameter: int numClips is the number of clips (in the horizontal direction) of
    * which to clip the sprite sheet
    */
   void setFigure(int x, int y, Surface& image, SDL_Surface* screen,
         int levelWidth, int levelHeight, int numClips);
};

#endif /* CIRCBOUNDARYFIGURE_H_ */
