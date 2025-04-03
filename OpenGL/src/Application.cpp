#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "shader.h"




//���ڴ�С
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//��������
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

//�����ӿڴ�С
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}





int main(void)
{
    //����Ӧ�ó�ʼ��GLFW��GLAD
    glfwInit();
    /* Initialize the library */
    if (!glfwInit())
        return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT,
        "GenShin Impact Start!", NULL, NULL);
    if (window == NULL) {
        std::cerr << "Failed to create  GLFW window!" << std::endl;

        glfwTerminate();//������Դ
        return -1;
    }
    //���������Ĵ���
    /* Make the window's context current */
    glfwMakeContextCurrent(window);


    //֪ͨ���ڵ�����Сʱ�����framebuffer_size_callback����
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //��ʼ��glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    Shader shader("res/shaders/3.3.vertex.shader", "res/shaders/3.3.fragment.shader");
    
    /*GLCall(glUseProgram(shaderProgram));
    GLCall(int location = glGetUniformLocation(shaderProgram, "ourColor"));
    ASSERT(location != -1);*/



    float vertices[] = {
    0.5f, 0.5f, 0.0f,   // ���Ͻ�
    0.5f, -0.5f, 0.0f,  // ���½�
    -0.5f, -0.5f, 0.0f, // ���½�
    -0.5f, 0.5f, 0.0f   // ���Ͻ�
    };
    float vertices2[] = {
        // λ��              // ��ɫ
         -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // ����
        -0.5f, 0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // ����
         0.5f, 0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  // ����
         0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f // ����



        // // λ��              // ��ɫ
        // 0.5f, -0.5f, 0.0f,  0.5f, 0.0f, 0.0f,   // ����
        //-0.5f, -0.5f, 0.0f,  0.0f, 0.5f, 0.0f,   // ����
        // 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 0.5f    // ����
    };

    unsigned int indices[] = {
    //    //�洢��ʱvertices������±꣬����Ϊ������ĳ���������
        0,1,3,//��һ��������
        1,2,3 //�ڶ���������
    };



    //�����������Ӧ�����Ȱ󶨣�
    unsigned int VAO;
    //���㻺�����
    unsigned int VBO;
    //Ԫ�ػ������
    unsigned int EBO;

    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    //�󶨶��㻺������Ȱ�VAO
    glBindVertexArray(VAO);

    //���ƶ������ݵ�������ڴ�
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

    //�����������鵽��������
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //1�����ö�������ָ��
    //(position�Ķ�������ֵ���������Դ�С��vec3����ָ���������ͣ�
    // ��׼��ӳ�䣨GL_TRUE�����������ݻᱻӳ�䵽0-1֮�䣩��
    // ������������֮����ֽڼ������
    // ����ǿ������ת�������������ʼλ��ƫ��)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindVertexArray(0);


   
    //ѭ����Ⱦ
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        //������ɫ��
        shader.use();

        ////����uniform��ɫ
        float timeValue = glfwGetTime();
        ////ͨ��ʱ�䱣֤������0-1֮�����ѭ�����ı���ɫ��
 /*       float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shader.ID, "ourColor");
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);*/


        //����
        glBindVertexArray(VAO);
        //�����߿�
        glLineWidth(2.0f);
        //�л��߿�ģʽ(GL_LINE)/���ģʽ��GL_FILL)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);



        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
       // glDrawArrays(GL_TRIANGLES, 0, 3);
  

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    //�ͷ�������Դ
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &VBO);
    //glDeleteProgram(shaderProgram);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}







//glUseProgram(shaderProgram);
////ɾ����ɫ������
//glDeleteShader(vertexShader);
//glDeleteShader(fragmentShader);

//const char* vertexShaderSource = "#version 330 core\n"
//"layout (location=0) in vec3 aPos;\n"
//"void main()\n"
//"{\n"
//"   gl_Position =vec4(aPos.x,aPos.y,aPos.z,1.0);\n"
//    
//"}\0";

//const char* v = R"({
//#version 330 core
//layout(location = 0) in vec3 aPos;
//void main(){
//    gl_Position = vec4(aPos, 1.0);
//}
//)";



