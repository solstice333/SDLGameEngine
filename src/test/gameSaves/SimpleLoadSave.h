/*
 * Load.h
 *
 *  Created on: Aug 18, 2013
 *      Author: knavero
 */

#ifndef SIMPLELOADSAVE_H_
#define SIMPLELOADSAVE_H_

#include "Dot.h"
#include "../../main/Exception.h"
#include <fstream>

using namespace std;

bool loadSavedGame(Dot& dot, Surface::Color& bg, Surface& source,
      SDL_Surface* screen);
bool saveGame(Dot& dot, Surface::Color& bg);

#endif /* SIMPLELOADSAVE_H_ */
