#include "Texture2D.h"

Texture2D::Texture2D(const string &file, GLenum format)
{
	//Generate Texture
	GLErrorCall(glGenTextures(1, &id));
	GLErrorCall(glBindTexture(GL_TEXTURE_2D, id));
	WrapTexture();
	FilterTexture();
	LoadImage(file, format);
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
	GLErrorCall(glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GLErrorCall(glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
}

void Texture2D::FilterTexture()
{
	//Texture Filtering
	GLErrorCall(glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	GLErrorCall(glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
}

void Texture2D::LoadImage(const string &file, GLenum format)
{
	//Load Image
	int width, height, nrChannels;
	unsigned char *data = stbi_load(file.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		GLErrorCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data));
		GLErrorCall(glGenerateMipmap(GL_TEXTURE_2D));
	}
	else
	{
		cout << "ERROR: " << "Could not load texture" << endl;
	}
	stbi_image_free(data);
}
