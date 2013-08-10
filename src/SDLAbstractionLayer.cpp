#include "Exception.h"
#include "SDLAbstractionLayer.h"
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

const bool DEBUG = true;

Surface::Surface() :
      s(NULL) {
}

Surface::Surface(SDL_Surface* sdls, Color ck) {
   SDL_Surface* optImg = optimizeImage(sdls);
   setColorKey(ck, optImg);
   s = optImg;
}

Surface::Surface(string filepath, Color ck) :
      s(loadImage(filepath, ck)) {
}

Surface::Surface(string ttfFile, int fontSize, Color textColor, string msg) :
      s(loadText(ttfFile, fontSize, textColor, msg)) {
}

void Surface::setSDL_Surface(SDL_Surface* surface) {
   s = surface;
}

void Surface::setSDL_Surface(string filepath, Color ck) {
   s = loadImage(filepath, ck);
}

void Surface::setSDL_Surface(string ttfFile, int fontSize,
      Surface::Color textColor, string msg) {
   s = loadText(ttfFile, fontSize, textColor, msg);
}

SDL_Surface * Surface::getSDL_Surface() {
   return s;
}

Surface::~Surface() {
   SDL_FreeSurface(s);
}

Music::Music() :
      m(NULL) {
}

Music::Music(string music) :
      m(loadMusic(music)) {
}

void Music::setMusic(string music) {
   m = loadMusic(music);
}

Mix_Music* Music::getMix_Music() {
   return m;
}

Music::~Music() {
   Mix_FreeMusic(m);
}

Chunk::Chunk() :
      c(NULL) {
}

Chunk::Chunk(string chunk) :
      c(loadChunk(chunk)) {
}

void Chunk::setChunk(string chunk) {
   c = loadChunk(chunk);
}

Mix_Chunk* Chunk::getMix_Chunk() {
   return c;
}

Chunk::~Chunk() {
   Mix_FreeChunk(c);
}

Timer::Timer() {
   startTicks = 0;
   pausedTicks = 0;
   paused = false;
   started = false;
}

void Timer::start() {
   started = true;
   paused = false;
   startTicks = SDL_GetTicks();
}

void Timer::stop() {
   started = false;
   paused = false;
}

void Timer::pause() {
   if (started && !paused) {
      paused = true;
      pausedTicks = SDL_GetTicks() - startTicks;
   }
}

void Timer::unpause() {
   if (paused) {
      paused = false;
      startTicks = SDL_GetTicks() - pausedTicks;
      pausedTicks = 0;
   }
}

int Timer::getTicks() {
   if (started) {
      if (paused)
         return pausedTicks;
      else
         return SDL_GetTicks() - startTicks;
   }

   return 0;
}

bool Timer::isStarted() {
   return started;
}

bool Timer::isPaused() {
   return paused;
}

int Timer::delayFrame(int fps) {
   int delay;

   if (this->getTicks() < 1000 / fps)
      SDL_Delay(delay = 1000 / fps - this->getTicks());

   return delay;
}

int Figure::calculateGravity() {
   if (posDim.y < screen->h - posDim.h)
      v.y += gravity + abs(v.y * 0.01);
   else
      v.y = 0;

   return v.y;
}

void Figure::initialize(int x, int y, double gravity, double speed,
      double jumpStrength, SDL_Surface* screen, Gravity gravityEnabled) {
   posDim.x = x;
   posDim.y = y;
   frame = 0;

   this->gravity = gravity;
   this->speed = speed;
   if (jumpStrength < 1)
      this->jumpStrength = 1;

   this->jumpStrength = jumpStrength;

   l = r = u = d = false;
   this->screen = screen;

   v.x = v.y = 0;
   current = this->right;

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
}

void Figure::xMovement(vector<Figure*>& other) {
   int count = 0;

   posDim.x += v.x;

   if (isCollided(other, count))
      posDim.x -= v.x;
   else if (posDim.x > screen->w - posDim.w)
      posDim.x = screen->w - posDim.w;
   else if (posDim.x < 0)
      posDim.x = 0;
}

void Figure::yMovement(vector<Figure*>& other) {
   if (gravityEnabled && !u)
      calculateGravity();

   int count = 0;

   posDim.y += v.y;
   if (isCollided(other, count)) {
      posDim.y -= v.y;

      if (gravityEnabled)
         v.y = 0;
   }
   else if (posDim.y > screen->h - posDim.h)
      posDim.y = screen->h - posDim.h;
   else if (posDim.y < 0)
      posDim.y = 0;

   if (gravityEnabled && u && frame < 3) {
      v.y -= posDim.h * speed / 100 * jumpStrength;
      frame++;
   }
   else {
      frame = 0;
      u = false;
   }
}

