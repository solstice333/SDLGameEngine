#ifndef SDLABSTRACTIONLAYER_H
#define SDLABSTRACTIONLAYER_H

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <string>
#include <vector>
using namespace std;

const bool DEBUG_PRIVATES = false;
const bool DEBUG_MOVE = false;
const bool DEBUG_HANDLE_INPUT = false;
const bool DEBUG_CAM = false;

//TODO make AFVALUE and TOTAL_PARTICLES user controlled
/*
 * Description: the greater AFVALUE is, the faster the animation sprites switchover
 */
const double AFVALUE = 0.03;

/*
 * Description: the greater JUMP_SMOOTHENER is the smoother the jump, but possibly worse
 * the collision
 */
const int JUMP_SMOOTHENER = 20;

/*
 * Description: total amount of particles. The higher the amount of particles, the
 * more particles show up on the screen.
 */
const int TOTAL_PARTICLES = 20;

/*
 * Description: allows for drag control of the particles
 */
const int PARTICLE_DRAG_MIN = 200;
const int PARTICLE_DRAG_MAX = 2000;

//struct describing current position on both x and y components
struct Position {
   double x, y;
};

//struct describing current velocity on both x and y components
struct Velocity {
   double x, y;
};

//struct describing a point
struct Point {
   double x, y;
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
    * Description: checks if Surface is empty. True if empty, false otherwise.
    */
   bool isEmpty();

   /*
    * Description: clears the Surface by making SDL_Surface* s NULL
    */
   void clear();

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
 * Description: Particle Engine
 */
class Particle {
private:
   /*
    * Description: dimension range of where to place the particle
    */
   SDL_Rect dim;

   /*
    * Description: position of the particle
    */
   Position p;

   /*
    * Description: particle frame counter
    */
   int frame;

   /*
    * Description: pointer to type of particle to show
    */
   Surface* type;

   /*
    * Description: pointer to particle 1
    */
   Surface* p1;

   /*
    * Description: pointer to particle 2
    */
   Surface* p2;

   /*
    * Description: pointer to particle 3
    */
   Surface* p3;

   /*
    * Description: pointer to particle 4
    */
   Surface* p4;

   /*
    * Description: pointer to screen
    */
   SDL_Surface* screen;

public:

   /*
    * Description: Particle constructor
    * Parameter: double x contains the x coordinate specifying position of the upper left
    * corner of the source image that the particles are following
    *
    * Parameter: double y contains the y coordinate specifying position of the upper left
    * corner of the source image that the particles are following
    *
    * Parameter: SDL_Rect dim contains the position of where to generally place the
    * particle and the dimensions of the source image of where the particles are to appear
    * around
    *
    * Parameter: Surface* p1 is the pointer to particle 1
    * Parameter: Surface* p2 is the pointer to particle 2
    * Parameter: Surface* p3 is the pointer to particle 3
    * Parameter: Surface* p4 is the pointer to particle 4
    * Parameter: Point to screen
    */
   Particle(double x, double y, SDL_Rect dim, Surface* p1, Surface* p2,
         Surface* p3, Surface* p4, SDL_Surface* screen);

   /*
    * Description: Applies particle to screen
    * Parameter: SDL_Rect* camera is the pointer to the relative camera. The relative camera
    * is the camera that follows the leader Figure
    */
   void show(SDL_Rect* camera);

   /*
    * Description: Checks if the particle is dead. True is dead, false otherwise.
    */
   bool isDead();
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
 * Exception: throws ConversionException()
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
 * Exceptions: throws InvalidColorException();
 */
SDL_Color parseColor(Surface::Color color);

/*
 * Description: loads the image specified by filename and color key ck. Default argument for
 * ck is Surface::NONE representing that no color key is existent. It is optional to pass a
 * Color argument when calling the function, thus loadImage("/home/User/Pictures/image.png")
 * is valid.
 *
 * Parameter: string filename is the path to the image file
 * Parameter: Surface::Color ck represents the color you want to colorkey
 * Exceptions: throws LoadImageException()
 * Return: the resulting SDL_Surface* specified by the parameters
 */
SDL_Surface* loadImage(string filename, Surface::Color ck = Surface::NONE);

/*
 * Description: opens the type of font at the specified size (pixel height)
 * Parameter: string pathtoTTF points to the file that contains the ttf font
 * Parameter: int size is the size of the font determined by pixel height
 * Parameter: Surface::Color color is the color of the text
 * Parameter: string msg is the text to be displayed
 * Exception: throws LoadTextException()
 * Return: TTF_Font pointer
 */
SDL_Surface* loadText(string pathToTTF, int size, Surface::Color color,
      string msg);

/*
 * Description: loadMusic loads the specified music via pathname
 * Parameter: string music is the music to load
 * Exception: throws LoadMusicException()
 * Return: Mix_Music pointer
 */
Mix_Music* loadMusic(string music);

/*
 * Description: loadChunk loads the specified sound effect via pathname
 * Parameter: string chunk is the sound effect chunk to load
 * Exception: throws LoadChunkException()
 * Return: Mix_Chunk pointer
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
 * Exception: throws FlipException()
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
 * Description: returns a random number within the specified range (inclusive). Initialize
 * pseudo random number generator using srand(time(NULL)) or srand(SDL_GetTicks()) before
 * using this function
 *
 * Parameter: int low is the minimum value of the range
 * Parameter: int high is the maximum value of the range
 */
int randRange(int low, int high);

/*
 * Description: returns the slope based on two points given (A and B)
 * Parameter: Point A is the first point
 * Parameter: Point B is the second point
 */
double slope(Point A, Point B);

/*
 * Description: returns a point on the line associated to int x passed in as an arg
 * Parameter: double m is the slope of the line
 * Parameter: Point p is any point on the line
 * Parameter: int x is the x point associated with the y output that we are interested in
 */
Point pointOnLine(double m, Point p, double x);

/*
 * Description: init initializes all SDL subsystems, sets the video mode, and sets the caption
 * Parameter: int w is the width of the screen
 * Parameter: int h is the height of the screen
 * Parameter: string title is the window title
 * Exception: throws InitException()
 * Exception: throws SetVideoException()
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
