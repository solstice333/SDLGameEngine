/*
 * Load.cpp
 *
 *  Created on: Aug 18, 2013
 *      Author: knavero
 */

#include "SimpleLoadSave.h"
#include <iostream>

using namespace std;

bool loadSavedGame(Dot& dot, Surface::Color& bg, Surface& source,
      SDL_Surface* screen) {
   ifstream load("resources/gameSave");

   if (load != NULL && load.is_open()) {
      Position offset;
      int r;
      int level;

      //read in position x and y from ifstream. If ifstream structure/syntax is wrong,
      //then throw exception
      if (!(load >> offset.x))
         throw LoadSavedGameException();
      if (!(load >> offset.y))
         throw LoadSavedGameException();

      cout << "successfully set Position offset" << endl;

      //set a radius based on the source surface, then sanity check the position offset
      //in case input file was edited by player
      if (source.getSDL_Surface()->w > source.getSDL_Surface()->h)
         r = source.getSDL_Surface()->w / 2;
      else
         r = source.getSDL_Surface()->h / 2;

      if (offset.x < r || offset.x > screen->w - r)
         throw LoadSavedGameException();
      if (offset.y < r || offset.y > screen->h - r)
         throw LoadSavedGameException();

      cout << "Position offset is within bounds" << endl;
      cout << "offset.x: " << offset.x << endl;
      cout << "offset.y: " << offset.y << endl;

      //set dot's privates
      dot.setDot(offset.x, offset.y, source, screen);

      //read in level background
      load.ignore(); //ignore line feed '\n' to move the seek cursor to the next line

      if (load >> level && level >= 0 && level <= 6)
         bg = static_cast<Surface::Color>(level);
      else
         throw LoadSavedGameException();

      cout << "Successfully set level and level is within enum bounds" << endl;

      // enum map: NONE = 0, RED = 1, GREEN = 2, BLUE = 3, CYAN = 4, BLACK = 5, WHITE = 6
      cout << "level: " << level << endl;
      cout << "c.r: "
            << static_cast<int>(parseColor(static_cast<Surface::Color>(level)).r)
            << endl;
      cout << "c.g: "
            << static_cast<int>(parseColor(static_cast<Surface::Color>(level)).g)
            << endl;
      cout << "c.b: "
            << static_cast<int>(parseColor(static_cast<Surface::Color>(level)).b)
            << endl;

      load.close();
   }
   else
      return false;

   return true;
}

bool saveGame(Dot& dot, Surface::Color& bg) {
   ofstream save("resources/gameSave");

   if (!save.is_open())
      return false;

   save << dot.getPosition().x << " ";
   save << dot.getPosition().y << endl;
   save << bg;

   save.close();

   return true;
}
