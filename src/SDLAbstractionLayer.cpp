#include "Exception.h"
#include "SDLAbstractionLayer.h"
#include <iostream>
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

int Figure::calculateGravity() {
   if (p.y < screen->h - height)
      v.y += gravity + abs(v.y * 0.05);
   else
      v.y = 0;

   return v.y;
}

Figure::Figure() {
}

Figure::Figure(int x, int y, Surface& left, Surface& right, SDL_Surface* screen,
      double speed, Gravity gravityEnabled, double gravity, double jumpStrength) :
      width((left.getSDL_Surface()->w + right.getSDL_Surface()->w) / 2), height(
            (left.getSDL_Surface()->h + right.getSDL_Surface()->h) / 2), gravity(
            gravity), speed(speed), jumpStrength(jumpStrength), l(false), r(
            false), u(false), d(false), screen(screen), left(&left), right(
            &right) {
   p.x = x, p.y = y;
   v.x = 0, v.y = 0;
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

void Figure::setFigure(int x, int y, Surface& left, Surface& right,
      SDL_Surface* screen, double speed, Gravity gravityEnabled, double gravity,
      double jumpStrength) {
   width = (left.getSDL_Surface()->w + right.getSDL_Surface()->w) / 2;
   height = (left.getSDL_Surface()->h + right.getSDL_Surface()->h) / 2;
   this->gravity = gravity;
   this->speed = speed;
   this->jumpStrength = jumpStrength;
   l = r = u = d = false;
   this->screen = screen;
   this->left = &left;
   this->right = &right;

   p.x = x, p.y = y;
   v.x = 0, v.y = 0;
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

int Figure::getWidth() {
   return width;
}

int Figure::getHeight() {
   return height;
}

void Figure::handleInput(SDL_Event& event) {
   if (event.type == SDL_KEYDOWN) {
      switch (event.key.keysym.sym) {
      case SDLK_UP:
         v.y -= height * speed / 100 * jumpStrength;
         u = true;
         break;
      case SDLK_DOWN:
         v.y += height * speed / 100;
         d = true;
         break;
      case SDLK_LEFT:
         v.x -= width * speed / 100;
         l = true;
         break;
      case SDLK_RIGHT:
         v.x += width * speed / 100;
         r = true;
         break;
      default:
         break;
      }
   }

   else if (event.type == SDL_KEYUP) {
      switch (event.key.keysym.sym) {
      case SDLK_UP:
         if (gravityEnabled)
            v.y += height * speed / 100 * (jumpStrength - (jumpStrength - 1));
         else
            v.y += height * speed / 100 * jumpStrength;
         u = false;
         break;
      case SDLK_DOWN:
         v.y -= height * speed / 100;
         d = false;
         break;
      case SDLK_LEFT:
         v.x += width * speed / 100;
         l = false;
         break;
      case SDLK_RIGHT:
         v.x -= width * speed / 100;
         r = false;
         break;
      default:
         break;
      }
   }
}

void Figure::move() {
   p.x += v.x;
   if (p.x > screen->w - width)
      p.x = screen->w - width;
   else if (p.x < 0)
      p.x = 0;

   if (gravityEnabled) {
      if (!u)
         calculateGravity();
   }

   p.y += v.y;
   if (p.y > screen->h - height)
      p.y = screen->h - height;
   else if (p.y < 0)
      p.y = 0;
}

void Figure::show(SDL_Rect* clip) {
   if (l)
      current = left;
   else if (r)
      current = right;

   applySurface(p.x, p.y, *current, screen, clip);

   if (DEBUG) {
      if (l || r) {
         cout << "p.x: " << p.x << endl;
         cout << "v.x: " << v.x << endl;
      }
      if (u || d) {
         cout << "p.y: " << p.y << endl;
         cout << "v.y: " << v.y << endl;
      }
   }
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
      c = setRGBColor(0, 255, 0);
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

void delayFrame(Timer timer, int fps) {
   if (timer.getTicks() < 1000 / fps)
      SDL_Delay(1000 / fps - timer.getTicks());
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
