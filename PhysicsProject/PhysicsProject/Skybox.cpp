//======================================================================
//File: Skybox.h
//Author: Jake Ellenberg
//Created: 2/14/2015
//Purpose: Creates a sky box
//======================================================================
#include "Skybox.h"
#include <SOIL.h>

Skybox::Skybox()
{
}


Skybox::~Skybox()
{
}
void Skybox::Initialize()
{
	loadImage("Stars/Stars_right1.jpg", &m_TextureRight);
	loadImage("Stars/Stars_left2.jpg", &m_TextureLeft);
	loadImage("Stars/Stars_top3.jpg", &m_TextureTop);
	loadImage("Stars/Stars_front5.jpg", &m_TextureFront);
	loadImage("Stars/Stars_bottom4.jpg", &m_TextureBot);
	loadImage("Stars/Stars_back6.jpg", &m_TextureBack);
}

//--------------------------------------------------------------------------------
void Skybox::loadImage(std::string filePath, GLuint* texture)
{
	glEnable(GL_TEXTURE_2D);
	int width;
	int height;

	glGenTextures(1, texture);
	glBindTexture(GL_TEXTURE_2D, *texture);

	unsigned char* image = SOIL_load_image(filePath.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
}

//--------------------------------------------------------------------------------
void Skybox::Render()
{
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);

	int width = 50;
	int height = 50;
	int length = 50;

	glBindTexture(GL_TEXTURE_2D, m_TextureTop);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(1.0f, 0.0f);	glVertex3f(width, height, -length);	// Top Right Of The Quad (Top)
	glTexCoord2d(1.0f, 1.0f);	glVertex3f(-width, height, -length);	// Top Left Of The Quad (Top)
	glTexCoord2d(0.0, 1.0f);	glVertex3f(-width, height, length);	// Bottom Left Of The Quad (Top)
	glTexCoord2d(0.0, 0.0f);	glVertex3f(width, height, length);	// Bottom Right Of The Quad (Top)
	glEnd();

	glBindTexture(GL_TEXTURE_2D, m_TextureFront);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2d(0.0f, 0.0f);	glVertex3f(width, height, length);	// Top Right Of The Quad (Front)
	glTexCoord2d(1.0f, 0.0f);	glVertex3f(-width, height, length);	// Top Left Of The Quad (Front)
	glTexCoord2d(1.0f, 1.0f);	glVertex3f(-width, -height, length);	// Bottom Left Of The Quad (Front) 
	glTexCoord2d(0.0f, 1.0f);	glVertex3f(width, -height, length);	// Bottom Right Of The Quad (Front)
	glEnd();

	glBindTexture(GL_TEXTURE_2D, m_TextureBack);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2d(0.0f, 1.0f);	glVertex3f(width, -height, -length);	// Bottom Left Of The Quad (Back)
	glTexCoord2d(1.0f, 1.0f);	glVertex3f(-width, -height, -length);	// Bottom Right Of The Quad (Back)
	glTexCoord2d(1.0f, 0.0f);	glVertex3f(-width, height, -length);	// Top Right Of The Quad (Back)
	glTexCoord2d(0.0f, 0.0f);	glVertex3f(width, height, -length);	// Top Left Of The Quad (Back)
	glEnd();

	glBindTexture(GL_TEXTURE_2D, m_TextureLeft);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2d(1.0f, 0.0f);	glVertex3f(-width, height, -length);	// Top Right Of The Quad (Left)
	glTexCoord2d(1.0f, 1.0f);	glVertex3f(-width, -height, -length);	// Top Left Of The Quad (Left)
	glTexCoord2d(0.0f, 1.0f);	glVertex3f(-width, -height, length);	// Bottom Left Of The Quad (Left)
	glTexCoord2d(0.0f, 0.0f);	glVertex3f(-width, height, length);	// Bottom Right Of The Quad (Left)
	glEnd();

	glBindTexture(GL_TEXTURE_2D, m_TextureRight);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2d(0.0f, 0.0f);	glVertex3f(width, height, -length);	// Top Right Of The Quad (Right)
	glTexCoord2d(1.0f, 0.0f);	glVertex3f(width, height, length);	// Top Left Of The Quad (Right)
	glTexCoord2d(1.0f, 1.0f);	glVertex3f(width, -height, length);	// Bottom Left Of The Quad (Right)
	glTexCoord2d(0.0f, 1.0f);	glVertex3f(width, -height, -length);	// Bottom Right Of The Quad (Right)
	glEnd();

	glBindTexture(GL_TEXTURE_2D, m_TextureBot);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	// Bottom Face
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-width, -height, -length);  // Top Right Of The Texture and Quad
	glTexCoord2f(0.0f, 1.0f); glVertex3f(width, -height, -length);  // Top Left Of The Texture and Quad
	glTexCoord2f(0.0f, 0.0f); glVertex3f(width, -height, length);  // Bottom Left Of The Texture and Quad
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-width, -height, length);  // Bottom Right Of The Texture and Quad
	glEnd();

	glEnable(GL_LIGHTING);
}