/*
 * RectBoundaryFigure.h
 *
 *  Created on: Sep 10, 2013
 *      Author: knavero
 */

#ifndef RECTBOUNDARYFIGURE_H_
#define RECTBOUNDARYFIGURE_H_

#include "Figure.h"

/*
 * Description: RectBoundaryFigure is used for rigid Figures that have a rectangular
 * shape
 */
class RectBoundaryFigure: public RectFigure {
public:

   /*
    * Description: RectBoundaryFigure default constructor
    */
   RectBoundaryFigure();

   /*
    * Description: RectBoundaryFigure parameterized constructor
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
   RectBoundaryFigure(int x, int y, Surface& image, SDL_Surface* screen,
         int levelWidth, int levelHeight, int numClips);

   /*
    * Description: RectBoundaryFigure set method
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

#endif /* RECTBOUNDARYFIGURE_H_ */
