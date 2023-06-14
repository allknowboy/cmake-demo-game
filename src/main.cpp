#include <iostream>
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/ext.hpp>

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
#include "control/input.h"
#include "control/key_code.h"

using namespace std;


static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

/// 键盘回调
/// \param window
/// \param key 键盘按键编码
/// \param scancode
/// \param action 0松开 1按下 2一直按下
/// \param mods
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Input::RecordKey(key, action);
}

/// 鼠标按键回调
/// \param window
/// \param button
/// \param action
/// \param mods
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    Input::RecordKey(button, action);
    std::cout << "mouse_button_callback:" << button << "," << action << std::endl;
}

/// 鼠标移动回调
/// \param window
/// \param x
/// \param y
void mouse_move_callback(GLFWwindow* window, double x, double y)
{
    Input::set_mousePosition(x,y);
    std::cout << "mouse_move_callback:" << x << "," << y << std::endl;
}

/// 鼠标滚轮回调
/// \param window
/// \param x
/// \param y
void mouse_scroll_callback(GLFWwindow* window, double x, double y)
{
    Input::RecordScroll(y);
    std::cout << "mouse_scroll_callback:" << x << "," << y << std::endl;
}

GLFWwindow* window;
float m_time = 0.f;

/// 初始化OpenGL
void init_opengl()
{
    std::cout << "init opengl" <<endl;

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
    // 创建窗口
    window = glfwCreateWindow(960, 640, "Simple example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glfwSwapInterval(1);

    // 按键监听
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window,mouse_button_callback);
    glfwSetScrollCallback(window,mouse_scroll_callback);
    glfwSetCursorPosCallback(window,mouse_move_callback);
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
    go->set_layer(0x01);
    auto transform = go->AddComponent<Transform>();

    //挂上 MeshFilter 组件
    auto mesh_filter = dynamic_cast<MeshFilter*>(go->AddComponent("MeshFilter"));
    mesh_filter->LoadObj(R"(obj\tree.obj)");
    //挂上MeshRenderer 组件
    auto mesh_renderer = dynamic_cast<MeshRenderer*>(go->AddComponent("MeshRenderer"));

    auto material = new Material();
    material->Parse("material/unknow.mat");
    mesh_renderer->SetMaterial(material);

    //创建相机1 GameObject
    auto go_camera_1 = new GameObject("main_camera");
    //挂上 Transform 组件
    auto transform_camera_1 = dynamic_cast<Transform*>(go_camera_1->AddComponent("Transform"));
    transform_camera_1->set_position(glm::vec3(0, 0, 10));
    //挂上 Camera 组件
    auto camera_1 = dynamic_cast<Camera*>(go_camera_1->AddComponent("Camera"));
    camera_1->set_depth(0);
    camera_1->set_culling_mask(0x01);

    //创建相机2 GameObject
    auto go_camera_2 = new GameObject("main_camera");
    //挂上 Transform 组件
    auto transform_camera_2 = dynamic_cast<Transform*>(go_camera_2->AddComponent("Transform"));
    transform_camera_2->set_position(glm::vec3(5, 0, 10));
    //挂上 Camera 组件
    auto camera_2 = dynamic_cast<Camera*>(go_camera_2->AddComponent("Camera"));
    //第二个相机不能清除之前的颜色。不然用第一个相机矩阵渲染的物体就被清除 没了。
    camera_2->set_clear_flag(GL_DEPTH_BUFFER_BIT);
    camera_2->set_depth(1);
    camera_2->set_culling_mask(0x02);

    //上一帧的鼠标位置
    vec2_ushort last_frame_mouse_position=Input::mousePosition();

    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;

        //获取画面宽高
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;

        //设置相机1
        camera_1->SetView(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
        camera_1->SetProjection(60.f, ratio, 1.f, 1000.f);

        //设置相机2
        camera_2->SetView(glm::vec3(0.1, 0, 0), glm::vec3(0, 1, 0));
        camera_2->SetProjection(60.f, ratio, 1.f, 1000.f);


        transform->set_scale(glm::vec3(0.001f, 0.001f, 0.001f));
        transform->set_position(glm::vec3(0, 0.01, 0));

        //旋转物体
        if(Input::GetKeyDown(KEY_CODE_R)){
            //旋转物体
            glm::vec3 rotation = transform->rotation();
            rotation.y += 0.5f;
            rotation.x -= 0.5f;
            transform->set_rotation(rotation);
        }

        //旋转相机
        if(Input::GetKeyDown(KEY_CODE_LEFT_ALT) && Input::GetMouseButtonDown(MOUSE_BUTTON_LEFT)){
            float degreesX = Input::mousePosition().x_ - last_frame_mouse_position.x_;
            float degreesY = Input::mousePosition().y_ - last_frame_mouse_position.y_;
            glm::mat4 old_mat4 = glm::mat4(1.0f);
            std::cout << glm::to_string(old_mat4) << std::endl;
            glm::mat4 rotate_mat4 = glm::rotate(old_mat4, glm::radians(degreesX * 100), glm::vec3(0.0f, 1.0f, 0.0f)); // 以相机所在坐标系位置，计算用于旋转的矩阵，这里是零点，所以直接用方阵。
            rotate_mat4 = glm::rotate(rotate_mat4, glm::radians(degreesY * 100), glm::vec3(1.0f, 0.0f, 0.0f)); // 以相机所在坐标系位置，计算用于旋转的矩阵，这里是零点，所以直接用方阵。
            glm::vec4 old_pos = glm::vec4(transform_camera_1->position(), 1.0f);
            glm::vec4 new_pos = rotate_mat4 * old_pos; // 旋转矩阵 * 原来的坐标 = 相机以零点做旋转。
            std::cout << glm::to_string(new_pos) << std::endl;
            transform_camera_1->set_position(glm::vec3(new_pos));
        }

        last_frame_mouse_position = Input::mousePosition();
        //鼠标滚轮控制相机远近
        transform_camera_1->set_position(transform_camera_1->position()*=(10 - Input::mouse_scroll())/10.f);

        //将状态为弹起的按键清理掉
        Input::Update();

        //遍历所有相机，每个相机的View Projection，都用来做一次渲染。
        Camera::Foreach([&](){
            mesh_renderer->Render();
        });

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}