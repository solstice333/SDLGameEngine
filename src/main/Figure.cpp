/*
 * Figure.cpp
 *
 *  Created on: Sep 4, 2013
 *      Author: knavero
 */

#include "Figure.h"

int Figure::determineGravity() {
   if (gravityEnabled && !u) {
      if (p.y < lh - dim.h)
         v.y += gravity + abs(0.01 * v.y);
      else
         v.y = 0;
   }

   return v.y;
}

int Figure::determineJump() {
   if (gravityEnabled && u && !jumpAction) {
      jumpAction = true;
      u = false;
   }
   else if (!u && gravityEnabled && jumpAction && jumpFrame < 5) {
      v.y += abs(v.y / JUMP_SMOOTHENER);
      jumpFrame++;
   }
   else {
      jumpFrame = 0;
      jumpAction = false;
   }

   return v.y;
}

void Figure::checkIfInAir(vector<Figure*>& other) {
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
}

void Figure::initialize(int x, int y, double gravity, double speed,
      double jumpStrength, SDL_Surface* screen, Gravity gravityEnabled,
      bool leader, int numClips, int levelWidth, int levelHeight, Surface* p1,
      Surface* p2, Surface* p3, Surface* p4) {
   p.x = x;
   p.y = y;
   this->leader = leader;

   jumpFrame = 0;
   this->numClips = numClips;
   cl = new SDL_Rect[numClips];
   cr = new SDL_Rect[numClips];
   status = RIGHT;

   setClips(dim.w, dim.h);

   this->gravity = gravity;
   this->speed = speed;
   if (jumpStrength < 1)
      this->jumpStrength = 1;

   this->jumpStrength = jumpStrength;
   jumpAction = false;

   l = r = u = d = false;
   this->screen = screen;

   v.x = v.y = 0;

   switch (gravityEnabled) {
   case GRAVITY_ENABLED:
      this->gravityEnabled = true;
      break;
   case GRAVITY_DISABLED:
      this->gravityEnabled = false;
      this->jumpStrength = 1;
      break;
   default:
      throw GravityException();
      break;
   }

   camera = new SDL_Rect;

   if (levelWidth == -1)
      lw = screen->w;
   else
      lw = levelWidth;

   if (levelHeight == -1)
      lh = screen->h;
   else
      lh = levelHeight;

   camera->x = camera->y = 0;
   camera->w = screen->w;
   camera->h = screen->h;

   particleEffects = false;
   this->p1 = this->p2 = this->p3 = this->p4 = NULL;

   if (p1 != NULL) {
      particleEffects = true;
      this->p1 = p1;
   }
   if (p2 != NULL) {
      particleEffects = true;
      this->p2 = p2;
   }
   if (p3 != NULL) {
      particleEffects = true;
      this->p3 = p3;
   }
   if (p4 != NULL) {
      particleEffects = true;
      this->p4 = p4;
   }

   if (particleEffects) {
      for (int i = 0; i < TOTAL_PARTICLES; i++) {
         particles[i] = new Particle(p.x, p.y, dim, this->p1, this->p2,
               this->p3, this->p4, screen);
      }
   }
   else {
      for (int i = 0; i < TOTAL_PARTICLES; i++) {
         particles[i] = NULL;
      }
   }
}

void Figure::setClips(int clipWidth, int clipHeight) {
   for (int i = 0; i < numClips; i++) {
      cr[i].w = clipWidth;
      cr[i].h = clipHeight;
      cr[i].x = clipWidth * i;
      cr[i].y = 0;

      cl[i].w = clipWidth;
      cl[i].h = clipHeight;
      cl[i].x = clipWidth * i;
      cl[i].y = clipHeight;
   }
}

void Figure::xMovement(vector<Figure*>& other, int deltaTicks) {
   int count = 0;

   p.x += v.x * deltaTicks / 1000.0;

   if (isCollided(other, count) && count != -1)
      resolveCollision(other[count], deltaTicks, XHAT);
   else if (p.x > lw - dim.w)
      p.x = lw - dim.w;
   else if (p.x < 0)
      p.x = 0;
}

void Figure::yMovement(vector<Figure*>& other, int deltaTicks) {
   int count = 0;

   //gravity considerations
   determineGravity();

   //jump action
   determineJump();

   //check if inAir is true
   checkIfInAir(other);

   //collision with boundaries or other Figures
   p.y += v.y * deltaTicks / 1000.0;

   if (isCollided(other, count) && count != -1)
      resolveCollision(other[count], deltaTicks, YHAT);
   else if (p.y > lh - dim.h)
      p.y = lh - dim.h;
}

