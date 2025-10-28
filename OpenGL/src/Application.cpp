#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "shader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Renderer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"



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
    //float vertices2[] = {
    //    // λ��              // ��ɫ               //����
    //     0.5f, 0.5, 0.0f,    0.5, 0.0f, 0.0f,    1.0f,1.0f, // ����
    //     0.5, -0.5, 0.0f,   0.0f, 0.5, 0.0f,    1.0f,0.0f, // ����
    //     -0.5, 0.5, 0.0f,   0.0f, 0.0f, 0.5,    0.0f,1.0f, // ����
    //     -0.5, -0.5, 0.0f,  0.0f, 0.0f, 0.5,    0.0f,0.0f  // ����
    //};
    
    //�������
    glEnable(GL_DEPTH_TEST);

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    glm::vec3 cubePositions[] = {
       glm::vec3(0.0f,  0.0f,  0.0f),
       glm::vec3(2.0f,  5.0f, -15.0f),
       glm::vec3(-1.5f, -2.2f, -2.5f),
       glm::vec3(-3.8f, -2.0f, -12.3f),
       glm::vec3(2.4f, -0.4f, -3.5f),
       glm::vec3(-1.7f,  3.0f, -7.5f),
       glm::vec3(1.3f, -2.0f, -2.5f),
       glm::vec3(1.5f,  2.0f, -2.5f),
       glm::vec3(1.5f,  0.2f, -1.5f),
       glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    //unsigned int indices[] = {
    //    //    //�洢��ʱvertices������±꣬����Ϊ������ĳ���������
    //        0,1,2,//��һ��������
    //        1,3,2 //�ڶ���������
    //};

    {

        Shader shader("res/shaders/3.3.vertex.shader", "res/shaders/3.3.fragment.shader");

        //�����������Ӧ�����Ȱ󶨣�
        VertexArray va;
        va.vertex_Array_Bind();

        VertexBuffer vertex_buffer(vertices, sizeof(vertices));
   /*     IndexBuffer index_buffer(indices, sizeof(indices) / sizeof(indices[0]));*/

        VertexBufferLayout layout;
        layout.push<float>(3);
        layout.push<float>(2);

        std::cout << layout.getStride() << std::endl;

        va.add_vertex_Buffer(vertex_buffer, layout);

        //��һ������Ԫ
        unsigned int texture1, texture2;
        glGenTextures(1, &texture1);
        glBindTexture(GL_TEXTURE_2D, texture1);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);

        unsigned char* data = stbi_load("source/123123.jpg", &width, &height, &nrChannels, 0);

        if (data) {

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);

        //�ڶ�������Ԫ
        glGenTextures(1, &texture2);
        glBindTexture(GL_TEXTURE_2D, texture2);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		data = stbi_load("source/456.png", &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);




        shader.use();
        //�ֶ�����
        //glUniform1i(glGetUniformLocation(shader.getShaderID(), "texture1"), 0);
		shader.setInt("texture1", 0);
        shader.setInt("texture2", 1);

        //ѭ����Ⱦ
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            processInput(window);

            glClearColor(0.2f, 0.3f, 0.3f, 0.8f);
            /* Render here */
          
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture1);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, texture2);

            shader.use();

            //����ͶӰ����
            //glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);
            //͸��ͶӰ����
            //glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);

            //glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
            //glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
            //glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
            //glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
            //glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
            //glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);


            glm::mat4 view = glm::mat4(1.0f); 
            float radius = 10.0f;
            float camX = sin(glfwGetTime()) * radius;
            float camZ = cos(glfwGetTime()) * radius;
            view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));

            glm::mat4 projection = glm::mat4(1.0f);
            projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
            //view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
            // pass transformation matrices to the shader
            shader.setMat4("projection", projection); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
            shader.setMat4("view", view);

            // render boxes
            //����
            va.vertex_Array_Bind();
            //glBindVertexArray(va.getVAO());
            for (unsigned int i = 0; i < 10; i++)
            {
                // calculate the model matrix for each object and pass it to shader before drawing
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, cubePositions[i]);
                float angle = 20.0f * i;
                model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
                shader.setMat4("model", model);

                glDrawArrays(GL_TRIANGLES, 0, 36);
            }



            //������ɫ��
            //shader.use();


       
			
       
            
            //�����߿�
            //glLineWidth(2.0f);
            //�л��߿�ģʽ(GL_LINE)/���ģʽ��GL_FILL)
            //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
           

            //GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
            // 
            // glDrawArrays(GL_TRIANGLES, 0, 3);


             /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

        //�ͷ�������Դ
        //glDeleteVertexArrays(1, &VAO);
        //vertex_buffer.~VertexBuffer();
        //index_buffer.~IndexBuffer();
        //glDeleteProgram(shaderProgram);

        // glfw: terminate, clearing all previously allocated GLFW resources.
    }
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


////����uniform��ɫ
            //float timeValue = glfwGetTime();
            ////ͨ��ʱ�䱣֤������0-1֮�����ѭ�����ı���ɫ��
     /*       float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
            int vertexColorLocation = glGetUniformLocation(shader.ID, "ourColor");
            glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 0.8f);*/


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


//glGenBuffers(1, &VBO);
//glGenBuffers(1, &EBO);
//
////�󶨶��㻺������Ȱ�VAO
//glBindVertexArray(VAO);
//
////���ƶ������ݵ�������ڴ�
//glBindBuffer(GL_ARRAY_BUFFER, VBO);
//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
//
////�����������鵽��������
//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


//unsigned int VAO;
//glGenVertexArrays(1, &VAO);
//glBindVertexArray(VAO); //����Ҫ�󶨶����������
//
//
//
//VertexBuffer vertex_buffer(vertices2, sizeof(vertices2));
//
//IndexBuffer index_buffer(indices, sizeof(indices) / sizeof(indices[0]));
//
//
//
//
//
////1�����ö�������ָ��
////(position�Ķ�������ֵ���������Դ�С��vec3����ָ���������ͣ�
//// ��׼��ӳ�䣨GL_TRUE�����������ݻᱻӳ�䵽0-1֮�䣩��
//// ������������֮����ֽڼ������
//// ����ǿ������ת�������������ʼλ��ƫ��)
//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
//glEnableVertexAttribArray(0);
//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
//glEnableVertexAttribArray(1);

//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//glBindBuffer(GL_ARRAY_BUFFER, 0);
//glBindVertexArray(0);