//======================================================================
//File: Skybox.h
//Author: Jake Ellenberg
//Created: 2/14/2015
//Purpose: Creates a sky box
//======================================================================
//======================================================================
#ifndef SKYBOX_H
#define SKYBOX_H
//======================================================================
#include <Windows.h>
#include "GL\glew.h"
#include <vector>
//======================================================================
class Skybox
{
public:
	Skybox();
	~Skybox();
	void Initialize();
	void loadImage(std::string filePath, GLuint* texture);
	GLuint loadCubemap(std::vector<std::string> faces);

	void Render();
private:
	GLuint m_TextureFront;
	GLuint m_TextureBack;
	GLuint m_TextureTop;
	GLuint m_TextureBot;
	GLuint m_TextureLeft;
	GLuint m_TextureRight;

};
//======================================================================
#endif