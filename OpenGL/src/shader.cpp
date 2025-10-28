#include "shader.h"


Shader::Shader(std::string vp, std::string fp) :vertexPath(vp), fragmentPath(fp) {
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
        fragmentShaderFile.open(fragmentPath);

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
Shader::~Shader() {
	GLCall(glDeleteProgram(ID));
}

void Shader::use() {
	GLCall(glUseProgram(ID));
}

void Shader::UnBind() {
    GLCall(glUseProgram(NULL));
}

unsigned int Shader::GetglUniformLocation(const std::string& name) {
    if (UniformLocationCache.find(name) != UniformLocationCache.end()) {
        return UniformLocationCache[name];
    }
    GLCall(unsigned int location = glGetUniformLocation(ID, name.c_str()));
    if (location == -1) {
        std::cout << "Warning: uniform " << name << "is not exist!" << std::endl;
    }
    UniformLocationCache[name] = location;
    return location;
}

void Shader::setUniform4f(const std::string& uniformName, float v0, float v1, float v2, float v3) {
    GLCall(glUniform4f(GetglUniformLocation(uniformName), v0, v1, v2, v3));
}



void Shader::setBool(const std::string& name, bool value) {
    GLCall(glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value));
}
void Shader::setInt(const std::string& name, int value) {
    GLCall(glUniform1i(glGetUniformLocation(ID, name.c_str()), value));
}
void Shader::setFloat(const std::string& name, float value) {
    GLCall(glUniform1f(glGetUniformLocation(ID, name.c_str()), value));
}

unsigned int Shader::getShaderID() {
    return ID;
}

void Shader::setVec2(const std::string& name, glm::vec2& value) {
    GLCall(glUniform2fv(GetglUniformLocation(name), 1, &value[0]));
}
void Shader::setVec2(const std::string& name, float x, float y) {
    GLCall(glUniform2f(GetglUniformLocation(name), x, y));
}

void Shader::setVec3(const std::string& name, glm::vec3& value) {
    GLCall(glUniform3fv(GetglUniformLocation(name), 1, &value[0]));

}
void Shader::setVec3(const std::string& name, float x, float y, float z) {
    GLCall(glUniform3f(GetglUniformLocation(name), x, y, z));
}

void Shader::setVec4(const std::string& name, glm::vec4& value) {
    GLCall(glUniform4fv(GetglUniformLocation(name), 1, &value[0]));
}
void Shader::setVec4(const std::string& name, float x, float y, float z, float w) {
    GLCall(glUniform4f(GetglUniformLocation(name), x, y, z, w));

}

void Shader::setMat2(const std::string& name, glm::mat2& mat) {
	GLCall(glUniformMatrix2fv(GetglUniformLocation(name), 1, GL_FALSE, &mat[0][0]));
}
void Shader::setMat3(const std::string& name, glm::mat3& mat) {
    GLCall(glUniformMatrix3fv(GetglUniformLocation(name), 1, GL_FALSE, &mat[0][0]));
}
void Shader::setMat4(const std::string& name, glm::mat4& mat) {
    GLCall(glUniformMatrix4fv(GetglUniformLocation(name), 1, GL_FALSE, &mat[0][0]));
}



//��̬������ʵ��ʱ���ܼ�static�ؼ���
unsigned int Shader::CompileShader(unsigned int Type, const std::string& source) {
    unsigned int id = glCreateShader(Type);//��Ӧ����İ���ɫ������
    const char* src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));
    checkCompileErrors(Type, "SHADER");
    return id;
}
//������ɫ���������Ӹ�����ɫ��
 unsigned int Shader::CreateShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource) {
    //��ɫ������
    unsigned int shaderProgram = glCreateProgram();
    //������ɫ��
    unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
    //Ƭ����ɫ��
    unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
    GLCall(glAttachShader(shaderProgram, vertexShader));
    GLCall(glAttachShader(shaderProgram, fragmentShader));
    GLCall(glLinkProgram(shaderProgram));
    checkCompileErrors(shaderProgram, "PROGRAM");
    GLCall(glDeleteShader(vertexShader));
    GLCall(glDeleteShader(fragmentShader));

    return shaderProgram;
}


void Shader::checkCompileErrors(unsigned int shaderTypeId, std::string type) {
    int result;
    int length;
    if (type != "PROGRAM") {
        glGetShaderiv(shaderTypeId, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE) {
            glGetShaderiv(shaderTypeId, GL_INFO_LOG_LENGTH, &length);
            char* message = (char*)alloca(sizeof(char) * length);
            glGetShaderInfoLog(shaderTypeId, length, &length, message);
            std::cout << "Failed to compile " <<
                ((shaderTypeId == GL_VERTEX_SHADER) ? "vertex" : "fragment") <<
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