void Figure::debug() {
   if (l || r) {
      cout << "posDim.x: " << posDim.x << endl;
      cout << "v.x: " << v.x << endl;
   }
   cout << "posDim.y: " << posDim.y << endl;
   cout << "v.y: " << v.y << endl;
}

Figure::Figure() {
}

Figure::Figure(int x, int y, Surface& left, Surface& right, SDL_Surface* screen,
      Gravity gravityEnabled, double speed, int gravity, double jumpStrength) :
      left(&left), right(&right) {

   posDim.w = (left.getSDL_Surface()->w + right.getSDL_Surface()->w) / 2;
   posDim.h = (left.getSDL_Surface()->h + right.getSDL_Surface()->h) / 2;

   initialize(x, y, gravity, speed, jumpStrength, screen, gravityEnabled);
}

Figure::Figure(int x, int y, Surface& image, SDL_Surface* screen,
      Gravity gravityEnabled, double speed, int gravity, double jumpStrength) :
      left(&image), right(&image) {

   posDim.w = image.getSDL_Surface()->w;
   posDim.h = image.getSDL_Surface()->h;

   initialize(x, y, gravity, speed, jumpStrength, screen, gravityEnabled);
}

void Figure::setFigure(int x, int y, Surface& left, Surface& right,
      SDL_Surface* screen, Gravity gravityEnabled, double speed, int gravity,
      double jumpStrength) {

   posDim.w = (left.getSDL_Surface()->w + right.getSDL_Surface()->w) / 2;
   posDim.h = (left.getSDL_Surface()->h + right.getSDL_Surface()->h) / 2;
   this->left = &left;
   this->right = &right;

   initialize(x, y, gravity, speed, jumpStrength, screen, gravityEnabled);
}

void Figure::setFigure(int x, int y, Surface& image, SDL_Surface* screen,
      Gravity gravityEnabled, double speed, int gravity, double jumpStrength) {

   posDim.w = image.getSDL_Surface()->w;
   posDim.h = image.getSDL_Surface()->h;
   this->left = &image;
   this->right = &image;

   initialize(x, y, gravity, speed, jumpStrength, screen, gravityEnabled);
}

int Figure::getWidth() {
   return posDim.w;
}

int Figure::getHeight() {
   return posDim.h;
}

int Figure::getX() {
   return posDim.x;
}

int Figure::getY() {
   return posDim.y;
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
         if (checkCollision(*i))
            return true;
      }

      count++;
   }

   return false;
}

void Figure::handleInput(SDL_Event& event) {
   if (event.type == SDL_KEYDOWN) {
      switch (event.key.keysym.sym) {
      case SDLK_UP:
         if (posDim.y > 0)
            v.y -= posDim.h * speed / 100 * jumpStrength;
         u = true;
         break;
      case SDLK_DOWN:
         v.y += posDim.h * speed / 100;
         d = true;
         break;
      case SDLK_LEFT:
         v.x -= posDim.w * speed / 100;
         l = true;
         break;
      case SDLK_RIGHT:
         v.x += posDim.w * speed / 100;
         r = true;
         break;
      default:
         break;
      }
   }

   else if (event.type == SDL_KEYUP) {
      switch (event.key.keysym.sym) {
      case SDLK_UP:
         if (!gravityEnabled) {
            v.y += posDim.h * speed / 100 * jumpStrength;
            u = false;
         }
         break;
      case SDLK_DOWN:
         v.y -= posDim.h * speed / 100;
         d = false;
         break;
      case SDLK_LEFT:
         v.x += posDim.w * speed / 100;
         l = false;
         break;
      case SDLK_RIGHT:
         v.x -= posDim.w * speed / 100;
         r = false;
         break;
      default:
         break;
      }
   }
}

void Figure::move(vector<Figure*>& other) {
   xMovement(other);
   yMovement(other);

   if (DEBUG)
      debug();
}

void Figure::show(SDL_Rect* clip) {
   if (l)
      current = left;
   else if (r)
      current = right;

   applySurface(posDim.x, posDim.y, *current, screen, clip);
}

string Figure::getClassName() {
   return className;
}

Figure::~Figure() {
}

RectFigure::RectFigure() {
   className = "RectFigure";
}

RectFigure::RectFigure(int x, int y, Surface& left, Surface& right,
      SDL_Surface* screen, Gravity gravityEnabled, double speed, int gravity,
      double jumpStrength) :
      Figure(x, y, left, right, screen, gravityEnabled, speed, gravity,
            jumpStrength) {
   className = "RectFigure";
}

RectFigure::RectFigure(int x, int y, Surface& image, SDL_Surface* screen,
      Gravity gravityEnabled, double speed, int gravity, double jumpStrength) :
      Figure(x, y, image, screen, gravityEnabled, speed, gravity, jumpStrength) {
   className = "RectFigure";
}

