/*
 * Figure.h
 *
 *  Created on: Sep 4, 2013
 *      Author: knavero
 */

#ifndef FIGURE_H_
#define FIGURE_H_

#include "SDLAbstractionLayer.h"
#include "Exception.h"
#include <typeinfo>
#include <iostream>
#include <cmath>

using namespace std;

/*
 * Description: Figure pre-declaration
 */
class Figure;

/*
 * Description: RectFigure pre-declaration
 */
class RectFigure;

/*
 * Description: CircFigure pre-declaration
 */
class CircFigure;

/*
 * Description: The Figure class is a convenience class for creating dynamic moveable
 * objects on the screen.
 */
class Figure {
public:

   /*
    * Description: Enum Gravity represents if gravity is enabled or disabled
    */
   enum Gravity {
      GRAVITY_DISABLED, GRAVITY_ENABLED
   };

   /*
    * Description: Status describes whether the Figure is moving left or right
    */
   enum Status {
      LEFT, RIGHT
   };

   /*
    * Description: Component for collision resolution
    */
   enum Component {
      XHAT, YHAT
   };

private:

   /*
    * Description: copy constructor placed in private to prevent object slicing
    */
   Figure(const Figure& other);

protected:

   /*
    * Description: contains dimensions of the image
    */
   SDL_Rect dim;

   /*
    * Description: contains the position of where the image is located at
    */
   Position p;

   /*
    * Description: the base gravity value specifying pixels covered per frame when in freefall
    */
   double gravity;

   /*
    * Description: the jump strength of the Figure if required to jump. Jump strength
    * in this context is a multiplier that is multiplied with speed and height
    * of the image
    */
   double jumpStrength;

   /*
    * Description: speed is the fraction of dimensions covered per frame when Figure is moving. In other
    * words, in terms of horizontal movement along the x axis, a Figure could be 100 pixels
    * in width, so that would mean that if the speed is a value of 0.5, then the Figure
    * move 50 pixels per frame
    */
   double speed;

   /*
    * Description: frame counter to smoothen jump motion
    */
   int jumpFrame;

   /*
    * Description: frame counter used for advancing the next clip in the animation
    */
   double animationFrame;

   /*
    * Description: number of clips associated to animating a Figure
    */
   int numClips;

   /*
    * Description: status of Figure if its moving left or right
    */
   Status status;

   /*
    * Description: holds the clips to animate the Figure when Figure is moving left
    */
   SDL_Rect* cl;

   /*
    * Description: holds the clips to animate the Figure when Figure is moving right
    */
   SDL_Rect* cr;

   /*
    * Description: true if gravity is enabled, false if Figure is intended to float
    */
   bool gravityEnabled;

   /*
    * Description: bool l, r, u, d describes a flag that can be set in order to transmit a state
    * from the handleInput() method to any other method of the class. For example, when
    * the left button is pressed, the l flag is set, and in the show() method, the
    * Surface* left image is rendered as a result
    */
   bool l, r, u, d;

   /*
    * Description: true if jump is in action, false otherwise
    */
   bool jumpAction;

   /*
    * Description: true if Figure is in in the air, false otherwise
    */
   bool inAir;

   /*
    * Description: describes whether a Figure is to be followed by the camera or not. If
    * followed by the camera, the Figure is considered to be the leader
    */
   bool leader;

   /*
    * Description: contains the class name of the subclass instantiated
    */
   string className;

   /*
    * Descrption: holds the current x, y velocity of the Figure. Velocity in this context describes
    * how many pixels the Figure will cover within the next frame i.e. pixels per frame
    */
   Velocity v;

   /*
    * Description: holds the pointer to screen. This is needed when grabbing the width and height
    * of the software display
    */
   SDL_Surface* screen;

   /*
    * Description: holds the pointer the Surface that contains the clips to be displayed
    * to screen
    */
   Surface* image;

   /*
    * Description: camera is the pointer to SDL_Rect that contains the x and y offset
    * (upper left corner) of where the camera is supposed to be within the level
    * boundaries, and the width and height matching the screen dimensions
    */
   SDL_Rect* camera;

   /*
    * Description: lw and lh are the level width and the level height
    */
   int lw, lh;

   /*
    * Description: True if there are particle effects, false if otherwise.
    */
   bool particleEffects;

