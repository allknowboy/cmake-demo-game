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
#include "renderer/mesh_renderer.h"
#include "Utils/application.h"



using namespace std;


static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

GLFWwindow* window;
GLint mvp_location, time_location, diffuse_texture_location, vpos_location, vcol_location, a_uv_location;
float m_time = 0.f;
float m_rotateX = .0f, m_rotateY = .0f, m_rotateZ = .0f;


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


int main(int argc, char **argv)
{   
    Application::set_data_path(R"(D:\GitHub\cmake-demo-game\resources\)");

    init_opengl();
    auto mesh_filter = new MeshFilter();
    mesh_filter->LoadMesh(R"(mesh\cube.mesh)");

    auto material = new Material();
    material->Parse("material/cube.mat");

    auto mesh_renderer=new MeshRenderer();
    mesh_renderer->SetMeshFilter(mesh_filter);
    mesh_renderer->SetMaterial(material);

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
        m_time += 0.01f;
        mesh_renderer->SetMVP(mvp);
        mesh_renderer->SetTime(m_time);
        mesh_renderer->Render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}