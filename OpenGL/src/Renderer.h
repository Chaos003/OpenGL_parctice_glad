#ifndef RENDERER_H
#define RENDERER_H
#include "glad/glad.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCALL(#x,__FILE__,__LINE__))


void GLClearError();

bool GLLogCALL(const char* function, const char* file, int line);




#endif // 