   /*
    * Description: pointer to particle 1
    */
   Surface* p1;

   /*
    * Description: Pointer to particle 2
    */
   Surface* p2;

   /*
    * Description: Pointer to particle 3
    */
   Surface* p3;

   /*
    * Description: Pointer to particle 4
    */
   Surface* p4;

   /*
    * Description: array of Particle pointers of size TOTAL_PARTICLES
    */
   Particle* particles[TOTAL_PARTICLES];

   /*
    * Description: private method for calculating the velocity in the y component as a result from gravity.
    * Makes direct changes to v.y in Figure instance, and thus it is not necessary to store the return value
    * to a location.
    *
    * Return: velocity of the Figure in the y component
    */
   virtual int determineGravity();

   /*
    * Description: private method for handling jump related operations
    * Return: velocity of the Figure in the y component
    */
   virtual int determineJump();

   /*
    * Description: private method for determining if bool inAir should be true or false
    * Parameter: vector<Figure*>& other is a reference to the collision vector that hold
    * Figure pointers to the Figures that are not to be collided with by the player Figure
    */
   virtual void checkIfInAir(vector<Figure*>& other);

   /*
    * Description: initialize function
    * Parameter: int x is the starting x coordinate of the Figure
    * Parameter: int y is the starting y coordinate of the Figure
    * Parameter: double gravity is the value for gravity
    * Parameter: double speed is the value for speed
    * Parameter: double jumpStrength is the value for the jump strength
    * Parameter: SDL_Surface* screen is the display screen
    * Parameter: Gravity gravityEnabled is the enum describing whether or not to enable
    * gravity or not
    *
    * Parameter: bool leader is true if the camera is to follow the this instance of
    * Figure (i.e. in most cases, the camera follows the Figure controlled
    * by the player), false otherwise.
    *
    * Parameter: int numClips describes the number of clips existing on the sprite sheet
    * for one single direction i.e. for the left direction, if there are four parts to
    * animate the left movement then numClips would be a value of 4. If this were the case,
    * then the right direction must also have four parts as well.
    *
    * Parameter: int levelWidth is the width of the level
    * Parameter: int levelHeight is the height of the level
    * Parameter: Surface* p1 is the pointer to particle 1
    * Parameter: Surface* p2 is the pointer to particle 2
    * Parameter: Surface* p3 is the pointer to particle 3
    * Parameter: Surface* p4 is the pointer to particle 4
    */
   void initialize(int x, int y, double gravity, double speed,
         double jumpStrength, SDL_Surface* screen, Gravity gravityEnabled,
         bool leader, int numClips, int levelWidth, int levelHeight,
         Surface* p1, Surface* p2, Surface* p3, Surface* p4);

   /*
    * Description: sets the clips to enable animation
    */
   void setClips(int clipWidth, int clipHeight);

   /*
    * Description: describes how the current x position should be updated
    * Parameter: vector<Figure*>& other is the reference to a vector containing Figure pointers
    * that are to be detected for collision
    *
    * Parameter: deltaTicks is the time that has passed since the timer started
    */
   virtual void xMovement(vector<Figure*>& other, int deltaTicks);

   /*
    * Description: describes how the current y position should be updated
    * Parameter: vector<Figure*>& other is the reference to a vector containing Figure pointers
    * that are to be detected for collision
    *
    * Parameter: deltaTicks is the time that has passed since the timer started
    */
   virtual void yMovement(vector<Figure*>& other, int deltaTicks);

   /*
    * Description: setCamera() sets the camera position to a new position
    */
   virtual void setCamera();

   /*
    * Description: debug() contains debugging information after a Figure constructor or
    * setFigure() has been called. This, mostly, performs a sanity check on the set
    * values of the private variables
    */
   void debug();

public:

   /*
    * Description: Default constructor
    */
   Figure();