void Figure::setCamera() {
   camera->x = p.x + dim.w / 2 - camera->w / 2;
   camera->y = p.y + dim.h / 2 - camera->h / 2;

   if (camera->x < 0)
      camera->x = 0;
   if (camera->y < 0)
      camera->y = 0;
   if (camera->x > lw - camera->w)
      camera->x = lw - camera->w;
   if (camera->y > lh - camera->h)
      camera->y = lh - camera->h;

   if (DEBUG_CAM) {
      cout << "camera->x: " << camera->x << endl;
      cout << "camera->y: " << camera->y << endl;
   }
}

void Figure::debug() {
   cout << "p.x: " << p.x << endl;
   cout << "p.y: " << p.y << endl;
   cout << "dim.w: " << dim.w << endl;
   cout << "dim.h: " << dim.h << endl;
   cout << "gravity: " << this->gravity << endl;
   cout << "jumpstrength: " << this->jumpStrength << endl;
   cout << "speed: " << this->speed << endl;
   cout << "jumpframe: " << jumpFrame << endl;
   cout << "animationframe: " << animationFrame << endl;
   cout << "numClips: " << this->numClips << endl;
   cout << "status: ";
   switch (status) {
   case LEFT:
      cout << "LEFT" << endl;
      break;
   case RIGHT:
      cout << "RIGHT" << endl;
      break;
   default:
      cout << "ERROR: invalid enum" << endl;
      break;
   }
   cout << "Checking cl and cr for validity. "
         << "If program crashes here, then cl and cr are not initialized properly."
         << endl;
   cout << "cl[1].w: " << cl[1].w << endl;
   cout << "cr[1].w: " << cr[1].w << endl;
   cout << "gravityEnabled: " << gravityEnabled << endl;
   cout << "l: " << l << endl;
   cout << "r: " << r << endl;
   cout << "u: " << u << endl;
   cout << "d: " << d << endl;
   cout << "className: " << className << endl;
   cout << "Checking velocity for validity. "
         << "If program crashes here, then v.x and v.y are not initialized properly."
         << endl;
   cout << "v.x, v.y: " << v.x << ", " << v.y << endl;
   cout << "Checking screen for validity. "
         << "If program crashes here, then screen is not initialized properly."
         << endl;
   cout << "screen->w: " << this->screen->w << endl;
   cout << "Checking Surface* image for validity. "
         << "If program crashes here, then image is not initialized properly. "
         << endl;
   cout << "Surface* image width: " << this->image->getSDL_Surface()->w << endl;
   cout << "Checking SDL_Rect* camera for validity. "
         << "If program crashes here, then camera is not initialized properly. "
         << endl;
   cout << "camera->w: " << this->camera->w << endl;
   cout << "lw, lh: " << lw << ", " << lh << endl;
   cout << "leader: " << leader << endl;
   cout << endl;
}

Figure::Figure() {
}

Figure::Figure(int x, int y, Surface& image, SDL_Surface* screen,
      Gravity gravityEnabled, bool leader, double speed, double gravity,
      double jumpStrength, int numClips, int levelWidth, int levelHeight,
      Surface* p1, Surface* p2, Surface* p3, Surface* p4) :
      image(&image) {

   dim.w = image.getSDL_Surface()->w / numClips;
   dim.h = image.getSDL_Surface()->h / 2;

   initialize(x, y, gravity, speed, jumpStrength, screen, gravityEnabled,
         leader, numClips, levelWidth, levelHeight, p1, p2, p3, p4);
}

void Figure::setFigure(int x, int y, Surface& image, SDL_Surface* screen,
      Gravity gravityEnabled, int levelWidth, int levelHeight, bool leader,
      double speed, double gravity, double jumpStrength, int numClips,
      Surface* p1, Surface* p2, Surface* p3, Surface* p4) {

   dim.w = image.getSDL_Surface()->w / numClips;
   dim.h = image.getSDL_Surface()->h / 2;
   this->image = &image;

   initialize(x, y, gravity, speed, jumpStrength, screen, gravityEnabled,
         leader, numClips, levelWidth, levelHeight, p1, p2, p3, p4);

   if (DEBUG_PRIVATES && this->className == "RectFigure")
      debug();
}

int Figure::getWidth() {
   return dim.w;
}

int Figure::getHeight() {
   return dim.h;
}

int Figure::getX() {
   return p.x;
}

int Figure::getY() {
   return p.y;
}

