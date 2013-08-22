#ifndef SDLABSTRACTIONLAYER_H
#define SDLABSTRACTIONLAYER_H

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include <string>
#include <vector>
using namespace std;

//struct describing current position on both x and y components
struct Position {
   int x, y;
};

//struct describing current velocity on both x and y components
struct Velocity {
   int x, y;
};

struct Point {
   int x, y;
};

//TODO late stages - add in window management classes for windowed/fullscreen
//TODO late stages - add in game save classes

/*
 * Description: The Surface class provides easy management with instantiating SDL_Surfaces
 * and clean up. Also included, is automatic color key by sending in the Color
 * enumerated types as an argument to the Surface constructor or setSDL_Surface method.
 */
class Surface {
private:

   /*
    * Description: SDL_Surface pointer that the Surface class encapsulates
    */
   SDL_Surface* s;

public:

   /*
    * Description: enumerated Color tags. Used for specifying any Color arguments
    * found in the constructor call or setSDL_Surface method. For example, a Color
    * argument would look like Surface::RED to specify that any red pixels be transparent
    */
   enum Color {
      NONE, RED, GREEN, BLUE, CYAN, BLACK, WHITE
   };

   /*
    * Description: default constructor for Surface. Creates a blank Surface
    * requiring setting of the SDL_Surface pointer.
    */
   Surface();

   /*
    * Description: overloading constructor. Creates a Surface using the given SDL_Surface*
    * and color key
    *
    * Parameter: SDL_Surface* sdls is the surface to be initialized to
    * Parameter Color ck is the optional color key representing the color that is to
    * be transparent
    */
   Surface(SDL_Surface* sdls, Color ck = Surface::NONE);

   /*
    * Description: overloading constructor. Creates a Surface using the given filepath
    * and color key
    *
    * Parameter: string filepath is the filepath pointing to the loading image
    * Parameter Color ck is the optional color key representing the color that is to
    * be transparent
    */
   Surface(string filepath, Color ck = Surface::NONE);

   /*
    * Description: Overloading constructor for specifying a surface containing a true
    * type font
    *
    * Parameter: string ttfFile is the path to the .ttf file
    * Parameter: int fontSize is the font size described as pixel height
    * Parameter: Color textColor is the color of the font (Surface::<color name>)
    * Paramater: string msg is the text to be displayed
    */
   Surface(string ttfFile, int fontSize, Color textColor, string msg);

   /*
    * Description: setSDL_Surface sets the SDL_Surface* s encapsulated within the Surface object
    * Parameter: SDL_Surface* surface is the SDL_Surface pointer that the Surface object's
    * SDL_Surface* s is being set to
    * PostCondition: private SDL_Surface* s value is changed
    */
   void setSDL_Surface(SDL_Surface* surface);

   /*
    * Description: setSDL_Surface sets the SDL_Surface* s encapsulated within the Surface object.
    * Contains a default color key that represents the option to pass in a color key or not to.
    * For example, setSDL_Surface("/home/User/Pictures/image.png") is a valid call to the method
    * and is the same as setSDL_Surface("/home/User/Pictures/image.png", Surface::NONE)
    *
    * Parameter: string filepath is the filepath pointing to the loading image
    * Parameter: Color ck is the color key representing the color that is to be transparent.
    * Default color key is set to NONE which describes that color key is nonexistent.
    */
   void setSDL_Surface(string filepath, Color ck = NONE);

   /*
    * Description: sets the SDL_Surface* s within a Surface object
    * Parameter: string ttfFile is the path to the .ttf file
    * Parameter: int fontSize is the font size described as pixel height
    * Parameter: Color textColor is the color of the font (Surface::<color name>)
    * Paramater: string msg is the text to be displayed
    *
    */
   void setSDL_Surface(string ttfFile, int fontSize, Color textColor,
         string msg);

   /*
    * Description: getSDL_Surface() returns the SDL_Surface* s encapsulated within the
    * Surface object
    *
    * Return: SDL_Surface* s
    */
   SDL_Surface* getSDL_Surface();

   /*
    * Description: Destructor for Surface objects
    */
   ~Surface();
};