//const char* vertexShaderSource = R"(
//#version 330 core
//layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec3 aColor;
//
//out vec3 ourColor; //ָ��Ƭ����ɫ���
//
//void main(){
//    gl_Position = vec4(aPos, 1.0);
//    ourColor = aColor;
//}
//)";


//const char* fragmentShaderSource = R"(
//#version 330 core
//
//out vec4 FragColor;
//in vec3 ourColor;
//
//void main()
//{
//   FragColor = vec4(ourColor, 1.0);
//}
//)";




//void check_successful(int shader) {
//    int success;
//    char infoLog[512];
//    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
//    if (!success) {
//        glGetShaderInfoLog(shader, 512, NULL, infoLog);
//        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
//            << infoLog << std::endl;
//    }
//}


//void vertexShader_compile(unsigned int* vertexShader) {
//    //ͨ����̬����Դ���븽�Ӷ�����ɫ������
//    *vertexShader = glCreateShader(GL_VERTEX_SHADER);
//    glShaderSource(*vertexShader, 1, &vertexShaderSource, NULL);
//    glCompileShader(*vertexShader);
//
//    //����ɹ�����
//    check_successful(*vertexShader);
//}
//
//void fragmentShader_compile(unsigned int* fragmentShader) {
//    //ͬ��̬���븽��Ƭ����ɫ������
//    *fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//    glShaderSource(*fragmentShader, 1, &fragmentShaderSource, NULL);
//    glCompileShader(*fragmentShader);
//    //����ɹ�����
//    check_successful(*fragmentShader);
//}
//
//static unsigned int  create_shaderProgram(unsigned int* shaderProgram, unsigned int* vertexShader, unsigned int* fragmentShader) {
//    *shaderProgram = glCreateProgram();
//    glAttachShader(*shaderProgram, *vertexShader);
//    glAttachShader(*shaderProgram, *fragmentShader);
//    glLinkProgram(*shaderProgram);
//    int success;
//    char infoLog[512];
//    glGetProgramiv(*shaderProgram, GL_LINK_STATUS, &success);
//    if (!success) {
//        glGetShaderInfoLog(*fragmentShader, 512, NULL, infoLog);
//        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
//            << infoLog << std::endl;
//    }
//}



//uniformΪȫ�ֵģ���ÿ����ɫ�������ж�һ�޶�
//�����������һ��uniformȴ��GLSL������û�ù����������ᾲĬ�Ƴ����������
// ������������İ汾�в����������������ܵ��¼����ǳ��鷳�Ĵ��󣬼�ס��㣡
//uniform vec4 ourColor;


//GLSL��д������ɫ����Դ����Ӳ����洢���ַ�����������̬����
//const std::string vertexShaderSourse = R"(
//#version 330 core
//layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec3 aColor;
//
//out vec3 ourColor;
//
//void main(){
//    gl_Position = vec4(aPos, 1.0);
//    ourColor = aColor;
//}
//)";
//
//
//
////GLSL�д���4������������ռ��е�һ�����꣬ͨ��vec.x,vec.y,vec.z,vex,w����ȡ
////vec.w ʹ�ó���Ϊ͸�ӳ�����Perspective Division��
//
////Ƭ����ɫ��
//
////�Ȱ󶨶�����ɫ����Ȼ�󶥵���ɫ������������ɫ���ԣ�����ͼԪ��Ƭ����ɫ���Զ������������ؽ�������Ⱦ
////layout(location = 0) out ver4 FragColor;
//
//const std::string fragmentShaderSource = R"(
//#version 330 core
//
//out vec4 FragColor;
//in vec3 ourColor;
//
//void main()
//{
//   FragColor = vec4(ourColor, 1.0);
//}
//)";

/*
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

struct ShaderProgramSource {
    std::string vertexShaderSourse;
    std::string fragmentShaderSource;
};

static ShaderProgramSource PareShader(const std::string& filepath) {
    std::ifstream stream(filepath);

    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line)) {
        //std::string::nposΪ����������ֵΪ-1
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos) {
                type = ShaderType::FRAGMENT;
            }
        }
        else {
            //ֱ�������Ӧ������ss[0]��ss[1]�У���ÿ�ν��л���
            ss[(int)type] << line << '\n';
        }
    }
    return  { ss[0].str(),ss[1].str() };
}*/