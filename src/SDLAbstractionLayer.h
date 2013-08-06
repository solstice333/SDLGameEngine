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
    * Description: delays frame with respect to user specified framerate
    * Parameter: int fps is the user specified framerate
    * Return: returns the the amount of time that needs to be delayed in milliseconds
    */
   int delayFrame(int fps);
};

/*
 * Description: The Figure class is a convenience class for creating dynamic moveable
 * objects on the screen.
 */
class Figure {
public:

   /*
    * Desciption: Enum Gravity represents if gravity is enabled or disabled
    */
   enum Gravity {
      GRAVITY_DISABLED, GRAVITY_ENABLED
   };

private:

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
    * Description: frame counter
    */
   int frame;

   /*
    * Description: true if gravity is enabled, false if Figure is intended to float
    */
   bool gravityEnabled;

   /*
    * Description: pauses gravity if collision on top
    */
   bool pauseGravity;

   /*
    * Description: speed is the fraction of dimensions covered per frame when Figure is moving. In other
    * words, in terms of horizontal movement along the x axis, a Figure could be 100 pixels
    * in width, so that would mean that if the speed is a value of 0.5, then the Figure
    * move 50 pixels per frame
    */
   double speed;

   /*
    * Description: bool l, r, u, d describes a flag that can be set in order to transmit a state
    * from the handleInput() method to any other method of the class. For example, when
    * the left button is pressed, the l flag is set, and in the show() method, the
    * Surface* left image is rendered as a result
    */
   bool l, r, u, d;

   /*
    * Descrption: holds the current x, y velocity of the Figure. Velocity in this context describes
    * how many pixels the Figure will cover within the next frame i.e. pixels per frame
    */
   Velocity v;

   /* 
    * Description: holds the pointer to screen. this is needed when grabbing the width and height
    * of the software display
    */
   SDL_Surface* screen;

   /*
    * Description: left Surface image to render when the Figure is moving to the left
    */
   Surface* left;

   /*
    * Description: right Surface image to render when the Figure is moving to the right
    */
   Surface* right;

   /*
    * Description: current Surface* image is the pointer to the most recent image rendered. This is
    * needed in the case where if the up button is pressed, then bool l and r are not set,
    * and the most recent image facing the most recent direction needs to be rendered
    */
   Surface* current;

   /*
    * Description: private method for calculating the velocity in the y component as a result from gravity.
    * Makes direct changes to v.y in Figure instance, and thus it is not necessary to store the return value 
    * to a location.
    *
    * Return: velocity of the Figure in the y component
    */
   int calculateGravity();

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
    */
   void initialize(int x, int y, double gravity, double speed,
         double jumpStrength, SDL_Surface* screen, Gravity gravityEnabled);

   /*
    * Description: xMovement() adjusts the current x position of the Figure while taking
    * into account colliding with Figure& other
    *
    * Parameter: Figure& other is the other Figure that cannot be collided with
    */
   void xMovement(vector<Figure>& other);

   /*
    * Description: yMovement() adjusts the current y position of the Figure while taking
    * into account colliding with Figure& other
    *
    * Parameter: Figure& other is the other Figure that cannot be collided with
    */
   void yMovement(vector<Figure>& other);

   /*
    * Description: debug() prints the current x and y positions and velocities real time
    */
   void debug();

public:

   /*
    * Description: Default constructor
    */
   Figure();

   /*
    * Description: Overloading Figure constructor for Figures that need an image when
    * moving left and right
    *
    * Parameter: int x is the x coordinate starting position of the Figure
    * Parameter: int y is the y coordinate starting position of the Figure
    * Parameter: Surface& left is the image to show when Figure is moving to the left
    * Parameter: Surface& right is the image to show when Figure is moving to the right
    * Parameter: SDL_Surface* screen is the software screen active in system memory
    * Parameter: double speed is the movement speed of the Figure in terms of percentage
    * of the dimensions of the Figure i.e. for horizontal movement, a speed value of 50
    * would indicate move 50% of the Figure width every frame
    *
    * Parameter: Gravity gravityEnabled is enum that specifies if gravity is enabled
    * or not for the Figure
    *
    * Parameter: int gravity is set to 1 by default and describes how strong the
    * gravity is. If GRAVITY_DISABLED is passed in as a parameter, this is disregarded
    * no matter what value is passed in for gravity
    *
    * Parameter: double jumpStrength is set to 1 by default and describes the jump
    * strength. If GRAVITY_DISABLED is passed in as a parameter, this is disregarded
    * no matter what value is passed in for jumpStrength
    */
   Figure(int x, int y, Surface& left, Surface& right, SDL_Surface* screen,
         Gravity gravityEnabled, double speed = 0, int gravity = 1,
         double jumpStrength = 1);