bool Figure::checkCollision(Figure* f) {
   RectFigure* r;
   CircFigure* c;

   if (f->getClassName() == "RectFigure") {
      r = static_cast<RectFigure*>(f);
      if (checkCollision(r))
         return true;
   }
   else if (f->getClassName() == "CircFigure") {
      c = static_cast<CircFigure*>(f);
      if (checkCollision(c))
         return true;
   }
   else
      throw FigureException();

   return false;
}

bool Figure::isCollided(vector<Figure*>& other, int& count) {
   if (!other.empty()) {
      for (vector<Figure*>::iterator i = other.begin(), end = other.end();
            i != end; i++) {
         if (*this != **i && checkCollision(*i))
            return true;

         count++;
      }

      if (count == other.size())
         count = -1;
   }

   return false;
}

void Figure::handleInput(SDL_Event& event) {
   if (event.type == SDL_KEYDOWN) {
      switch (event.key.keysym.sym) {
      case SDLK_UP:
         if ((!jumpAction && !inAir) || !gravityEnabled)
            v.y -= dim.h * speed / 100 * jumpStrength;

         u = true;
         if (inAir)
            u = false;

         break;
      case SDLK_DOWN:
         if (!gravityEnabled)
            v.y += dim.h * speed / 100;

         d = true;
         break;
      case SDLK_LEFT:
         v.x -= dim.w * speed / 100;
         l = true;
         break;
      case SDLK_RIGHT:
         v.x += dim.w * speed / 100;
         r = true;
         break;
      default:
         break;
      }
   }

   else if (event.type == SDL_KEYUP) {
      switch (event.key.keysym.sym) {
      case SDLK_UP:
         if (!gravityEnabled)
            v.y += dim.h * speed / 100 * jumpStrength;

         u = false;
         break;
      case SDLK_DOWN:
         if (!gravityEnabled)
            v.y -= dim.h * speed / 100;

         d = false;
         break;
      case SDLK_LEFT:
         v.x += dim.w * speed / 100;
         l = false;
         break;
      case SDLK_RIGHT:
         v.x -= dim.w * speed / 100;
         r = false;
         break;
      default:
         break;
      }
   }

   if (DEBUG_HANDLE_INPUT) {
      cout << "v.x: " << v.x << endl;
      cout << "v.y: " << v.y << endl;
   }
}

void Figure::move(vector<Figure*>& other, int deltaTicks) {
   xMovement(other, deltaTicks);
   yMovement(other, deltaTicks);

   setCamera();

   if (DEBUG_MOVE) {
      cout << "p.x: " << p.x << endl;
      cout << "p.y: " << p.y << endl;
   }
}

void Figure::show(SDL_Rect* otherCamera) {
   if (numClips > 0) {
      if (v.x < 0) {
         status = LEFT;
         animationFrame += AFVALUE;
      }
      else if (v.x > 0) {
         status = RIGHT;
         animationFrame += AFVALUE;
      }
      else
         animationFrame = 0;

      if (animationFrame >= numClips)
         animationFrame = 0;

      if (leader) {
         if (status == LEFT)
            applySurface((int) p.x - camera->x, (int) p.y - camera->y, *image,
                  screen, &cl[static_cast<int>(animationFrame)]);
         else if (status == RIGHT)
            applySurface((int) p.x - camera->x, (int) p.y - camera->y, *image,
                  screen, &cr[static_cast<int>(animationFrame)]);

         if (particleEffects)
            showParticles(camera);
      }
      else {
         if (status == LEFT)
            applySurface((int) p.x - otherCamera->x, (int) p.y - otherCamera->y,
                  *image, screen, &cl[static_cast<int>(animationFrame)]);
         else if (status == RIGHT)
            applySurface((int) p.x - otherCamera->x, (int) p.y - otherCamera->y,
                  *image, screen, &cr[static_cast<int>(animationFrame)]);

         if (particleEffects)
            showParticles(otherCamera);
      }
   }
}

void Figure::showParticles(SDL_Rect* camera) {
   for (int i = 0; i < TOTAL_PARTICLES; i++) {
      if (particles[i]->isDead()) {
         delete particles[i];
         particles[i] = new Particle(p.x, p.y, dim, p1, p2, p3, p4, screen);
      }

      particles[i]->show(camera);
   }
}

SDL_Rect* Figure::getCameraClip() {
   return camera;
}

