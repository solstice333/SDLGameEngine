/*
 * PlayerFigure.cpp
 *
 *  Created on: Sep 10, 2013
 *      Author: knavero
 */

#include "PlayerFigure.h"

void PlayerFigure::determineGrabX() {
   //TODO this needs to be animated with the PlayerFigure moving toward the GrabbableFigure
   //instead of teleporting
   if (grabstate) {
      p.x = cursor.getGrabbableFigure()->getX();
   }

}

void PlayerFigure::determineGrabY() {
   //TODO this needs to be animated with the PlayerFigure moving toward the GrabbableFigure
   //instead of teleporting
   if (grabstate) {
      p.y = cursor.getGrabbableFigure()->getY();
   }
}

void PlayerFigure::checkIfInAir(vector<Figure*>& other) {
   int count = 0;

   inAir = true;
   p.y += 3;

   //standing on ground or other Figure
   if ((v.y == 0 && p.y >= lh - dim.h)
         || (v.y <= gravity && isCollided(other, count)))
      inAir = false;
   p.y -= 3;

   //peak of trajectory
   if (p.y < lh - dim.h && v.y <= 0.5 && v.y >= -0.5)
      inAir = true;

   //collided with TempFigure or GrabbableFigure
   if (count != -1
         && (typeid(*other[count]) == typeid(TempFigure)
               || typeid(*other[count]) == typeid(GrabbableFigure)))
      inAir = true;
}

void PlayerFigure::xMovement(vector<Figure*>& other, int deltaTicks) {
   int count = 0;

   //x movement grabstate
   determineGrabX();

   p.x += v.x * deltaTicks / 1000.0;

   if (isCollided(other, count) && count != -1)
      resolveCollision(other[count], deltaTicks, XHAT);
   else if (p.x > lw - dim.w)
      p.x = lw - dim.w;
   else if (p.x < 0)
      p.x = 0;
}

void PlayerFigure::yMovement(vector<Figure*>& other, int deltaTicks) {
   int count = 0;

   //gravity considerations
   determineGravity();

   //jump action
   determineJump();

   //check if inAir is true
   checkIfInAir(other);

   //y movement grabstate
   determineGrabY();

   //collision with boundaries or other Figures
   p.y += v.y * deltaTicks / 1000.0;

   if (isCollided(other, count) && count != -1)
      resolveCollision(other[count], deltaTicks, YHAT);
   else if (p.y > lh - dim.h)
      p.y = lh - dim.h;
}

PlayerFigure::PlayerFigure() {
}

PlayerFigure::PlayerFigure(int x, int y, Surface& image, SDL_Surface* screen,
      double speed, double gravity, double jumpStrength, int numClips,
      int levelWidth, int levelHeight, Surface* p1, Surface* p2, Surface* p3,
      Surface* p4) :
      RectFigure(x, y, image, screen, GRAVITY_ENABLED, levelWidth, levelHeight,
            true, speed, gravity, jumpStrength, numClips, p1, p2, p3, p4), target(
            "images/target2.png", Surface::CYAN), cursor(x, y, target, screen,
            camera), grabstate(false) {
}

void PlayerFigure::setFigure(int x, int y, Surface& image, SDL_Surface* screen,
      double speed, double gravity, double jumpStrength, int numClips,
      int levelWidth, int levelHeight, Surface* p1, Surface* p2, Surface* p3,
      Surface* p4) {
   Figure::setFigure(x, y, image, screen, GRAVITY_ENABLED, levelWidth,
         levelHeight, true, speed, gravity, jumpStrength, numClips, p1, p2, p3,
         p4);
   target.setSDL_Surface("images/target2.png", Surface::CYAN);
   cursor.setFigure(x, y, target, screen, camera);
   grabstate = false;
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

   cursor.handleInput(event);
}

void PlayerFigure::move(vector<Figure*>& other, int deltaTicks) {
   grabstate = cursor.getGrabState();

   xMovement(other, deltaTicks);
   yMovement(other, deltaTicks);

   cursor.move(other, deltaTicks);

   setCamera();
}

void PlayerFigure::resolveCollision(Figure* other, double timeStep,
      Component dir) {
   if (typeid(*other) == typeid(TempFigure))
      inAir = true;
   else if (typeid(*other) == typeid(RectBoundaryFigure)
         || typeid(*other) == typeid(CircBoundaryFigure)) {
      if (dir == XHAT)
         p.x -= v.x * timeStep / 1000.0;
      else if (dir == YHAT) {
         p.y -= v.y * timeStep / 1000.0;
         if (gravityEnabled)
            v.y = 0;
      }
   }
   else if (typeid(*other) == typeid(GrabbableFigure)) {
      grabstate = false;
      cursor.setGrabState(grabstate);
   }
}

void PlayerFigure::show(SDL_Rect* otherCamera) {
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
         applySurface(static_cast<int>(p.x) - camera->x,
               static_cast<int>(p.y) - camera->y, *image, screen,
               &cl[static_cast<int>(animationFrame)]);
      else if (status == RIGHT)
         applySurface(static_cast<int>(p.x) - camera->x,
               static_cast<int>(p.y) - camera->y, *image, screen,
               &cr[static_cast<int>(animationFrame)]);

      if (particleEffects)
         showParticles(camera);

      cursor.show();
   }
}
