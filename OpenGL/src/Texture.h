#ifndef TEXTURE_H
#define TEXTURE_H
#include<iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Renderer.h"

class Texture {
	unsigned int m_texture;
	std::string m_filePath;
	
	unsigned char* m_LocalBuffer;
	int m_Height, m_Width, m_BPP;
public:
	Texture(const std::string&);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void UnBind() const;
	inline int getHeight() { return m_Height; }
	inline int getWidth() { return m_Height; }

};



#endif
