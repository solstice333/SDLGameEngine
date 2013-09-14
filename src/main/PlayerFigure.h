/*
 * PlayerFigure.h
 *
 *  Created on: Sep 10, 2013
 *      Author: knavero
 */

#ifndef PLAYERFIGURE_H_
#define PLAYERFIGURE_H_

#include "SDLAbstractionLayer.h"
#include "Figure.h"
#include "RectBoundaryFigure.h"
#include "CircBoundaryFigure.h"
#include "CursorFigure.h"
#include "TempFigure.h"

/*
 * Description: PlayerFigure represents the Figure that the player controls
 */
class PlayerFigure: public RectFigure {
private:
   Surface target;
   CursorFigure cursor;
   bool grabstate;
   bool resetVelY;
   Point A, B;
   double multiplier;
   Velocity grabVel;

protected:
   virtual void determineGrabX(int deltaTicks);
   virtual void determineGrabY(int deltaTicks);
   virtual void checkIfInAir(vector<Figure*>& other);
   virtual void xMovement(vector<Figure*>& other, int deltaTicks);
   virtual void yMovement(vector<Figure*>& other, int deltaTicks);

public:

   /*
    * Description: PlayerFigure default constructor
    */
   PlayerFigure();

   /*
    * Description: PlayerFigure parameterized constructor
    * Parameter: int x is the horizontal coordinate
    * Parameter: int y is the vertical coordinate
    * Parameter: Surface& image is the sprite sheet containing the images to be blitted
    * to screen
    *
    * Parameter: SDL_Surface* screen is the pointer to screen
    * Parameter: double speed represents the movement speed of the Figure
    * Parameter: double gravity represents the strength of gravity applied to the Figure
    * Parameter: double jumpStrenght represents the jump strength of the Figure
    * Parameter: int numClips is the number of clips (in the horizontal direction) of
    * which to clip the sprite sheet
    *
    * Parameter: int levelWidth is the level width
    * Parameter: int levelHeight is the level height
    * Parameter: p1, p2, p3, p4 are all Surface pointers pointing to particle images
    */
   PlayerFigure(int x, int y, Surface& image, SDL_Surface* screen, double speed,
         double gravity, double jumpStrength, int numClips, int levelWidth,
         int levelHeight, Surface* p1 = NULL, Surface* p2 = NULL, Surface* p3 =
         NULL, Surface* p4 = NULL);

   /*
    * Description: PlayerFigure set method
    * Parameter: int x is the horizontal coordinate
    * Parameter: int y is the vertical coordinate
    * Parameter: Surface& image is the sprite sheet containing the images to be blitted
    * to screen
    *
    * Parameter: SDL_Surface* screen is the pointer to screen
    * Parameter: double speed represents the movement speed of the Figure
    * Parameter: double gravity represents the strength of gravity applied to the Figure
    * Parameter: double jumpStrenght represents the jump strength of the Figure
    * Parameter: int numClips is the number of clips (in the horizontal direction) of
    * which to clip the sprite sheet
    *
    * Parameter: int levelWidth is the level width
    * Parameter: int levelHeight is the level height
    * Parameter: p1, p2, p3, p4 are all Surface pointers pointing to particle images
    */
   virtual void setFigure(int x, int y, Surface& image, SDL_Surface* screen,
         double speed, double gravity, double jumpStrength, int numClips,
         int levelWidth, int levelHeight, Surface * p1 = NULL, Surface* p2 =
         NULL, Surface* p3 = NULL, Surface* p4 = NULL);

   /*
    * Description: overrided from Figure parent class. Takes in input from the user
    * and adjusts velocity or sets Player states
    *
    * Parameter: SDL_Event& event is the reference to the event located in the event
    * loop
    *
    * Preconditions: Gravity must be set to GRAVITY_ENABLED. Not sure what this does
    * when it's not. Don't worry though. PlayerFigure constructor and setFigure is
    * set to that configuration already.
    */
   virtual void handleInput(SDL_Event& event);

   /*
    * TODO doc
    */
   virtual void move(vector<Figure*>& other, int deltaTicks);

   /*
    * Description: resolves collision on the x and y axes
    * Parameter: Figure* other points the Figure collided with
    * Parameter: double timeStep is the delta ticks from the start of the timer to
    * when this method is called
    *
    * Parameter: Component dir is the axis of which the collision occurred on
    */
   virtual void resolveCollision(Figure* other, double timeStep, Component dir);

   /*
    * TODO description
    */
   virtual void show(SDL_Rect* otherCamera = NULL);
};

#endif /* PLAYERFIGURE_H_ */