   /*
    * Description: Overloading Figure constructor for Figures that only need one image
    * Parameter: int x is the x coordinate starting position of the Figure
    * Parameter: int y is the y coordinate starting position of the Figure
    * Parameter: Surface& image is the image to show
    * Parameter: SDL_Surface* screen is the software screen active in system memory
    * Parameter: Gravity gravityEnabled is enum that specifies if gravity is enabled
    * or not for the Figure
    *
    * Parameter: bool leader is true if the camera is to follow the this instance of
    * Figure (i.e. in most cases, the camera follows the Figure controlled
    * by the player), false otherwise. Default value is false.
    *
    * Parameter: Resolves resolve describes the collision resolution action if collided
    * with. Default is BOUNDARY.
    *
    * Parameter: double speed is the movement speed of the Figure in terms of percentage
    * of the dimensions of the Figure i.e. for horizontal movement, a speed value of 50
    * would indicate move 50% of the Figure width every frame. Default is 5.
    *
    * Parameter: double gravity is set to 1 by default and describes how strong the
    * gravity is. If GRAVITY_DISABLED is passed in as a parameter, this is disregarded
    * no matter what value is passed in for gravity
    *
    * Parameter: double jumpStrength is set to 1 by default and describes the jump
    * strength. If GRAVITY_DISABLED is passed in as a parameter, this is disregarded
    * no matter what value is passed in for jumpStrength
    *
    * Parameter: int numClips describes the number of clips existing on the sprite sheet
    * for one single direction i.e. for the left direction, if there are four parts to
    * animate the left movement then numClips would be a value of 4. If this were the case,
    * then the right direction must also have four parts as well. Default is 1.
    *
    * Parameter: int levelWidth is the width of the level. Default is -1.
    * Parameter: int levelHeight is the height of the level. Default is -1.
    * Parameter: Surface* p1 is the pointer to particle 1. Default is NULL.
    * Parameter: Surface* p2 is the pointer to particle 2. Default is NULL.
    * Parameter: Surface* p3 is the pointer to particle 3. Default is NULL.
    * Parameter: Surface* p4 is the pointer to particle 4. Default is NULL.
    */
   Figure(int x, int y, Surface& image, SDL_Surface* screen,
         Gravity gravityEnabled, bool leader = false, double speed = 5,
         double gravity = 1, double jumpStrength = 1, int numClips = 1,
         int levelWidth = -1, int levelHeight = -1, Surface * p1 = NULL,
         Surface* p2 = NULL, Surface* p3 = NULL, Surface* p4 = NULL);

   /*
    * Description: sets Figure
    * Parameter: int x is the x coordinate starting position of the Figure
    * Parameter: int y is the y coordinate starting position of the Figure
    * Parameter: Surface& image is the image to show when Figure is moving
    * Parameter: SDL_Surface* screen is the software screen active in system memory
    * Parameter: Gravity gravityEnabled is enum that specifies if gravity is enabled
    * or not for the Figure
    *
    * Parameter: bool leader is true if the camera is to follow the this instance of
    * Figure (i.e. in most cases, the camera follows the Figure controlled
    * by the player), false otherwise. Default value is false.
    *
    * Parameter: Resolves resolve describes the collision resolution action if collided
    * with. Default is BOUNDARY.
    *
    * Parameter: double speed is the movement speed of the Figure in terms of percentage
    * of the dimensions of the Figure i.e. for horizontal movement, a speed value of 50
    * would indicate move 50% of the Figure width every frame. Default is 5.
    *
    * Parameter: double gravity is set to 1 by default and describes how strong the
    * gravity is. If GRAVITY_DISABLED is passed in as a parameter, this is disregarded
    * no matter what value is passed in for gravity
    *
    * Parameter: double jumpStrength is set to 1 by default and describes the jump
    * strength. If GRAVITY_DISABLED is passed in as a parameter, this is disregarded
    * no matter what value is passed in for jumpStrength
    *
    * Parameter: int numClips describes the number of clips existing on the sprite sheet
    * for one single direction i.e. for the left direction, if there are four parts to
    * animate the left movement then numClips would be a value of 4. If this were the case,
    * then the right direction must also have four parts as well. Default is 1.
    *
    * Parameter: int levelWidth is the width of the level. Default is -1.
    * Parameter: int levelHeight is the height of the level. Default is -1.
    * Parameter: Surface* p1 is the pointer to particle 1. Default is NULL.
    * Parameter: Surface* p2 is the pointer to particle 2. Default is NULL.
    * Parameter: Surface* p3 is the pointer to particle 3. Default is NULL.
    * Parameter: Surface* p4 is the pointer to particle 4. Default is NULL.
    */
   virtual void setFigure(int x, int y, Surface& image, SDL_Surface* screen,
         Gravity gravityEnabled, int levelWidth = -1, int levelHeight = -1,
         bool leader = false, double speed = 5, double gravity = 1,
         double jumpStrength = 1, int numClips = 1, Surface* p1 = NULL,
         Surface* p2 = NULL, Surface* p3 = NULL, Surface* p4 = NULL);