   /*
    * Description: Overloading Figure constructor for Figures that only need one image
    * Parameter: int x is the x coordinate starting position of the Figure
    * Parameter: int y is the y coordinate starting position of the Figure
    * Parameter: Surface& image is the image to show
    * Parameter: SDL_Surface* screen is the software screen active in system memory
    * Parameter: double speed is the movement speed of the Figure in terms of percentage
    * of the dimensions of the Figure i.e. for horizontal movement, a speed value of 50
    * would indicate move 50% of the Figure width every frame
    *
    * Parameter: Gravity gravityEnabled is enum that specifies if gravity is enabled
    * or not for the Figure
    *
    * Parameter: int gravity is set to 1 by default and describes how strong the
    * gravity is. If GRAVITY_DISABLED is passed in as a parameter, this is disregarded
    * no matter what value is passed in for gravity
    *
    * Parameter: double jumpStrength is set to 1 by default and describes the jump
    * strength. If GRAVITY_DISABLED is passed in as a parameter, this is disregarded
    * no matter what value is passed in for jumpStrength
    */
   Figure(int x, int y, Surface& image, SDL_Surface* screen,
         Gravity gravityEnabled, double speed = 0, int gravity = 1,
         double jumpStrength = 1);

   /*
    * Description: sets Figure
    * Parameter: int x is the x coordinate starting position of the Figure
    * Parameter: int y is the y coordinate starting position of the Figure
    * Parameter: Surface& left is the image to show when Figure is moving to the left
    * Parameter: Surface& right is the image to show when Figure is moving to the right
    * Parameter: SDL_Surface* screen is the software screen active in system memory
    * Parameter: double speed is the movement speed of the Figure in terms of percentage
    * of the dimensions of the Figure i.e. for horizontal movement, a speed value of 50
    * would indicate move 50% of the Figure width every frame
    *
    * Parameter: Gravity gravityEnabled is enum that specifies if gravity is enabled
    * or not for the Figure
    *
    * Parameter: int gravity is set to 1 by default and describes how strong the
    * gravity is. If GRAVITY_DISABLED is passed in as a parameter, this is disregarded
    * no matter what value is passed in for gravity
    *
    * Parameter: double jumpStrength is set to 1 by default and describes the jump
    * strength. If GRAVITY_DISABLED is passed in as a parameter, this is disregarded
    * no matter what value is passed in for jumpStrength
    */
   void setFigure(int x, int y, Surface& left, Surface& right,
         SDL_Surface* screen, Gravity gravityEnabled, double speed = 0,
         int gravity = 1, double jumpStrength = 1);

   /*
       * Description: sets Figure
       * Parameter: int x is the x coordinate starting position of the Figure
       * Parameter: int y is the y coordinate starting position of the Figure
       * Parameter: Surface& image is the image to show when Figure is moving
       * Parameter: SDL_Surface* screen is the software screen active in system memory
       * Parameter: double speed is the movement speed of the Figure in terms of percentage
       * of the dimensions of the Figure i.e. for horizontal movement, a speed value of 50
       * would indicate move 50% of the Figure width every frame
       *
       * Parameter: Gravity gravityEnabled is enum that specifies if gravity is enabled
       * or not for the Figure
       *
       * Parameter: int gravity is set to 1 by default and describes how strong the
       * gravity is. If GRAVITY_DISABLED is passed in as a parameter, this is disregarded
       * no matter what value is passed in for gravity
       *
       * Parameter: double jumpStrength is set to 1 by default and describes the jump
       * strength. If GRAVITY_DISABLED is passed in as a parameter, this is disregarded
       * no matter what value is passed in for jumpStrength
       */
   void setFigure(int x, int y, Surface& image, SDL_Surface* screen,
         Gravity gravityEnabled, double speed = 0, int gravity = 1,
         double jumpStrength = 1);

   /*
    * Description: obtains the width of the Figure
    */
   int getWidth();

   /*
    * Description: obtains the height of the Figure
    */
   int getHeight();

   /*
    * Description: checks if collided with other Figure
    * Parameter: Figure other is the Figure being compared to this Figure if collision
    * has occurred
    *
    * Return: true if collided, false otherwise
    */
   bool isCollided(vector<Figure>& other, int& count);

   /*
    * Description: handleInput() handles all input when dequeued from the event queue
    * using SDL_PollEvent()
    *
    * Parameter: SDL_Event& event is the event polled
    */
   void handleInput(SDL_Event& event);

   /*
    * Description; move() changes the current position based on the velocities
    * determined in handleInput() or in the internal calculateGravity() method
    *
    * Parameter: Figure other is the object that this Figure cannot pass through i.e.
    * collision is taken into account
    */
   void move(vector<Figure> other);

   /*
    * Description: show() applies the Figure to the screen
    */
   void show(SDL_Rect* clip = NULL);
};

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
 * starting from the upper left corner with positive values to the right
 *
 * Parameter: int y is the vertical coordinate of where you want the image to be placed
 * starting from the upper left corner with positive values down
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
 * Description: delays the frame based on timer and user defined fps. Be sure to start timer
 * at the beginning of the event loop
 *
 * Parameter: Timer timer is the timer being used to time the frame period
 * Parameter: int fps is the framerate requirement of the user
 */
void delayFrame(Timer timer, int fps);

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
