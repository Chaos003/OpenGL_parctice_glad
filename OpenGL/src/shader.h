#ifndef SHADER_H
#define SHADER_H

#include "glad/glad.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>


#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCALL(#x,__FILE__,__LINE__))



static void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCALL(const char* function, const char* file, int line) {
    while (GLenum error = glGetError()) {
        std::cout << "[ OpenGL error ] (" << error << ")\n"
            << "├── [ Error function ] " << function << "\n"
            << "├── [ Error file ] " << file << "\n"
            << "└── [ Error line ] " << line << std::endl;
        return false;
    }
    return true;
}



class Shader 
{
public:
    unsigned int ID;//shaderprogram 的ID

    Shader(const char* vertexPath, const char* fragmentPah) {

        //1、第一步读取对应的着色器代码
        std::string vertexCode;
        std::string fragmentCode;

        std::ifstream vertexShaderFile;
        std::ifstream fragmentShaderFile;

        //failbit代表输入输出失败时的标志，比如读取一个无效值（将整数读取到一个字符串变量中）
        //但虽然表示流进入失败状态，但是流仍然可以使用
        //badbit代表发生了不可恢复的错误，比如读取过程中发生了硬件错误或者流已经损坏，
        //baibit代表流已经进入不可恢复的错误状态，流可能无法继续使用
        vertexShaderFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);
        try {
            vertexShaderFile.open(vertexPath);
            fragmentShaderFile.open(fragmentPah);
            
            //建立对应的文件流
            std::stringstream vertexShaderStream, fragmentShaderStream;
            //将文件缓存进入流中
            vertexShaderStream << vertexShaderFile.rdbuf();
            fragmentShaderStream << fragmentShaderFile.rdbuf();

            //关闭对应的文件流通道
            vertexShaderFile.close();
            fragmentShaderFile.close();
            //将转化成字符串string
            vertexCode = vertexShaderStream.str();
            fragmentCode = fragmentShaderStream.str();
        }
        catch (std::ifstream::failure& e) {
            //打开GLGS着色器文件失败
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ:" << e.what() << std::endl;
        }
        //因为读入的是string字符串，需要的参数是const char*所以需要copy字符串到一个对应格式的字符串指针方便传参
        const char* vertexShaderSourceCode = vertexCode.c_str();
        const char* fragmentShaderSourceCode = fragmentCode.c_str();

        //2、编译着色器程序shaders
        //unsigned int vertex, fragment; 
        ID = CreateShaderProgram(vertexShaderSourceCode, fragmentShaderSourceCode);
    }
    //使用着色器程序
    void use() {
        glUseProgram(ID);
    }

    //uniform的多种setter函数
    void setBool(const std::string& name, bool value) {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }
    void setInt(const std::string& name, int value) {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }
    void setFloat(const std::string& name, float value) {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }




private:
    static unsigned int CompileShader(unsigned int Type, const std::string& source) {
        unsigned int id = glCreateShader(Type);//对应传入的绑定着色器对象
        const char* src = source.c_str();
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        return id;
    }
    //创建着色器程序链接各个着色器
    static unsigned int CreateShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource) {
        //着色器程序
        unsigned int shaderProgram = glCreateProgram();
        //顶点着色器
        unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
        //片段着色器
        unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return shaderProgram;
    }
};

void checkCompileErrors(unsigned int shaderTypeId, std::string type) {
    int result;
    int length;
    if (type != "PROGRAM") {
        glGetShaderiv(shaderTypeId, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE) {
            glGetShaderiv(shaderTypeId, GL_INFO_LOG_LENGTH, &length);
            char* message = (char*)alloca(sizeof(char) * length);
            glGetShaderInfoLog(shaderTypeId, length, &length, message);
            std::cout << "Failed to compile " <<
                ((shaderTypeId == GL_VERTEX_SHADER) ? "vertex" : "fragment" ) <<
                "shader!" << std::endl;
        }
    }
    else {
        glGetShaderiv(shaderTypeId, GL_LINK_STATUS, &result);
        if (result == GL_FALSE) {
            glGetShaderiv(shaderTypeId, GL_INFO_LOG_LENGTH, &length);
            char* message = (char*)alloca(sizeof(char) * length);
            glGetShaderInfoLog(shaderTypeId, length, &length, message);
            std::cout << "Failed to link shaderprogram!" << std::endl;
            std::cout << message << std::endl;
        }
    }
}



#endif 
