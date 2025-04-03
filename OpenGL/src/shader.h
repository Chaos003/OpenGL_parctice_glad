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
            << "������ [ Error function ] " << function << "\n"
            << "������ [ Error file ] " << file << "\n"
            << "������ [ Error line ] " << line << std::endl;
        return false;
    }
    return true;
}



class Shader 
{
public:
    unsigned int ID;//shaderprogram ��ID

    Shader(const char* vertexPath, const char* fragmentPah) {

        //1����һ����ȡ��Ӧ����ɫ������
        std::string vertexCode;
        std::string fragmentCode;

        std::ifstream vertexShaderFile;
        std::ifstream fragmentShaderFile;

        //failbit�����������ʧ��ʱ�ı�־�������ȡһ����Чֵ����������ȡ��һ���ַ��������У�
        //����Ȼ��ʾ������ʧ��״̬����������Ȼ����ʹ��
        //badbit�������˲��ɻָ��Ĵ��󣬱����ȡ�����з�����Ӳ������������Ѿ��𻵣�
        //baibit�������Ѿ����벻�ɻָ��Ĵ���״̬���������޷�����ʹ��
        vertexShaderFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);
        try {
            vertexShaderFile.open(vertexPath);
            fragmentShaderFile.open(fragmentPah);
            
            //������Ӧ���ļ���
            std::stringstream vertexShaderStream, fragmentShaderStream;
            //���ļ������������
            vertexShaderStream << vertexShaderFile.rdbuf();
            fragmentShaderStream << fragmentShaderFile.rdbuf();

            //�رն�Ӧ���ļ���ͨ��
            vertexShaderFile.close();
            fragmentShaderFile.close();
            //��ת�����ַ���string
            vertexCode = vertexShaderStream.str();
            fragmentCode = fragmentShaderStream.str();
        }
        catch (std::ifstream::failure& e) {
            //��GLGS��ɫ���ļ�ʧ��
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ:" << e.what() << std::endl;
        }
        //��Ϊ�������string�ַ�������Ҫ�Ĳ�����const char*������Ҫcopy�ַ�����һ����Ӧ��ʽ���ַ���ָ�뷽�㴫��
        const char* vertexShaderSourceCode = vertexCode.c_str();
        const char* fragmentShaderSourceCode = fragmentCode.c_str();

        //2��������ɫ������shaders
        //unsigned int vertex, fragment; 
        ID = CreateShaderProgram(vertexShaderSourceCode, fragmentShaderSourceCode);
    }
    //ʹ����ɫ������
    void use() {
        glUseProgram(ID);
    }

    //uniform�Ķ���setter����
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
        unsigned int id = glCreateShader(Type);//��Ӧ����İ���ɫ������
        const char* src = source.c_str();
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        return id;
    }
    //������ɫ���������Ӹ�����ɫ��
    static unsigned int CreateShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource) {
        //��ɫ������
        unsigned int shaderProgram = glCreateProgram();
        //������ɫ��
        unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
        //Ƭ����ɫ��
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
