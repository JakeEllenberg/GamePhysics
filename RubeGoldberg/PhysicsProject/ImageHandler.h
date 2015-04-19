//=============================================================================
//                              Image Handler
//
// Written by Robert Bethune
//
// Manages Textures
//=============================================================================
#ifndef IMAGE_HANDLER_H
#define IMAGE_HANDLER_H
//=============================================================================
#include <map>
#include <Windows.h>
#include "GL\Glut.h"
#include <string>
//=============================================================================
class ImageHandler
{
public:
	ImageHandler();
	static ImageHandler* GetInstance();
	~ImageHandler();
	GLuint* AddImage(std::string filePath, std::string name);
	GLuint* GetImage(std::string name);


private:
	std::map<std::string, GLuint*> m_Images;
	static ImageHandler* m_ImageHandler;

};
//=============================================================================
#endif // IMAGE_HANDLER_H