   /*
    * Description: obtains the width of the Figure
    */
   virtual int getWidth();

   /*
    * Description: obtains the height of the Figure
    */
   virtual int getHeight();

   /*
    * Description: sets the x position of the Figure
    */
   virtual void setX(int x);

   /*
    * Description: obtains the x position of the Figure
    */
   virtual int getX();

   /*
    * Description: sets the y position of the Figure
    */
   virtual void setY(int y);

   /*
    * Description: obtains the y position of the Figure
    */
   virtual int getY();

   /*
    * Description: parses through the subclasses to see what kind of Figure the this instance is colliding with, then calls
    * the respective checkCollision.
    *
    * Parameter: Figure* f is the pointer to Figure of who is being checked for collision with the this instance
    * Return: true if collision occurs with Figure* f, false otherwise
    */
   virtual bool checkCollision(Figure* f);

   /*
    * Description: checks if collided with a RectFigure. Requires implementation in subclass.
    * Parameter: RectFigure* r is the pointer to RectFigure that is being checked for
    * collision with the this instance
    *
    * Return: true if collision occurs with RectFigure* r, false otherwise
    */
   virtual bool checkCollision(RectFigure* r) = 0;

   /*
    * Description: checks if collided with a CircFigure. Requires implementation in subclass.
    * Parameter: CircFigure* c is the pointer to CircFigure that is being checked for
    * collision with the this instance
    *
    * Return: true if collision occurs with CircFigure* c, false otherwise
    */
   virtual bool checkCollision(CircFigure* c) = 0;

   /*
    * Description: accepts a reference to a vector containing the pointer to Figures in
    * where the Figures need to be parsed through to check for collision with the this Figure.
    *
    * Parameter: vector<Figure*>& other is the reference to a vector holding the Figure pointers
    * that require parsing for collision detection i.e. the vector that contains all the
    * instantiated Figures. isCollided() is aware of reflexive properties between Figures and
    * ignores checking collision for a Figure that is itself
    *
    * Parameter: int& count is the reference to the counter describing which index of the vector
    * the collision occurred on. After the method has been executed, if count results as -1,
    * then no collision occurred
    *
    * Precondition: count must be passed in with the value of 0
    *
    * Return: true if collision occurred, false otherwise
    */
   virtual bool isCollided(vector<Figure*>& other, int& count);

   /*
    * Description: resolves collision based on the Component dir passed in i.e.
    * if collision happened along the y axis, then dir would be YHAT
    *
    * Parameter: Figure* other is the pointer to Figure that was collided with
    * Parameter: double timeStep is the deltaTicks between the start of the timer to the
    * call of resolveCollision. timeStep is used for time-based frame independent movement.
    *
    * Parameter: Component dir is the axis that collision occurred on
    * Precondition: Figure* other is valid and not NULL
    */
   virtual void resolveCollision(Figure* other, double timeStep, Component dir);

   /*
    * Description: handles input with directional keys and adjusts the velocity respectively
    * Parameter: SDL_Event& event is the reference to the SDL_Event type in the event loop
    */
   virtual void handleInput(SDL_Event& event);

   /*
    * Description: moves by adding the velocity to the current position while checking for
    * collision
    *
    * Parameter: vector<Figure*>& other is the reference to a vector holding the Figure pointers
    * that require parsing for collision detection
    *
    * Parameter: deltaTicks is the time that has passed since the timer started
    */
   virtual void move(vector<Figure*>& other, int deltaTicks);

   /*
    * Description: applies the current image (left or right) to the screen. Does not flip the
    * video buffers. That should be done manually.
    *
    * Parameter: SDL_Rect* otherCamera is the camera belonging to the Figure being followed,
    * i.e. the Figure controlled by the player. For example, RectFigure rf1 is a Figure that
    * is not moving on the level/screen and RectFigure rf2 is a Figure controlled by
    * the player. When showing rf1, it would look like this: rf1.show(rf2.getCameraClip()).
    * Default value for otherCamera is NULL.
    *
    * Exception: throws InvalidMarkerException()
    * Return: Marker describing whether the Figure is ACTIVE, INACTIVE, or set to REMOVE
    */
   virtual void show(SDL_Rect* otherCamera = NULL);

