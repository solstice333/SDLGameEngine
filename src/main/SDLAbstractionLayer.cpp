#include "Exception.h"
#include "SDLAbstractionLayer.h"
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

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

Particle::Particle(double x, double y, SDL_Rect dim, Surface* p1, Surface* p2,
      Surface* p3, Surface* p4, SDL_Surface* screen) :
      p1(p1), p2(p2), p3(p3), p4(p4), screen(screen) {
   //set offsets
   this->p.x = x + static_cast<double>(randRange(-5, dim.w));
   this->p.y = y + static_cast<double>(randRange(-5, dim.h));

   //init animation frame
   frame = randRange(0, 4);

   //set type
   switch (randRange(0, 2)) {
   case 0:
      type = this->p1;
      break;
   case 1:
      type = this->p2;
      break;
   case 2:
      type = this->p3;
      break;
   default:
      break;
   }
}

void Particle::show(SDL_Rect* camera) {
   if (type != NULL)
      applySurface(p.x - camera->x, p.y - camera->y, *type, screen);

   if (frame % 2 == 0 && p4 != NULL)
      applySurface(p.x - camera->x, p.y - camera->y, *p4, screen);

   frame++;
}

bool Particle::isDead() {
   if (frame > randRange(PARTICLE_DRAG_MIN, PARTICLE_DRAG_MAX))
      return true;
   return false;
}

StringInput::StringInput(string ttfFile, int fontSize, Surface::Color fontColor,
      SDL_Surface* screen) :
      str(""), ttfFile(ttfFile), fontSize(fontSize), fontColor(fontColor), screen(
            screen), text(ttfFile, fontSize, fontColor, "") {
   SDL_EnableUNICODE(SDL_ENABLE);
}

void StringInput::handleInput(SDL_Event& event) {
   if (event.type == SDL_KEYDOWN) {
      string temp = str;

      if (str.length() <= 16) {
         if (event.key.keysym.unicode == (Uint16) ' ')
            str += (char) event.key.keysym.unicode;
         else if ((event.key.keysym.unicode >= (Uint16) '0'
               && event.key.keysym.unicode <= (Uint16) '9')
               || (event.key.keysym.unicode >= (Uint16) 'A'
                     && event.key.keysym.unicode <= (Uint16) 'Z')
               || (event.key.keysym.unicode >= (Uint16) 'a'
                     && event.key.keysym.unicode <= (Uint16) 'z'))
            str += (char) event.key.keysym.unicode;
      }

      if (event.key.keysym.sym == SDLK_BACKSPACE && str.length() > 0) {
         str.erase(str.length() - 1);
      }

      if (str != temp)
         text.setSDL_Surface(ttfFile, fontSize, fontColor, str);
   }
}

void StringInput::showCentered() {
   applySurfaceMiddle(text, screen);
}

StringInput::~StringInput() {
   SDL_EnableUNICODE(SDL_DISABLE);
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

int randRange(int low, int high) {
   return rand() % (high + 1 - low) + low;
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
