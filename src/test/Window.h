/*
 * Window.h
 *
 *  Created on: Aug 20, 2013
 *      Author: knavero
 */

#ifndef WINDOW_H_
#define WINDOW_H_

#include "../main/SDLAbstractionLayer.h"

class Window {
private:
   bool windowed;
   bool windowOK;
   SDL_Surface*& screen;
   SDL_Rect dims;
public:
   Window(SDL_Surface*& screen, int initWidth, int initHeight);
   void handleEvents(SDL_Event& event);
   void toggleFullscreen();
   bool error();
};


#endif /* WINDOW_H_ */
