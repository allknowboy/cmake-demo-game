#include <iostream>
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtx/transform2.hpp>
#include<glm/gtx/euler_angles.hpp>

#include <stdlib.h>
#include <stdio.h>

#include "vertex_data.h"
#include "renderer/mesh_filter.h"
#include "renderer/shader.h"
#include "renderer/texture2d.h"
#include "renderer/material.h"
#include "Utils/application.h"



using namespace std;


static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

GLFWwindow* window;
GLint mvp_location, time_location, diffuse_texture_location, vpos_location, vcol_location, a_uv_location;
float m_time = 0.f;
MeshFilter* mesh_filter= nullptr;
float m_rotateX = .0f, m_rotateY = .0f, m_rotateZ = .0f;
GLuint kVBO, kEBO;
GLuint kVAO;

/// 创建VAO
void GeneratorVertexArrayObject(){
    glGenVertexArrays(1, &kVAO);
}

/// 初始化OpenGL
void init_opengl()
{
    cout<<"init opengl"<<endl;

    //设置错误回调
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    //创建窗口
    window = glfwCreateWindow(960, 640, "Simple example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glfwSwapInterval(1);
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

//创建VBO和EBO
void GeneratorBufferObject()
{
    //在GPU上创建缓冲区对象
    glGenBuffers(1, &kVBO);
    //将缓冲区对象指定为顶点缓冲区对象
    glBindBuffer(GL_ARRAY_BUFFER, kVBO);
    //上传顶点数据到缓冲区对象
    glBufferData(GL_ARRAY_BUFFER, mesh_filter->mesh()->vertex_num_ * sizeof(MeshFilter::Vertex), mesh_filter->mesh()->vertex_data_, GL_STATIC_DRAW);

    //在GPU上创建缓冲区对象
    glGenBuffers(1, &kEBO);
    //将缓冲区对象指定为顶点索引缓冲区对象
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, kEBO);
    //上传顶点索引数据到缓冲区对象
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh_filter->mesh()->vertex_index_num_ * sizeof(unsigned short), mesh_filter->mesh()->vertex_index_data_, GL_STATIC_DRAW);

    // 设置VAO
    glBindVertexArray(kVAO);
    {
        //指定当前使用的VBO
        glBindBuffer(GL_ARRAY_BUFFER, kVBO);
        glVertexAttribPointer(vpos_location, 3, GL_FLOAT, false, sizeof(Vertex), 0);
        glVertexAttribPointer(vcol_location, 4, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(float)*3));
        glVertexAttribPointer(a_uv_location, 2, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(float)*(3 + 4)));

        glEnableVertexAttribArray(vpos_location);
        glEnableVertexAttribArray(vcol_location);
        glEnableVertexAttribArray(a_uv_location);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, kEBO);
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

int main(int argc, char **argv)
{   
    Application::set_data_path(R"(D:\GitHub\cmake-demo-game\resources\)");

    init_opengl();
    mesh_filter = new MeshFilter();
    mesh_filter->LoadMesh(R"(mesh\cube.mesh)");
    auto material = new Material();
    material->Parse("material/cube.mat");
    //获取`Shader`的`gl_program_id`，指定为目标Shader程序。
    GLuint gl_program_id = material->shader()->gl_program_id();

    //获取shader属性ID
    mvp_location = glGetUniformLocation(gl_program_id, "u_mvp");
    time_location = glGetUniformLocation(gl_program_id, "u_time");
    diffuse_texture_location = glGetUniformLocation(gl_program_id, "u_diffuse_texture");
    vpos_location = glGetAttribLocation(gl_program_id, "a_pos");
    vcol_location = glGetAttribLocation(gl_program_id, "a_color");
    a_uv_location = glGetAttribLocation(gl_program_id, "a_uv");

    GeneratorVertexArrayObject();
    GeneratorBufferObject();

    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;
        glm::mat4 model, view, projection, mvp;

        //获取画面宽高
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glClearColor(49.f/255, 77.f/255, 121.f/255, 1.f);

        m_rotateX += 0.1f;
        m_rotateY += 0.5f;
        m_rotateZ += 0.3f;
        //坐标系变换
        glm::mat4 trans = glm::translate(glm::vec3(0, 0, 0)); //不移动顶点坐标;
        glm::mat4 rotation = glm::eulerAngleYXZ(glm::radians(m_rotateX), glm::radians(m_rotateY), glm::radians(m_rotateZ)); //使用欧拉角旋转;
        glm::mat4 scale = glm::scale(glm::vec3(1.0f, 1.0f, 1.0f)); //缩放;
        model = trans * scale * rotation;
        view = glm::lookAt(glm::vec3(0, 0, 300), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
        projection = glm::perspective(glm::radians(60.f), ratio, 1.f, 1000.f);
        mvp = projection * view * model;

        //指定GPU程序(就是指定顶点着色器、片段着色器)
        glUseProgram(gl_program_id);
        {
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_CULL_FACE);//开启背面剔除
            //上传mvp矩阵
            glUniformMatrix4fv(mvp_location, 1, GL_FALSE, &mvp[0][0]);
            glUniform1f(time_location, m_time);
             //拿到保存的Texture
            std::vector<std::pair<std::string,Texture2D*>> textures=material->textures();
            for (int texture_index = 0; texture_index < textures.size(); ++texture_index) {
                GLint u_texture_location = glGetUniformLocation(gl_program_id, textures[texture_index].first.c_str());
                //激活纹理单元0
                glActiveTexture(GL_TEXTURE0+texture_index);
                //将加载的图片纹理句柄，绑定到纹理单元0的Texture2D上。
                glBindTexture(GL_TEXTURE_2D,textures[texture_index].second->gl_texture_id());
                //设置Shader程序从纹理单元0读取颜色数据
                glUniform1i(u_texture_location,texture_index);
            }
            glBindVertexArray(kVAO);
            {
                glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);//使用顶点索引进行绘制，最后的0表示数据偏移量。
            }
            glBindVertexArray(0);
        }
        m_time += 0.01f;
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}