/*
 * Description: class Music is a convenience class for handling Mix_Music objects and automating
 * clean up.
 */
class Music {
private:

   /*
    * Description: Mix_Music pointer that the Music class encapsulates
    */
   Mix_Music* m;

public:

   /*
    * Description: default constructor for Music
    */
   Music();

   /*
    * Description: overloading constructor with pathname to specified music
    * Parameter: string music is the pathname to specified music
    */
   Music(string music);

   /*
    * Description: setMusic sets the music of private Mix_Music* m
    * Parameter: string music is the pathname to specified music
    */
   void setMusic(string music);

   /*
    * Description: getMix_Music returns the private Mix_Music* m value
    */
   Mix_Music* getMix_Music();

   /*
    * Description: Destructor for Music objects
    */
   ~Music();
};

/*
 * Description: class Chunk is a convenience class for handling Mix_Chunk objects and automating
 * clean up.
 */
class Chunk {
private:

   /*
    * Description: Mix_Chunk pointer that the Chunk class encapsulates
    */
   Mix_Chunk* c;

public:

   /*
    * Description: default constructor for Chunk
    */
   Chunk();

   /*
    * Description: overloading constructor with pathname to specified chunk
    * Parameter: string chunk is the pathname to specified sound effect
    */
   Chunk(string chunk);

   /*
    * Description: setChunk sets the chunk of private Mix_Chunk* c
    * Parameter: string chunk is the pathname to specified chunk
    */
   void setChunk(string chunk);

   /*
    * Description: getMix_Chunk returns the private Mix_Chunk* c value
    */
   Mix_Chunk* getMix_Chunk();

   /*
    * Description: Destructor for Chunk objects
    */
   ~Chunk();

};

/*
 * Description: Convenience class for timer functionality
 */
class Timer {
private:

   /*
    * Description: startTicks is the time at which the Timer is started at
    */
   int startTicks;

   /*
    * Description: pausedTicks is the time at which the Timer is paused at
    */
   int pausedTicks;

   /*
    * Description: true if paused, false otherwise
    */
   bool paused;

   /*
    * Description: true if started, false otherwise
    */
   bool started;

public:

   /*
    * Description: default constructor for Timer
    */
   Timer();

   /*
    * Description: starts the timer
    */
   void start();

   /*
    * Description: stops and resets the timer
    */
   void stop();

   /*
    * Description: pauses the timer
    */
   void pause();

   /*
    * Description: unpauses the timer
    */
   void unpause();

   /*
    * Description: obtains the current or paused milliseconds count
    * Return: integer for current or paused milliseconds
    */
   int getTicks();

   /*
    * Description: checks if timer is started
    * Return: true if timer is started, false otherwise
    */
   bool isStarted();

   /*
    * Description: checks if timer is paused
    * Return: true if paused, false otherwise
    */
   bool isPaused();

   /*
    * Description: delays the frame according to user defined framerate fps
    * Parameter: int fps is the user specified framerate
    * Return: returns the amount of time delayed in milliseconds
    */
   int delayFrame(int fps);
};

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

private:

   /*
    * Description: copy constructor placed in private to prevent object slicing
    */
   Figure(const Figure& other);

