
#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
using namespace std;

class LoadImageException : public exception {
public:
   virtual const char* what() const throw();
};

class ConversionException : public exception {
public:
   virtual const char* what() const throw();
};

class InitException : public exception {
public:
   virtual const char* what() const throw();
};

class SetVideoModeException : public exception {
public:
   virtual const char* what() const throw();
};

class FlipException : public exception {
public:
   virtual const char* what() const throw();
};

class InvalidColorException : public exception {
public:
   virtual const char* what() const throw();
};

class LoadTextException : public exception {
public:
   virtual const char* what() const throw();
};

class LoadMusicException : public exception {
public:
   virtual const char* what() const throw();
};

class LoadChunkException : public exception {
public:
   virtual const char* what() const throw();
};

class SoundException : public exception {
public:
   virtual const char* what() const throw();
};

class GravityException : public exception {
public:
   virtual const char* what() const throw();
};

class FigureException : public exception {
public:
   virtual const char* what() const throw();
};

class LoadSavedGameException : public exception {
public:
   virtual const char* what() const throw();
};

class WindowException : public exception {
public:
   virtual const char* what() const throw();
};

class InvalidMarkerException : public exception {
public:
   virtual const char* what() const throw();
};

#endif
