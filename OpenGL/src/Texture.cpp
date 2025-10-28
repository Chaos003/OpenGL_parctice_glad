#include "Texture.h"

Texture::Texture(const std::string& filepath):m_filePath(filepath) {

    m_LocalBuffer = stbi_load("source/123123.jpg", &m_Width, &m_Height, &m_BPP, 0);

    if (m_LocalBuffer) {

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_LocalBuffer);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(m_LocalBuffer);
}

Texture::~Texture() {

}

void Texture::Bind(unsigned int slot = 0) const{

}
void Texture::UnBind() const{

}