bool RectFigure::checkCollision(RectFigure* r) {
   int left1 = posDim.x;
   int right1 = posDim.x + posDim.w;
   int top1 = posDim.y;
   int bot1 = posDim.y + posDim.h;

   int left2 = r->posDim.x;
   int right2 = r->posDim.x + r->posDim.w;
   int top2 = r->posDim.y;
   int bot2 = r->posDim.y + r->posDim.h;

   if (!(bot1 < top2 || top1 > bot2 || right1 < left2 || left1 > right2))
      return true;
   return false;
}

bool RectFigure::checkCollision(CircFigure* c) {
   int cx, cy;

   if (c->getX() < posDim.x)
      cx = posDim.x;
   else if (c->getX() > posDim.x + posDim.w)
      cx = posDim.x + posDim.w;
   else
      cx = c->getX();

   if (c->getY() < posDim.y)
      cy = posDim.y;
   else if (c->getY() > posDim.y + posDim.h)
      cy = posDim.y + posDim.h;
   else
      cy = c->getY();

   Point closestPoint = { cx, cy };
   Point circle = { c->getX(), c->getY() };
   if (dist(closestPoint, circle) < c->getR())
      return true;

   return false;
}

void CircFigure::xMovement(vector<Figure*>& other) {
   int count = 0;

   posDim.x += v.x;

   if (isCollided(other, count))
      posDim.x -= v.x;
   else if (posDim.x > screen->w - r)
      posDim.x = screen->w - r;
   else if (posDim.x < r)
      posDim.x = r;
}

void CircFigure::yMovement(vector<Figure*>& other) {
   if (gravityEnabled && !u)
      calculateGravity();

   int count = 0;

   posDim.y += v.y;
   if (isCollided(other, count)) {
      posDim.y -= v.y;

      if (gravityEnabled)
         v.y = 0;
   }
   else if (posDim.y > screen->h - r)
      posDim.y = screen->h - r;
   else if (posDim.y < r)
      posDim.y = r;

   if (gravityEnabled && u && frame < 3) {
      v.y -= posDim.h * speed / 100 * jumpStrength;
      frame++;
   }
   else {
      frame = 0;
      u = false;
   }
}

CircFigure::CircFigure() {
   className = "CircFigure";
}

CircFigure::CircFigure(int x, int y, Surface& left, Surface& right,
      SDL_Surface* screen, Gravity gravityEnabled, double speed, int gravity,
      double jumpStrength) :
      Figure(x, y, left, right, screen, gravityEnabled, speed, gravity,
            jumpStrength) {
   className = "CircFigure";
   r = (left.getSDL_Surface()->w + right.getSDL_Surface()->w) / 4;
}

CircFigure::CircFigure(int x, int y, Surface& image, SDL_Surface* screen,
      Gravity gravityEnabled, double speed, int gravity, double jumpStrength) :
      Figure(x, y, image, screen, gravityEnabled, speed, gravity, jumpStrength) {
   className = "CircFigure";
   r = image.getSDL_Surface()->w / 2;
}

void CircFigure::setFigure(int x, int y, Surface& left, Surface& right,
      SDL_Surface* screen, Gravity gravityEnabled, double speed, int gravity,
      double jumpStrength) {
   Figure::setFigure(x, y, right, screen, gravityEnabled, speed, gravity,
         jumpStrength);
   r = (left.getSDL_Surface()->w + right.getSDL_Surface()->w) / 4;
}

void CircFigure::setFigure(int x, int y, Surface& image, SDL_Surface* screen,
      Gravity gravityEnabled, double speed, int gravity, double jumpStrength) {
   Figure::setFigure(x, y, image, screen, gravityEnabled, speed, gravity,
         jumpStrength);
   r = image.getSDL_Surface()->w / 2;
}

int CircFigure::getR() {
   return r;
}

void CircFigure::show(SDL_Rect* clip) {
   if (l)
      current = left;
   else if (r)
      current = right;

   applySurface(posDim.x - r, posDim.y - r, *current, screen, clip);
}

bool CircFigure::checkCollision(RectFigure* r) {
   int cx, cy;

   if (posDim.x < r->getX())
      cx = r->getX();
   else if (posDim.x > r->getX() + r->getWidth())
      cx = r->getX() + r->getWidth();
   else
      cx = posDim.x;

   if (posDim.y < r->getY())
      cy = r->getY();
   else if (posDim.y > r->getY() + r->getHeight())
      cy = r->getY() + r->getHeight();
   else
      cy = posDim.y;

   Point p1 = { posDim.x, posDim.y };
   Point p2 = { cx, cy };
   if (dist(p1, p2) < this->r)
      return true;

   return false;
}

bool CircFigure::checkCollision(CircFigure* c) {
   Point thisCenter = { posDim.x, posDim.y };
   Point otherCenter = { c->posDim.x, c->posDim.y };

   if (dist(thisCenter, otherCenter) < this->r + c->r) {
      return true;
   }

   return false;
}

