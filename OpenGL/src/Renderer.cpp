#include "Renderer.h"

void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCALL(const char* function, const char* file, int line) {
    while (GLenum error = glGetError()) {
        std::cout << "[ OpenGL error ] (" << error << ")\n"
            << "©À©¤©¤ [ Error function ] " << function << "\n"
            << "©À©¤©¤ [ Error file ] " << file << "\n"
            << "©¸©¤©¤ [ Error line ] " << line << std::endl;
        return false;
    }
    return true;
}