protected:

   /*
    * Description: SDL_Rect posDim holds the current x, y position and dimensions of
    * the Figure. If there are two Surface images (a left and right) then the average is taken
    * for each respective dimension i.e. an average width and an average height.
    */
   SDL_Rect posDim;

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
    */
   void initialize(int x, int y, double gravity, double speed,
         double jumpStrength, SDL_Surface* screen, Gravity gravityEnabled,
         bool leader, int numClips, int levelWidth, int levelHeight);

   /*
    * Description: sets the clips to enable animation
    */
   void setClips(int clipWidth, int clipHeight);

   /*
    * Description: describes how the current x position should be updated
    * Parameter: vector<Figure*>& other is the reference to a vector containing Figure pointers
    * that are to be detected for collision
    */
   virtual void xMovement(vector<Figure*>& other);

   /*
    * Description: describes how the current y position should be updated
    * Parameter: vector<Figure*>& other is the reference to a vector containing Figure pointers
    * that are to be detected for collision
    */
   virtual void yMovement(vector<Figure*>& other);

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
    * Parameter: double speed is the movement speed of the Figure in terms of percentage
    * of the dimensions of the Figure i.e. for horizontal movement, a speed value of 50
    * would indicate move 50% of the Figure width every frame. Default is 5.
    *
    * Parameter: int gravity is set to 1 by default and describes how strong the
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
    */
   Figure(int x, int y, Surface& image, SDL_Surface* screen,
         Gravity gravityEnabled, bool leader = false, double speed = 5,
         int gravity = 1, double jumpStrength = 1, int numClips = 1,
         int levelWidth = -1, int levelHeight = -1);

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
    * Parameter: double speed is the movement speed of the Figure in terms of percentage
    * of the dimensions of the Figure i.e. for horizontal movement, a speed value of 50
    * would indicate move 50% of the Figure width every frame. Default is 5.
    *
    * Parameter: int gravity is set to 1 by default and describes how strong the
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
    */
   virtual void setFigure(int x, int y, Surface& image, SDL_Surface* screen,
         Gravity gravityEnabled, bool leader = false, double speed = 5,
         int gravity = 1, double jumpStrength = 1, int numClips = 1,
         int levelWidth = -1, int levelHeight = -1);

   /*
    * Description: obtains the width of the Figure
    */
   virtual int getWidth();

   /*
    * Description: obtains the height of the Figure
    */
   virtual int getHeight();

   /*
    * Description: obtains the x position of the Figure
    */
   virtual int getX();

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
    * that require parsing for collision detection
    *
    * Parameter: int& count is the reference to the counter describing which index of the vector
    * the collision occurred on
    *
    * Return: true if collision occurred, false otherwise
    */
   virtual bool isCollided(vector<Figure*>& other, int& count);

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
    */
   virtual void move(vector<Figure*>& other);

   /*
    * Description: applies the current image (left or right) to the screen. Does not flip the
    * video buffers. That should be done manually.
    *
    * Parameter: SDL_Rect* otherCamera is the camera belonging to the Figure being followed,
    * i.e. the Figure controlled by the player. For example, RectFigure rf1 is a Figure that
    * is not moving on the level/screen and RectFigure rf2 is a Figure controlled by
    * the player. When showing rf1, it would look like this: rf1.show(rf2.getCameraClip()).
    * Default value for otherCamera is NULL.
    */
   virtual void show(SDL_Rect* otherCamera = NULL);

   /*
    * Description: obtains the SDL_Rect pointer to the camera belonging to the
    * associating Figure. This is used primarily for non-leader Figures that are not
    * followed by the camera. For example, RectFigure rf1 is a Figure that is not
    * moving on the level/screen and RectFigure rf2 is a Figure controlled by the player.
    * When showing rf1, it would look like this: rf1.show(rf2.getCameraClip())
    */
   virtual SDL_Rect* getCameraClip();

   /*
    * Description: obtains the class name of the subclass instance
    * Return: the class name of the subclass instantiated
    */
   string getClassName();

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
    * Parameter: double speed is the movement speed of the Figure in terms of percentage
    * of the dimensions of the Figure i.e. for horizontal movement, a speed value of 50
    * would indicate move 50% of the Figure width every frame. Default is 5;
    *
    * Parameter: int gravity is set to 1 by default and describes how strong the
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
    */
   RectFigure(int x, int y, Surface& image, SDL_Surface* screen,
         Gravity gravityEnabled, bool leader = false, double speed = 5,
         int gravity = 1, double jumpStrength = 1, int numClips = 1,
         int levelWidth = -1, int levelHeight = -1);

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
private:

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
    */
   virtual void xMovement(vector<Figure*>& other);

   /*
    * Description: describes how the current y position should be updated
    * Parameter: vector<Figure*>& other is the reference to a vector containing Figure pointers
    * that are to be detected for collision
    */
   virtual void yMovement(vector<Figure*>& other);

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
    * Parameter: double speed is the movement speed of the Figure in terms of percentage
    * of the dimensions of the Figure i.e. for horizontal movement, a speed value of 50
    * would indicate move 50% of the Figure width every frame. Default is 5;
    *
    * Parameter: int gravity is set to 1 by default and describes how strong the
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
    */
   CircFigure(int x, int y, Surface& image, SDL_Surface* screen,
         Gravity gravityEnabled, bool leader = false, double speed = 5,
         int gravity = 1, double jumpStrength = 1, int numClips = 1,
         int levelWidth = -1, int levelHeight = -1);

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
    * Parameter: double speed is the movement speed of the Figure in terms of percentage
    * of the dimensions of the Figure i.e. for horizontal movement, a speed value of 50
    * would indicate move 50% of the Figure width every frame. Default is 5;
    *
    * Parameter: int gravity is set to 1 by default and describes how strong the
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
    */
   virtual void setFigure(int x, int y, Surface& image, SDL_Surface* screen,
         Gravity gravityEnabled, bool leader = false, double speed = 5,
         int gravity = 1, double jumpStrength = 1, int numClips = 1,
         int levelWidth = -1, int levelHeight = -1);

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