/*
 * Collision resolver -
 * Uses a int given in the figure, and int given in other
 * object that is involved with the collision
 * eg. player has resolve 1, and goal has resolve 2
 * so when the objects collide, collision 1,2 occurs
 * (and any special properties of that collision happen)
 * @param int  resolve constant of other involed figure
 * @param float time step given in mili seconds
 *
 * TODO: There has to be a better way to do this
 * Kevin - precondition here: Figure* other is valid and not NULL. Will keep thinking of a
 * better way to do the above. We'll see a pattern when this becomes bigger. Right now I'm
 * thinking of a multi-dimensional list-like data structure (vector, array) perhaps?
 */
void Figure::resolveCollision(Figure* other, double timeStep, Component dir) {
   if (dir == XHAT)
      p.x -= v.x * timeStep / 1000.0;
   else if (dir == YHAT) {
      p.y -= v.y * timeStep / 1000.0;
      if (gravityEnabled)
         v.y = 0;
   }
}

string Figure::getClassName() {
   return className;
}

bool Figure::operator==(const Figure& other) {
   return this->p.x == other.p.x && this->p.y == other.p.y;
}

bool Figure::operator!=(const Figure& other) {
   return this->p.x != other.p.x || this->p.y != other.p.y;
}

Figure::~Figure() {
   if (camera != NULL)
      delete camera;

   for (int i = 0; i < TOTAL_PARTICLES; i++) {
      if (particles[i] != NULL)
         delete particles[i];
   }
}

RectFigure::RectFigure() {
   camera = NULL;

   for (int i = 0; i < TOTAL_PARTICLES; i++) {
      particles[i] = NULL;
   }

   className = "RectFigure";
}

RectFigure::RectFigure(int x, int y, Surface& image, SDL_Surface* screen,
      Gravity gravityEnabled, int levelWidth, int levelHeight, bool leader,
      double speed, double gravity, double jumpStrength, int numClips,
      Surface* p1, Surface* p2, Surface* p3, Surface* p4) :
      Figure(x, y, image, screen, gravityEnabled, leader, speed, gravity,
            jumpStrength, numClips, levelWidth, levelHeight, p1, p2, p3, p4) {
   className = "RectFigure";

   if (DEBUG_PRIVATES)
      debug();
}

bool RectFigure::checkCollision(RectFigure* r) {
   int left1 = p.x;
   int right1 = p.x + dim.w;
   int top1 = p.y;
   int bot1 = p.y + dim.h;

   int left2 = r->p.x;
   int right2 = r->p.x + r->dim.w;
   int top2 = r->p.y;
   int bot2 = r->p.y + r->dim.h;

   if (!(bot1 < top2 || top1 > bot2 || right1 < left2 || left1 > right2))
      return true;
   return false;
}

bool RectFigure::checkCollision(CircFigure* c) {
   int cx, cy;

   if (c->getX() < p.x)
      cx = p.x;
   else if (c->getX() > p.x + dim.w)
      cx = p.x + dim.w;
   else
      cx = c->getX();

   if (c->getY() < p.y)
      cy = p.y;
   else if (c->getY() > p.y + dim.h)
      cy = p.y + dim.h;
   else
      cy = c->getY();

   Point closestPoint = { cx, cy };
   Point circle = { c->getX(), c->getY() };
   if (dist(closestPoint, circle) < c->getR())
      return true;

   return false;
}

int CircFigure::determineGravity() {
   if (gravityEnabled && !u) {
      if (p.y < lh - r)
         v.y += gravity + abs(v.y * 0.01);
      else
         v.y = 0;
   }

   return v.y;
}

void CircFigure::checkIfInAir(vector<Figure*>& other) {
   int count = 0;

   inAir = true;
   p.y += 3;

   //if on floor or standing on another Figure
   if ((v.y == 0 && p.y >= lh - r) || (isCollided(other, count)))
      inAir = false;
   p.y -= 3;

   //Figure is at the peak of trajectory
   if (p.y < lh - r && v.y <= 0.5 && v.y >= 0.5)
      inAir = true;
}

void CircFigure::xMovement(vector<Figure*>& other, int deltaTicks) {
   int count = 0;

   p.x += v.x * deltaTicks / 1000.0;

   if (isCollided(other, count))
      p.x -= gravity / 2 * v.x * deltaTicks / 1000.0;
   else if (p.x > lw - r)
      p.x = lw - r;
   else if (p.x < r)
      p.x = r;
}

void CircFigure::yMovement(vector<Figure*>& other, int deltaTicks) {
   int count = 0;

   //gravity considerations
   determineGravity();

   //jump action
   determineJump();

   //check if inAir is true
   checkIfInAir(other);

   p.y += v.y * deltaTicks / 1000.0;

   if (isCollided(other, count)) {
      if (v.y * deltaTicks / 1000.0 < 0)
         p.y -= floor(v.y * deltaTicks / 1000.0);
      else
         p.y -= ceil(v.y * deltaTicks / 1000.0);

      if (gravityEnabled)
         v.y = 0;
   }
   else if (p.y > lh - r)
      p.y = lh - r;
}

