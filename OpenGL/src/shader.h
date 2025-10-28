#ifndef SHADER_H
#define SHADER_H
#include "glad/glad.h"
#include "Renderer.h"
#include <unordered_map>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>


class Shader 
{
private:
    unsigned int ID;//shaderprogram ��ID
    std::string vertexPath;
    std::string fragmentPath;
    std::unordered_map<std::string, unsigned int> UniformLocationCache;

    unsigned int CompileShader(unsigned int Type, const std::string& source);
    //������ɫ���������Ӹ�����ɫ��
    unsigned int CreateShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
    //����program�������ɫ���������Ӵ���
    static void checkCompileErrors(unsigned int shaderTypeId, std::string type);


public:
    Shader(std::string vp, std::string fp);
    ~Shader();

    //ʹ����ɫ������
    void use();
    void UnBind();

    void setUniform4f(const std::string& uniform, float v0, float v1, float v2, float v3);
    unsigned int GetglUniformLocation(const std::string& name);

    //uniform�Ķ���setter����
    void setBool(const std::string& name, bool value);
    void setInt(const std::string& name, int value);
    void setFloat(const std::string& name, float value);
    unsigned int getShaderID();

    void setVec2(const std::string& name, glm::vec2& value);
    void setVec2(const std::string& name, float x, float y);

    void setVec3(const std::string& name, glm::vec3& value);
    void setVec3(const std::string& name, float x, float y, float z);

    void setVec4(const std::string& name, glm::vec4& value);
    void setVec4(const std::string& name, float x, float y, float z, float w);

	void setMat2(const std::string& name, glm::mat2& mat);
	void setMat3(const std::string& name, glm::mat3& mat);
    void setMat4(const std::string& name, glm::mat4& mat);



};


#endif 