/*
 * Description: Convenience class for accepting user input and outputting text
 * to the screen
 */
class StringInput {
private:

   /*
    * Description: string str is the string to be outputted to the screen
    */
   string str;

   /*
    * Description: text is the Surface to be outputted to the screen
    */
   Surface text;

   /*
    * Description: screen is the software display
    */
   SDL_Surface* screen;

   /*
    * Description: ttfFile is the relative path to the ttf file
    */
   string ttfFile;

   /*
    * Description: fontSize is the size of the font
    */
   int fontSize;

   /*
    * Description: fontColor is the color of the font
    */
   Surface::Color fontColor;

public:

   /*
    * Description: Constructor for StringInput
    * Parameter: string ttfFile is the relative path to the ttf file
    * Parameter: int fontSize is the size of the font
    * Parameter: Surface::Color fontColor is the color of the font
    * Parameter: SDL_Surface* screen
    */
   StringInput(string ttfFile, int fontSize, Surface::Color fontColor,
         SDL_Surface* screen);

   /*
    * Description: handleInput handles all keyboard input
    * Parameter: SDL_Event& event is the reference to an event within the event loop
    */
   void handleInput(SDL_Event& event);

   /*
    * Description: blits the text surface to the middle of the screen
    */
   void showCentered();

   /*
    * Description: clean up destructor for StringInput
    */
   ~StringInput();
};

/*
 * Description: returns the distance between Point p1 and Point p2
 * Parameter: Point p1 is point 1
 * Parameter: Point p2 is point 2
 * Return: the distance between the two points
 */
double dist(Point p1, Point p2);

/*
 * Description: optimizes the image to match the pixel format and colors
 * of the video framebuffer
 *
 * Parameter: SDL_Surface* s points to the SDL_Surface to optimize
 * Return: SDL_Surface pointer pointing to the converted surface that is compatible
 * to the display format
 */
SDL_Surface* optimizeImage(SDL_Surface* s);

/*
 * Description: sets the color key of the desired SDL_Surface based on
 * the specified Color argument
 *
 * Parameter: Surface::Color ck is the color key to set as transparent
 * Parameter: SDL_Surface* s is the pointer to surface whose color key is to be set
 */
void setColorKey(Surface::Color ck, SDL_Surface* s);

/*
 * Description: sets SDL_Color struct
 * Parameter: int r sets the red color (0-255 inclusive)
 * Parameter: int g sets the green color (0-255 inclusive)
 * Parameter: int b sets the blue color (0-255 inclusive)
 * Return: SDL_Color with the specifying parameters
 */
SDL_Color setRGBColor(int r, int g, int b);

/*
 * Description: parses Surface::Color color and returns the respective SDL_Color
 * Parameter: Surface::Color color is the color desired
 */
SDL_Color parseColor(Surface::Color color);

/*
 * Description: loads the image specified by filename and color key ck. Default argument for
 * ck is Surface::NONE representing that no color key is existent. It is optional to pass a
 * Color argument when calling the function, thus loadImage("/home/User/Pictures/image.png")
 * is valid.
 *
 * Return: the resulting SDL_Surface* specified by the parameters
 */
SDL_Surface* loadImage(string filename, Surface::Color ck = Surface::NONE);

