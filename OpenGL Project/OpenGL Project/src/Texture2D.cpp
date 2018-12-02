#include "Texture2D.h"

Texture2D::Texture2D(const string &file)
{
	//Generate Texture
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	WrapTexture();
	FilterTexture();
	LoadImage(file);
}

Texture2D::~Texture2D()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::Bind()
{
	glBindTexture(GL_TEXTURE_2D, id);
}

void Texture2D::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::WrapTexture()
{
	//Texture Wrapping
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void Texture2D::FilterTexture()
{
	//Texture Filtering
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Texture2D::LoadImage(const string &file)
{
	//Load Image
	int width, height, nrChannels;
	unsigned char *data = stbi_load(file.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		cout << "ERROR: " << "Could not load texture" << endl;
	}
	stbi_image_free(data);
}
