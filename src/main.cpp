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
#include "renderer/camera.h"

#include "component/component.h"
#include "component/game_object.h"
#include "component/transform.h"


using namespace std;


static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

GLFWwindow* window;
float m_time = 0.f;

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

    //创建GameObject
    GameObject* go = new GameObject("Tree");
    auto transform = go->AddComponent<Transform>();

    //挂上 MeshFilter 组件
    auto mesh_filter = dynamic_cast<MeshFilter*>(go->AddComponent("MeshFilter"));
    mesh_filter->LoadObj(R"(obj\tree.obj)");
    //挂上MeshRenderer 组件
    auto mesh_renderer = dynamic_cast<MeshRenderer*>(go->AddComponent("MeshRenderer"));

    auto material = new Material();
    material->Parse("material/unknow.mat");
    mesh_renderer->SetMaterial(material);

    //创建相机 GameObject
    auto go_camera = new GameObject("main_camera");
    //挂上 Transform 组件
    auto transform_camera=dynamic_cast<Transform*>(go_camera->AddComponent("Transform"));
    transform_camera->set_position(glm::vec3(0, 0, 10));
    //挂上 Camera 组件
    auto camera = dynamic_cast<Camera*>(go_camera->AddComponent("Camera"));

    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;

        //获取画面宽高
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;

        //设置相机
        camera->SetView(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
        camera->SetProjection(60.f, ratio, 1.f, 1000.f);
        camera->Clear();
        //旋转物体
        glm::vec3 rotation = transform->rotation();
        rotation.y += 0.5f;
        rotation.x -= 0.5f;
        transform->set_rotation(rotation);
        transform->set_scale(glm::vec3(0.001f, 0.001f, 0.001f));
        transform->set_position(glm::vec3(0, 0.01, 0));

        mesh_renderer->SetView(camera->view_mat4());
        mesh_renderer->SetProjection(camera->projection_mat4());
        m_time += 0.01f;
        mesh_renderer->SetTime(m_time);
        mesh_renderer->Render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}