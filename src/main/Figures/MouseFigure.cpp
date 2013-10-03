/*
 * MouseFigure.cpp
 *
 *  Created on: Sep 6, 2013
 *      Author: Alles Rebel
 */

#include "MouseFigure.h"

//TODO commented out for now because dependent on Editor

/*
MouseFigure::MouseFigure(int x, int y, Surface* image, SDL_Surface* screen,
      int levelWidth, int levelHeight, int numClips) :
      Figure(x, y, *image, screen, Figure::GRAVITY_DISABLED, true, 0, 0, 0, 1,
            levelWidth, levelHeight) {
   this->y = y;
   this->x = x;
   header = NULL;
   container = NULL;
   SDL_GetMouseState(&x, &y);
   currentObject = none;
   currentObjectType = Editor::rectBoundaryFigure;
   imageSurf = NULL;
   tempObject = NULL;
   this->lvlHeight = lvlHeight;
   this->lvlWidth = lvlWidth;
}

MouseFigure::~MouseFigure() {

}

bool MouseFigure::checkCollision(CircFigure* other) {
   if (distance(other->getX(), other->getY()) < other->getR()) {
      return true;
   }
   else
      return false;
}

bool MouseFigure::checkCollision(RectFigure* other) {
   if (x <= other->getX() || x >= other->getX() + other->getWidth())
      return false;
   if (y <= other->getY() || y >= other->getY() + other->getHeight())
      return false;
   return true;
}

void MouseFigure::handleInput(SDL_Event& event) {
   if (event.type == SDL_MOUSEMOTION) {
      p.x = event.motion.x;
      p.y = event.motion.y;

      if (tempObject != NULL) {
         tempObject->setPosition(event.motion.x, event.motion.y);
      }
   }
   else if (event.type == SDL_MOUSEBUTTONDOWN) {
      switch (event.button.button) {
      case SDL_BUTTON_LEFT: {
         //get location of mouse currently
         SDL_GetMouseState(&x, &y);

         //add offsets to it based on camera clip
         x += camera->x;
         y += camera->y;

         SDL_Surface* screen = SDL_GetVideoSurface();

         //load the image for the surface based on currentobject
         Surface* image = NULL;
         switch (currentObject) {
         case redWall: {
            image = new Surface("images/rectangle.png");
            break;
         }
         case blackdot: {
            image = new Surface("images/dot.png", Surface::CYAN);
            break;
         }
         case cloud: {
            image = new Surface("images/grab.png", Surface::CYAN);
            break;
         }
         case coin: {
            image = new Surface("images/coin.png", Surface::CYAN);
            break;
         }
         case none: {
            //No object selected - delete if there's an object under
            int index = 0;
            printf("No object selected - attempting delete!\n");
            if (isCollided(*container, index)) {
               printf("Found an object!\n");
               //found an object under mouse - free it's memeory
               delete container->at(index);
               container->erase(container->begin() + index);
            }
            return;
            break;
         }
         }

         //Load the figure assoicated with the current Object
         Figure* finalObject = NULL;
         switch (currentObjectType) {
         case Editor::rectBoundaryFigure: {
            finalObject = new RectBoundaryFigure(x, y, *image, screen, lvlWidth,
                  lvlHeight, 1);
            break;
         }
         case Editor::grabbableFigure: {
            finalObject = new GrabbableFigure(x, y, *image, screen, lvlWidth,
                  lvlHeight, 1);
            break;
         }
         case Editor::circBoundryFigure: {
            finalObject = new CircBoundaryFigure(
                  x + image->getSDL_Surface()->w / 2,
                  y + image->getSDL_Surface()->h / 4, *image, screen, lvlWidth,
                  lvlHeight, 1);
            break;
         }

         case Editor::tempFigure: {
            finalObject = new TempFigure(x, y, *image, screen, lvlWidth,
                  lvlHeight);
            break;
         }

         case Editor::cursorFigure: {
            finalObject = new CursorFigure(x, y, *image, screen,
            NULL);
            break;
         }
         }

         //turn of grav for the figure
         finalObject->setGravEnable(Figure::GRAVITY_DISABLED);

         //place the final figure into the container
         container->push_back(finalObject);

         break;
      }
      }
   }
   else if (event.type == SDL_KEYDOWN) {
      switch (event.key.keysym.sym) {
      case SDLK_1: {

         if (currentObject != redWall) {

            //free up memory used by previous selection
            clearLocalMemory();

            //get location of mouse currently
            SDL_GetMouseState(&x, &y);

            //load image
            imageSurf = new Surface("images/rectangle.png", Surface::CYAN);

            //and place the object there
            tempObject = new MouseFigure(x, y, imageSurf, screen, lvlWidth,
                  lvlHeight, 1);

            currentObject = redWall;
            currentObjectType = Editor::rectBoundaryFigure;
         }
         break;
      }
      case SDLK_2:
         //coin Placement
         if (currentObject != coin) {
            //free up memory used by previous selection
            clearLocalMemory();

            //get location of mouse currently
            SDL_GetMouseState(&x, &y);

            //load image
            imageSurf = new Surface("images/coin.png", Surface::CYAN);

            //and place the object there
            tempObject = new MouseFigure(x, y, imageSurf, screen, lvlWidth,
                  lvlHeight, 1);

            currentObject = coin;
            currentObjectType = Editor::tempFigure;
         }
         break;

      case SDLK_3:
         if (currentObject != cloud) {
            //free up memory used by previous selection
            clearLocalMemory();

            //get location of mouse currently
            SDL_GetMouseState(&x, &y);

            //load image
            imageSurf = new Surface("images/grab.png", Surface::CYAN);

            //and place the object there
            tempObject = new MouseFigure(x, y, imageSurf, screen, lvlWidth,
                  lvlHeight, 1);

            currentObject = cloud;
            currentObjectType = Editor::grabbableFigure;
         }
         break;

      case SDLK_4:
         if (currentObject != blackdot) {
            //free up memory used by previous selection
            clearLocalMemory();

            //get location of mouse currently
            SDL_GetMouseState(&x, &y);

            //load image
            imageSurf = new Surface("images/dot.png", Surface::CYAN);

            //and place the object there
            tempObject = new MouseFigure(x, y, imageSurf, screen, lvlWidth,
                  lvlHeight, 1);

            currentObject = blackdot;
            currentObjectType = Editor::circBoundryFigure;
         }
         break;

      case SDLK_ESCAPE:
         if (currentObject != none) {
            delete tempObject;
            tempObject = NULL;

            currentObject = none;
         }
         break;

      case SDLK_s: {
         //save this map to level.txt
         //TODO: probably should allow user to customize this

         Editor saveLevel("resources/level.txt", Editor::write);
         saveLevel.writeHeader(*header);
         saveLevel.encode(container, *header);

         break;
      }

      case SDLK_l: {
         //force load map from level.txt

         Editor loadLevel("resources/level.txt", Editor::read);
         loadLevel.readHeader();
         clearContainer();
         container = NULL;
         container = loadLevel.decode();
         loadLevel.closeFile();
         break;
      }
      default:
         break;
      }
   }
}

void MouseFigure::setContainer(vector<Figure*>* src) {
   container = src;
}

void MouseFigure::setPosition(int x, int y) {
   this->p.x = x;
   this->p.y = y;
}

void MouseFigure::setHeightWidth(int h, int w) {
   lvlHeight = h;
   lvlWidth = w;
}

void MouseFigure::setHeader(Header* input) {
   header = input;
}

float MouseFigure::distance(int x, int y) {
   float xresult = this->x - x;
   xresult *= xresult;

   float yresult = this->y - y;
   yresult *= yresult;

   float result = sqrt(xresult + yresult);

   return result;
}

void MouseFigure::clearLocalMemory() {
   //free memory used by previous surface
   delete imageSurf;
   imageSurf = NULL;

   //free memory used by tempObject Earlier
   delete tempObject;
   tempObject = NULL;
}

void MouseFigure::clearContainer() {
   for (unsigned int i = 0; i < container->size(); i++) {
      delete container->at(i);
   }
   container->clear();
}
*/
