/*
 * PlayerFigure.cpp
 *
 *  Created on: Sep 10, 2013
 *      Author: knavero
 */

#include "PlayerFigure.h"

PlayerFigure::PlayerFigure() {
}

PlayerFigure::PlayerFigure(int x, int y, Surface& image, SDL_Surface* screen,
      double speed, double gravity, double jumpStrength, int numClips,
      int levelWidth, int levelHeight, Surface* p1, Surface* p2, Surface* p3,
      Surface* p4) :
      RectFigure(x, y, image, screen, GRAVITY_ENABLED, levelWidth, levelHeight,
            true, speed, gravity, jumpStrength, numClips, p1, p2, p3, p4), target(
            "images/target.png", Surface::CYAN) {
   cursor_x = cursor_y = 0;
}

void PlayerFigure::setFigure(int x, int y, Surface& image, SDL_Surface* screen,
      double speed, double gravity, double jumpStrength, int numClips,
      int levelWidth, int levelHeight, Surface* p1, Surface* p2, Surface* p3,
      Surface* p4) {
   Figure::setFigure(x, y, image, screen, GRAVITY_ENABLED, levelWidth,
         levelHeight, true, speed, gravity, jumpStrength, numClips, p1, p2, p3,
         p4);
   target.setSDL_Surface("images/target.png", Surface::CYAN);
   cursor_x = cursor_y = 0;
}

void PlayerFigure::handleInput(SDL_Event& event) {
   if (event.type == SDL_KEYDOWN) {
      switch (event.key.keysym.sym) {
      case SDLK_w:
         if ((!jumpAction && !inAir))
            v.y -= dim.h * speed / 100 * jumpStrength;

         u = true;
         break;
      case SDLK_a:
         v.x -= dim.w * speed / 100;
         l = true;
         break;
      case SDLK_d:
         v.x += dim.w * speed / 100;
         r = true;
         break;
      default:
         break;
      }
   }

   else if (event.type == SDL_KEYUP) {
      switch (event.key.keysym.sym) {
      case SDLK_a:
         v.x += dim.w * speed / 100;
         l = false;
         break;
      case SDLK_d:
         v.x -= dim.w * speed / 100;
         r = false;
         break;
      default:
         break;
      }
   }

   else if (event.type == SDL_MOUSEMOTION) {
      cursor_x = event.button.x;
      cursor_y = event.button.y;
   }
}

void PlayerFigure::resolveCollision(Figure* other, double timeStep,
      Component dir) {
   if (typeid(*other) == typeid(RectBoundaryFigure)
         || typeid(*other) == typeid(CircBoundaryFigure)) {
      if (dir == XHAT)
         p.x -= v.x * timeStep / 1000.0;
      else if (dir == YHAT) {
         p.y -= v.y * timeStep / 1000.0;
         if (gravityEnabled)
            v.y = 0;
      }
   }

   else if (typeid(*other) == typeid(TempFigure))
      inAir = true;
}

void PlayerFigure::show() {
   if (numClips > 0) {
      if (v.x < 0) {
         status = LEFT;
         animationFrame += AFVALUE;
      }
      else if (v.x > 0) {
         status = RIGHT;
         animationFrame += AFVALUE;
      }
      if (v.x == 0 || animationFrame >= numClips)
         animationFrame = 0;

      if (status == LEFT)
         applySurface((int) p.x - camera->x, (int) p.y - camera->y, *image,
               screen, &cl[static_cast<int>(animationFrame)]);
      else if (status == RIGHT)
         applySurface((int) p.x - camera->x, (int) p.y - camera->y, *image,
               screen, &cr[static_cast<int>(animationFrame)]);

      if (particleEffects)
         showParticles(camera);

      applySurface(cursor_x - target.getSDL_Surface()->w / 2,
            cursor_y - target.getSDL_Surface()->h / 2, target, screen);
   }
}
