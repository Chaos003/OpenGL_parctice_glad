#include "shader.h"


Shader::Shader(std::string vp, std::string fp) :vertexPath(vp), fragmentPath(fp) {
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
        fragmentShaderFile.open(fragmentPath);

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



//静态方法在实现时不能加static关键词
unsigned int Shader::CompileShader(unsigned int Type, const std::string& source) {
    unsigned int id = glCreateShader(Type);//对应传入的绑定着色器对象
    const char* src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));
    checkCompileErrors(Type, "SHADER");
    return id;
}
//创建着色器程序链接各个着色器
 unsigned int Shader::CreateShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource) {
    //着色器程序
    unsigned int shaderProgram = glCreateProgram();
    //顶点着色器
    unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
    //片段着色器
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