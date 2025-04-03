#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "shader.h"




//窗口大小
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//处理输入
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

//调整视口大小
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}





int main(void)
{
    //首先应该初始化GLFW和GLAD
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

        glfwTerminate();//清理资源
        return -1;
    }
    //链接上下文窗口
    /* Make the window's context current */
    glfwMakeContextCurrent(window);


    //通知窗口调整大小时候调用framebuffer_size_callback函数
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //初始化glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    Shader shader("res/shaders/3.3.vertex.shader", "res/shaders/3.3.fragment.shader");
    
    /*GLCall(glUseProgram(shaderProgram));
    GLCall(int location = glGetUniformLocation(shaderProgram, "ourColor"));
    ASSERT(location != -1);*/



    float vertices[] = {
    0.5f, 0.5f, 0.0f,   // 右上角
    0.5f, -0.5f, 0.0f,  // 右下角
    -0.5f, -0.5f, 0.0f, // 左下角
    -0.5f, 0.5f, 0.0f   // 左上角
    };
    float vertices2[] = {
        // 位置              // 颜色
         -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
        -0.5f, 0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
         0.5f, 0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  // 顶部
         0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f // 顶部



        // // 位置              // 颜色
        // 0.5f, -0.5f, 0.0f,  0.5f, 0.0f, 0.0f,   // 右下
        //-0.5f, -0.5f, 0.0f,  0.0f, 0.5f, 0.0f,   // 左下
        // 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 0.5f    // 顶部
    };

    unsigned int indices[] = {
    //    //存储的时vertices数组的下标，返回为三角形某顶点的坐标
        0,1,3,//第一个三角形
        1,2,3 //第二个三角形
    };



    //顶点数组对象（应该优先绑定）
    unsigned int VAO;
    //顶点缓冲对象
    unsigned int VBO;
    //元素缓冲对象
    unsigned int EBO;

    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    //绑定顶点缓冲对象，先绑定VAO
    glBindVertexArray(VAO);

    //复制顶点数据到缓冲的内存
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

    //复制索引数组到索引缓冲
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //1、设置顶点属性指针
    //(position的顶点属性值，顶点属性大小（vec3），指定数据类型，
    // 标准化映射（GL_TRUE代表所有数据会被映射到0-1之间），
    // 步长：组数据之间的字节间隔数，
    // 数据强制类型转换解决缓冲中起始位置偏移)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindVertexArray(0);


   
    //循环渲染
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        //激活着色器
        shader.use();

        ////更新uniform颜色
        float timeValue = glfwGetTime();
        ////通过时间保证数据在0-1之间进行循环（改变颜色）
 /*       float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shader.ID, "ourColor");
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);*/


        //绘制
        glBindVertexArray(VAO);
        //设置线宽
        glLineWidth(2.0f);
        //切换线框模式(GL_LINE)/填充模式（GL_FILL)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);



        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
       // glDrawArrays(GL_TRIANGLES, 0, 3);
  

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    //释放所有资源
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &VBO);
    //glDeleteProgram(shaderProgram);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}







//glUseProgram(shaderProgram);
////删除着色器对象
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
//out vec3 ourColor; //指定片段颜色输出
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
//    //通过动态编译源代码附加顶点着色器对象
//    *vertexShader = glCreateShader(GL_VERTEX_SHADER);
//    glShaderSource(*vertexShader, 1, &vertexShaderSource, NULL);
//    glCompileShader(*vertexShader);
//
//    //编译成功检验
//    check_successful(*vertexShader);
//}
//
//void fragmentShader_compile(unsigned int* fragmentShader) {
//    //同动态编译附加片段着色器对象
//    *fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//    glShaderSource(*fragmentShader, 1, &fragmentShaderSource, NULL);
//    glCompileShader(*fragmentShader);
//    //编译成功检验
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



//uniform为全局的，在每个着色器程序中独一无二
//如果你声明了一个uniform却在GLSL代码中没用过，编译器会静默移除这个变量，
// 导致最后编译出的版本中并不会包含它，这可能导致几个非常麻烦的错误，记住这点！
//uniform vec4 ourColor;


//GLSL编写顶点着色器，源代码硬编码存储于字符串，后续动态编译
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
////GLSL中存在4个分量，代表空间中的一个坐标，通过vec.x,vec.y,vec.z,vex,w来获取
////vec.w 使用场景为透视除法（Perspective Division）
//
////片段着色器
//
////先绑定顶点着色器，然后顶点着色器输出顶点的颜色属性，构建图元后，片段着色器对顶点间的所有像素进行逐步渲染
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
            << "├── [ Error function ] " << function << "\n"
            << "├── [ Error file ] " << file << "\n"
            << "└── [ Error line ] " << line << std::endl;
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
        //std::string::npos为常量，返回值为-1
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos) {
                type = ShaderType::FRAGMENT;
            }
        }
        else {
            //直接推入对应的数组ss[0]和ss[1]中，对每次进行换行
            ss[(int)type] << line << '\n';
        }
    }
    return  { ss[0].str(),ss[1].str() };
}*/