#include "Exception.h"

const char* LoadImageException::what() const throw () {
   return "Error: Image failed to load. \n";
}

const char* ConversionException::what() const throw () {
   return "Error: Conversion failed. \n";
}

const char* InitException::what() const throw () {
   return "Error: Failed to initialize. \n";
}

const char* SetVideoModeException::what() const throw () {
   return "Error: Failed to set video mode. \n";
}

const char* FlipException::what() const throw () {
   return "Error: Failed to swap video buffers. \n";
}

const char* InvalidColorException::what() const throw () {
   return "Error: Invalid ColorKey enum. \n";
}

const char* LoadTextException::what() const throw () {
   return "Error: Font failed to load. \n";
}

const char* LoadMusicException::what() const throw () {
   return "Error: Music failed to load. \n";
}

const char* LoadChunkException::what() const throw () {
   return "Error: Chunk failed to load. \n";
}

const char* SoundException::what() const throw () {
   return "Error: Music or chunk failed to play \n";
}

const char* GravityException::what() const throw () {
   return "Error: Invalid Gravity enum \n";
}

const char* FigureException::what() const throw () {
   return "Error: Invalid Figure \n";
}

const char* LoadSavedGameException::what() const throw() {
   return "Error: Failed to load saved game \n";
}

const char* WindowException::what() const throw() {
   return "Error: Window error \n";
}

const char* InvalidMarkerException::what() const throw() {
   return "Error: Invalid marker enum \n";
}