   /*
    * Description: applies the particles to screen
    * Paramter: SDL_Rect* camera is the relative camera. The relative camera is the camera following the
    * leader Figure
    */
   virtual void showParticles(SDL_Rect* camera);

   /*
    * Description: obtains the SDL_Rect pointer to the camera belonging to the
    * associating Figure. This is used primarily for non-leader Figures that are not
    * followed by the camera. For example, RectFigure rf1 is a Figure that is not
    * moving on the level/screen and RectFigure rf2 is a Figure controlled by the player.
    * When showing rf1, it would look like this: rf1.show(rf2.getCameraClip())
    */
   virtual SDL_Rect* getCameraClip();

   /*
    * Description: performs instanceof check to see if subclass is an instance of
    * RectFigure or CircFigure. Can be overrided, but user must Figure::checkCollision() must
    * be edited, else a FigureException will be thrown. It is advised not to override this
    * if it can be avoided
    *
    * Return: the class name of the subclass instantiated
    */
   virtual string getClassName();

   /*
    * Description: true if Figures are equal, false otherwise
    */
   bool operator==(const Figure& other);

   /*
    * Description: true if Figures are not equal, false otherwise
    */
   bool operator!=(const Figure& other);

   /*
    * Description: destructor
    */
   virtual ~Figure();
};

/*
 * Description: RectFigure extends Figure class in being a convenience class that handles
 * Rectangular Figures and thus making them dynamic movable objects on the screen aware
 * of collision with other Figures
 */
class RectFigure: public Figure {
public:

   /*
    * Description: Default RectFigure() constructor
    */
   RectFigure();

   /*
    * Description: Overloading parameterized constructor
    * Parameter: int x is the horizontal position specifying the upper left corner
    * Parameter: int y is the vertical position specifying the upper left corner
    * Parameter: Surface& image is the image to display when moving
    * Parameter: SDL_Surface* screen is the software screen active in system memory
    * Parameter: Gravity gravityEnabled is enum that specifies if gravity is enabled
    * or not for the Figure
    *
    * Parameter: bool leader is true if the camera is to follow the this instance of
    * Figure (i.e. in most cases, the camera follows the Figure controlled
    * by the player), false otherwise. Default value is false.
    *
    * Parameter: Resolves resolve describes the collision resolution action if collided
    * with. Default is BOUNDARY.
    *
    * Parameter: double speed is the movement speed of the Figure in terms of percentage
    * of the dimensions of the Figure i.e. for horizontal movement, a speed value of 50
    * would indicate move 50% of the Figure width every frame. Default is 5;
    *
    * Parameter: double gravity is set to 1 by default and describes how strong the
    * gravity is. If GRAVITY_DISABLED is passed in as a parameter, this is disregarded
    * no matter what value is passed in for gravity
    *
    * Parameter: double jumpStrength is set to 1 by default and describes the jump
    * strength. If GRAVITY_DISABLED is passed in as a parameter, this is disregarded
    * no matter what value is passed in for jumpStrength
    *
    * Parameter: int numClips describes the number of clips existing on the sprite sheet
    * for one single direction i.e. for the left direction, if there are four parts to
    * animate the left movement then numClips would be a value of 4. If this were the case,
    * then the right direction must also have four parts as well. Default is 1.
    *
    * Parameter: int levelWidth is the width of the level. Default is -1.
    * Parameter: int levelHeight is the height of the level. Default is -1.
    * Parameter: Surface* p1 is the pointer to particle 1. Default is NULL.
    * Parameter: Surface* p2 is the pointer to particle 2. Default is NULL.
    * Parameter: Surface* p3 is the pointer to particle 3. Default is NULL.
    * Parameter: Surface* p4 is the pointer to particle 4. Default is NULL.
    */
   RectFigure(int x, int y, Surface& image, SDL_Surface* screen,
         Gravity gravityEnabled, int levelWidth = -1, int levelHeight = -1,
         bool leader = false, double speed = 5, double gravity = 1,
         double jumpStrength = 1, int numClips = 1, Surface* p1 = NULL,
         Surface* p2 = NULL, Surface* p3 =
         NULL, Surface* p4 = NULL);