double dist(Point p1, Point p2) {
   return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

SDL_Surface* optimizeImage(SDL_Surface* s) {
   SDL_Surface* optImg = SDL_DisplayFormat(s);
   if (optImg == NULL)
      throw ConversionException();

   SDL_FreeSurface(s);
   return optImg;
}

void setColorKey(Surface::Color ck, SDL_Surface* s) {
   Uint32 colorkey;

   SDL_Color c = parseColor(ck);
   colorkey = SDL_MapRGB(s->format, c.r, c.g, c.b);
   SDL_SetColorKey(s, SDL_SRCCOLORKEY, colorkey);
}

SDL_Color setRGBColor(int r, int g, int b) {
   SDL_Color c = { r, g, b };
   return c;
}

SDL_Color parseColor(Surface::Color color) {
   SDL_Color c;
   switch (color) {
   case Surface::NONE:
      c = setRGBColor(0, 0, 0);
      break;
   case Surface::RED:
      c = setRGBColor(255, 0, 0);
      break;
   case Surface::GREEN:
      c = setRGBColor(0, 255, 0);
      break;
   case Surface::BLUE:
      c = setRGBColor(0, 0, 255);
      break;
   case Surface::CYAN:
      c = setRGBColor(0, 255, 255);
      break;
   case Surface::BLACK:
      c = setRGBColor(0, 0, 0);
      break;
   case Surface::WHITE:
      c = setRGBColor(255, 255, 255);
      break;
   default:
      throw InvalidColorException();
      break;
   }

   return c;
}

SDL_Surface* loadImage(string filename, Surface::Color ck) {
   SDL_Surface* loadImg = IMG_Load(filename.c_str());
   if (loadImg == NULL)
      throw LoadImageException();
   else {
      SDL_Surface* optImg = optimizeImage(loadImg);

      if (ck != Surface::NONE)
         setColorKey(ck, optImg);

      return optImg;
   }
}

SDL_Surface* loadText(string pathToTTF, int size, Surface::Color color,
      string msg) {
   TTF_Font* font = TTF_OpenFont(pathToTTF.c_str(), size);
   if (font == NULL)
      throw LoadTextException();

   SDL_Color c = parseColor(color);
   if (msg == "")
      msg = " ";

   SDL_Surface* text = TTF_RenderText_Solid(font, msg.c_str(), c);
   if (text == NULL)
      throw LoadTextException();

   TTF_CloseFont(font);

   return text;
}

Mix_Music* loadMusic(string music) {
   Mix_Music* m = Mix_LoadMUS(music.c_str());
   if (m == NULL)
      throw LoadMusicException();

   return m;
}

Mix_Chunk* loadChunk(string chunk) {
   Mix_Chunk* c = Mix_LoadWAV(chunk.c_str());
   if (c == NULL)
      throw LoadChunkException();

   return c;
}

void applySurface(int x, int y, Surface& source, SDL_Surface* destination,
      SDL_Rect* clip) {
   SDL_Rect offset;

   offset.x = x;
   offset.y = y;
   //I wonder if you will ever find this comment... =P
   SDL_BlitSurface(source.getSDL_Surface(), clip, destination, &offset);
}

void applySurfaceMiddle(Surface& source, SDL_Surface* destination,
      SDL_Rect* clip) {
   applySurface((destination->w - source.getSDL_Surface()->w) / 2,
         (destination->h - source.getSDL_Surface()->h) / 2, source, destination,
         clip);
}

void flip(SDL_Surface* screen) {
   if (SDL_Flip(screen) < 0)
      throw FlipException();
}

int getVerticalMiddlePosition(Surface& object, SDL_Surface* screen) {
   return (screen->h - object.getSDL_Surface()->h) / 2;
}

int getHorizontalMiddlePosition(Surface& object, SDL_Surface* screen) {
   return (screen->w - object.getSDL_Surface()->w) / 2;
}

bool isHeldDown(SDL_Event& event) {
   while (SDL_PollEvent(&event)) {
      if (event.type == SDL_KEYUP)
         return false;
   }
   return true;
}

void fillScreen(SDL_Surface* screen, Surface::Color color) {
   SDL_Color c = parseColor(color);
   SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, c.r, c.g, c.b));
}

SDL_Surface* init(int w, int h, string title) {
   SDL_Surface* screen = NULL;

   if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
      throw InitException();

   screen = SDL_SetVideoMode(w, h, 32, SDL_SWSURFACE);
   if (screen < 0)
      throw SetVideoModeException();

   if (TTF_Init() < 0)
      throw InitException();

   if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
      throw InitException();

   SDL_WM_SetCaption(title.c_str(), NULL);

   return screen;
}

void cleanUp() {
   Mix_CloseAudio();
   TTF_Quit();
   SDL_Quit();
}
