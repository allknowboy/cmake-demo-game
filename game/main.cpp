#define GLFW_INCLUDE_NONE

#include "component/game_object.h"
#include "utils/application.h"

int main(int argc, char **argv)
{   
    Application::set_data_path(R"(D:\GitHub\cmake-demo-game\resources\)");
    Application::InitOpengl(); // 初始化引擎

    GameObject* go = new GameObject("LoginSceneGo");
    go->AddComponent("Transform");
    go->AddComponent("LoginScene");

    Application::Run(); // 开始引擎主循环

}