   /*
    * Description: checks for RectFigure to RectFigure collision
    * Parameter: RectFigure* r is the pointer to the RectFigure that is being checked for collision with
    * the this instance
    * Return: true if collision occurs with RectFigure* r, false otherwise
    */
   virtual bool checkCollision(RectFigure* r);

   /*
    * Description: checks for RectFigure to CircFigure collision
    * Parameter: CircFigure* c is the pointer to the CircFigure that is being checked for collision with
    * the this instance
    *
    * Return: true if collision occurs with CircFigure* c, false otherwise
    */
   virtual bool checkCollision(CircFigure* c);
};

/*
 * Description: CircFigure extends Figure class in being a convenience class that handles
 * Circular Figures and thus making them dynamic movable objects on the screen aware
 * of collision with other Figures
 */
class CircFigure: public Figure {
protected:

   /*
    * Description: int r is the radius of the CircFigure
    */
   int r;

   /*
    * Description: calculates gravity with respect to circle figures
    */
   virtual int determineGravity();

   /*
    * Description: private method for determining if bool inAir should be true or false
    * Parameter: vector<Figure*>& other is a reference to the collision vector that hold
    * Figure pointers to the Figures that are not to be collided with by the player Figure
    */
   virtual void checkIfInAir(vector<Figure*>& other);

   /*
    * Description: describes how the current x position should be updated
    * Parameter: vector<Figure*>& other is the reference to a vector containing Figure pointers
    * that are to be detected for collision
    *
    * Parameter: deltaTicks is the time that has passed since the timer started
    */
   virtual void xMovement(vector<Figure*>& other, int deltaTicks);

   /*
    * Description: describes how the current y position should be updated
    * Parameter: vector<Figure*>& other is the reference to a vector containing Figure pointers
    * that are to be detected for collision
    *
    * Parameter: deltaTicks is the time that has passed since the timer started
    */
   virtual void yMovement(vector<Figure*>& other, int deltaTicks);

public:

   /*
    * Description: default constructor for CircFigure
    */
   CircFigure();

   /*
    * Description: Overloading parameterized constructor
    * Parameter: int x is the horizontal position specifying the center of the circle
    * Parameter: int y is the vertical position specifying the center of the circle
    * Parameter: Surface& image is the image to display when moving
    * Parameter: SDL_Surface* screen is the software screen active in system memory
    * Parameter: Gravity gravityEnabled is enum that specifies if gravity is enabled
    * or not for the Figure
    *
    * Parameter: bool leader is true if the camera is to follow the this instance of
    * Figure (i.e. in most cases, the camera follows the Figure controlled
    * by the player), false otherwise. Default value is false.
    *
    * Parameter: Resolves resolve describes the collision resolution action if collided
    * with. Default is BOUNDARY.
    *
    * Parameter: double speed is the movement speed of the Figure in terms of percentage
    * of the dimensions of the Figure i.e. for horizontal movement, a speed value of 50
    * would indicate move 50% of the Figure width every frame. Default is 5;
    *
    * Parameter: double gravity is set to 1 by default and describes how strong the
    * gravity is. If GRAVITY_DISABLED is passed in as a parameter, this is disregarded
    * no matter what value is passed in for gravity
    *
    * Parameter: double jumpStrength is set to 1 by default and describes the jump
    * strength. If GRAVITY_DISABLED is passed in as a parameter, this is disregarded
    * no matter what value is passed in for jumpStrength
    *
    * Parameter: int numClips describes the number of clips existing on the sprite sheet
    * for one single direction i.e. for the left direction, if there are four parts to
    * animate the left movement then numClips would be a value of 4. If this were the case,
    * then the right direction must also have four parts as well. Default is 1.
    *
    * Parameter: int levelWidth is the width of the level. Default is -1.
    * Parameter: int levelHeight is the height of the level. Default is -1.
    * Parameter: Surface* p1 is the pointer to particle 1. Default is NULL.
    * Parameter: Surface* p2 is the pointer to particle 2. Default is NULL.
    * Parameter: Surface* p3 is the pointer to particle 3. Default is NULL.
    * Parameter: Surface* p4 is the pointer to particle 4. Default is NULL.
    */
   CircFigure(int x, int y, Surface& image, SDL_Surface* screen,
         Gravity gravityEnabled, int levelWidth = -1, int levelHeight = -1,
         bool leader = false, double speed = 5, double gravity = 1,
         double jumpStrength = 1, int numClips = 1, Surface* p1 = NULL,
         Surface* p2 = NULL, Surface* p3 = NULL, Surface* p4 = NULL);