/*
 * Description: opens the type of font at the specified size (pixel height)
 * Parameter: string pathtoTTF points to the file that contains the ttf font
 * Parameter: int size is the size of the font determined by pixel height
 * Parameter: Surface::Color color is the color of the text
 * Parameter: string msg is the text to be displayed
 * Return: TTF_Font pointer
 */
SDL_Surface* loadText(string pathToTTF, int size, Surface::Color color,
      string msg);

/*
 * Description: loadMusic loads the specified music via pathname
 * Parameter: string music is the music to load
 */
Mix_Music* loadMusic(string music);

/*
 * Description: loadChunk loads the specified sound effect via pathname
 * Parameter: string chunk is the sound effect chunk to load
 */
Mix_Chunk* loadChunk(string chunk);

/*
 * Description: blits the source image to the destination surface at the specified
 * coordinates and updates the destination surface
 *
 * Parameter: int x is the horizontal coordinate of where you want the image to be placed
 * on the destination surface starting from the upper left corner with
 * positive values to the right
 *
 * Parameter: int y is the vertical coordinate of where you want the image to be placed
 * on the destination surface starting from the upper left corner with positive values down
 *
 * Parameter: Surface source is the surface to be blitted to the destination surface
 * Parameter: SDL_Surface* destination is the surface being blitted onto (usually the screen
 * or surface active in system memory)
 *
 * Parameter: SDL_Rect* clip is optional and defines which portion of the source surface to
 * be cropped and blitted to the destination surface, i.e. the user an select part of the
 * source image to be blitted by defining this parameter
 */
void applySurface(int x, int y, Surface& source, SDL_Surface* destination,
      SDL_Rect* clip = NULL);

/*
 * Description: applies source surface to the middle of the screen
 * Parameter: Surface source is the source surface to be blitted to the destination surface
 * Parameter: SDL_Surface* destination is the surface active in system memory
 * Parameter: SDL_Rect* clip is an optional parameter specifying what to crop from the source
 */
void applySurfaceMiddle(Surface& source, SDL_Surface* destination,
      SDL_Rect* clip = NULL);

/*
 * Description: swaps the video buffers as to update the software screen
 * Parameter: SDL_Surface* screen is the screen in system memory
 */
void flip(SDL_Surface* screen);

/*
 * Description: retrieves the middle position relative to the vertical axis of the screen
 * Parameter: Surface& object is the reference to the object desired to be placed into the middle position
 * of the screen relative to the vertical axis of the screen
 *
 * Parameter: SDL_Surface* screen is the screen
 */
int getVerticalMiddlePosition(Surface& object, SDL_Surface* screen);

/*
 * Description: retrieves the middle position relative to the horizontal axis of
 * the screen
 *
 * Parameter: Surface& object is the reference to the object desired to be placed into the middle position
 * of the screen relative to the horizontal axis of the screen
 *
 * Parameter: SDL_Surface* screen is the screen
 */
int getHorizontalMiddlePosition(Surface& object, SDL_Surface* screen);

/*
 * Description: checks when the key is released. If the key hasn't been released,
 * isHeldDown returns true and vice versa.
 *
 * Parameter: SDL_Event& event is the event to be polled into the event queue
 * Return: true if key hasn't been released, false if released
 */
bool isHeldDown(SDL_Event& event);

/*
 * Description: fills screen with a color of choice
 * Parameter: SDL_Surface* screen is the screen to fill with the color
 * Parameter: Surface::Color color is the color to fill the screen with
 */
void fillScreen(SDL_Surface* screen, Surface::Color color);

/*
 * Description: init initializes all SDL subsystems, sets the video mode, and sets the caption
 * Parameter: int w is the width of the screen
 * Parameter: int h is the height of the screen
 * Parameter: string title is the window title
 * Return: returns an SDL_Surface* that represents the screen in system memory i.e.
 * the software display
 *
 * Example: SDL_Surface* screen = init(640, 480, "foo");
 */
SDL_Surface* init(int w, int h, string title);

/*
 * Description: calls the Quit methods for SDL, ttf, and audio
 */
void cleanUp();

#endif /* SDLABSTRACTIONLAYER_H */