CircFigure::CircFigure() {
   camera = NULL;

   for (int i = 0; i < TOTAL_PARTICLES; i++) {
      particles[i] = NULL;
   }

   className = "CircFigure";
}

CircFigure::CircFigure(int x, int y, Surface& image, SDL_Surface* screen,
      Gravity gravityEnabled, int levelWidth, int levelHeight, bool leader,
      double speed, double gravity, double jumpStrength, int numClips,
      Surface* p1, Surface* p2, Surface* p3, Surface* p4) :
      Figure(x, y, image, screen, gravityEnabled, leader, speed, gravity,
            jumpStrength, numClips, levelWidth, levelHeight, p1, p2, p3, p4) {
   className = "CircFigure";

   if (dim.w > dim.h)
      r = dim.w / 2;
   else
      r = dim.h / 2;

   if (DEBUG_PRIVATES)
      debug();
}

void CircFigure::setFigure(int x, int y, Surface& image, SDL_Surface* screen,
      Gravity gravityEnabled, int levelWidth, int levelHeight, bool leader,
      double speed, double gravity, double jumpStrength, int numClips,
      Surface* p1, Surface* p2, Surface* p3, Surface* p4) {
   Figure::setFigure(x, y, image, screen, gravityEnabled, levelWidth,
         levelHeight, leader, speed, gravity, jumpStrength, numClips, p1, p2,
         p3, p4);

   if (dim.w > dim.h)
      r = dim.w / 2;
   else
      r = dim.h / 2;

   if (DEBUG_PRIVATES)
      debug();
}

int CircFigure::getR() {
   return r;
}

void CircFigure::show(SDL_Rect* otherCamera) {
   if (numClips > 0) {
      if (v.x < 0) {
         status = LEFT;
         animationFrame += AFVALUE;
      }
      else if (v.x > 0) {
         status = RIGHT;
         animationFrame += AFVALUE;
      }
      else
         animationFrame = 0;

      if (animationFrame >= numClips)
         animationFrame = 0;

      if (leader) {
         if (status == LEFT)
            applySurface((int) p.x - r - camera->x, (int) p.y - r - camera->y,
                  *image, screen, &cl[static_cast<int>(animationFrame)]);
         else if (status == RIGHT)
            applySurface((int) p.x - r - camera->x, (int) p.y - r - camera->y,
                  *image, screen, &cr[static_cast<int>(animationFrame)]);

         if (particleEffects)
            showParticles(camera);
      }
      else {
         if (status == LEFT)
            applySurface((int) p.x - r - otherCamera->x,
                  (int) p.y - r - otherCamera->y, *image, screen,
                  &cl[static_cast<int>(animationFrame)]);
         else if (status == RIGHT)
            applySurface((int) p.x - r - otherCamera->x,
                  (int) p.y - r - otherCamera->y, *image, screen,
                  &cr[static_cast<int>(animationFrame)]);

         if (particleEffects)
            showParticles(otherCamera);
      }
   }
}

void CircFigure::showParticles(SDL_Rect* camera) {
   Position posOff;
   posOff.x = p.x - r;
   posOff.y = p.y - r;

   for (int i = 0; i < TOTAL_PARTICLES; i++) {
      if (particles[i]->isDead()) {
         delete particles[i];
         particles[i] = new Particle(posOff.x, posOff.y, dim, p1, p2, p3, p4,
               screen);
      }

      particles[i]->show(camera);
   }
}

bool CircFigure::checkCollision(RectFigure* r) {
   int cx, cy;

   if (p.x < r->getX())
      cx = r->getX();
   else if (p.x > r->getX() + r->getWidth())
      cx = r->getX() + r->getWidth();
   else
      cx = p.x;

   if (p.y < r->getY())
      cy = r->getY();
   else if (p.y > r->getY() + r->getHeight())
      cy = r->getY() + r->getHeight();
   else
      cy = p.y;

   Point p1 = { p.x, p.y };
   Point p2 = { cx, cy };
   if (dist(p1, p2) < this->r)
      return true;

   return false;
}

bool CircFigure::checkCollision(CircFigure* c) {
   Point thisCenter = { p.x, p.y };
   Point otherCenter = { c->p.x, c->p.y };

   if (dist(thisCenter, otherCenter) < this->r + c->r) {
      return true;
   }

   return false;
}