   /*
    * Description: Overloading parameterized constructor
    * Parameter: int x is the horizontal position specifying the center of the circle
    * Parameter: int y is the vertical position specifying the center of the circle
    * Parameter: Surface& image is the image to display when moving
    * Parameter: SDL_Surface* screen is the software screen active in system memory
    * Parameter: Gravity gravityEnabled is enum that specifies if gravity is enabled
    * or not for the Figure
    *
    * Parameter: bool leader is true if the camera is to follow the this instance of
    * Figure (i.e. in most cases, the camera follows the Figure controlled
    * by the player), false otherwise. Default value is false.
    *
    * Parameter: Resolves resolve describes the collision resolution action if collided
    * with. Default is BOUNDARY.
    *
    * Parameter: double speed is the movement speed of the Figure in terms of percentage
    * of the dimensions of the Figure i.e. for horizontal movement, a speed value of 50
    * would indicate move 50% of the Figure width every frame. Default is 5;
    *
    * Parameter: double gravity is set to 1 by default and describes how strong the
    * gravity is. If GRAVITY_DISABLED is passed in as a parameter, this is disregarded
    * no matter what value is passed in for gravity
    *
    * Parameter: double jumpStrength is set to 1 by default and describes the jump
    * strength. If GRAVITY_DISABLED is passed in as a parameter, this is disregarded
    * no matter what value is passed in for jumpStrength
    *
    * Parameter: int numClips describes the number of clips existing on the sprite sheet
    * for one single direction i.e. for the left direction, if there are four parts to
    * animate the left movement then numClips would be a value of 4. If this were the case,
    * then the right direction must also have four parts as well. Default is 1.
    *
    * Parameter: int levelWidth is the width of the level. Default is -1.
    * Parameter: int levelHeight is the height of the level. Default is -1.
    * Parameter: Surface* p1 is the pointer to particle 1. Default is NULL.
    * Parameter: Surface* p2 is the pointer to particle 2. Default is NULL.
    * Parameter: Surface* p3 is the pointer to particle 3. Default is NULL.
    * Parameter: Surface* p4 is the pointer to particle 4. Default is NULL.
    */
   virtual void setFigure(int x, int y, Surface& image, SDL_Surface* screen,
         Gravity gravityEnabled, int levelWidth = -1, int levelHeight = -1,
         bool leader = false, double speed = 5, double gravity = 1,
         double jumpStrength = 1, int numClips = 1, Surface* p1 = NULL,
         Surface* p2 = NULL, Surface* p3 = NULL, Surface* p4 = NULL);

   /*
    * Description: obtains the radius of the circle
    * Return: radius of the circle
    */
   int getR();

   /*
    * Description: applies the current image (left or right) to the screen. Does not flip the
    * video buffers. That should be done manually.
    *
    * Parameter: SDL_Rect* otherCamera is the camera belonging to the Figure being followed,
    * i.e. the Figure controlled by the player. For example, CircFigure cf1 is a Figure that
    * is not moving on the level/screen and CircFigure cf2 is a Figure controlled by
    * the player. When showing cf1, it would look like this: cf1.show(cf2.getCameraClip()).
    * Default value for otherCamera is NULL.
    */
   virtual void show(SDL_Rect* otherCamera = NULL);

   /*
    * Description: applies the particles to screen
    * Paramter: SDL_Rect* camera is the relative camera. The relative camera is the camera following the
    * leader Figure
    */
   virtual void showParticles(SDL_Rect* camera);

   /*
    * Description: checks for CircFigure to RectFigure collision
    * Parameter: RectFigure* r is the pointer to the RectFigure that is being checked for collision with
    * the this instance
    * Return: true if collision occurs with RectFigure* r, false otherwise
    */
   virtual bool checkCollision(RectFigure* r);

   /*
    * Description: checks for CircFigure to CircFigure collision
    * Parameter: CircFigure* r is the pointer to the CircFigure that is being checked for collision with
    * the this instance
    * Return: true if collision occurs with CircFigure* c, false otherwise
    */
   virtual bool checkCollision(CircFigure* c);
};

#endif /* FIGURE_H_ */
