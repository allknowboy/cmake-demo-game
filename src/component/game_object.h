#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
#include <rttr/registration>
using namespace rttr;

class Component;
class GameObject
{
public:
    GameObject();
    GameObject(std::string name);
    ~GameObject();

    std::string name() { return name_; }
    void set_name(std::string name) { name_ = name; }

    // 添加组件
    Component* AddComponent(std::string component_type_name);
    
    template <class T>
    T* AddComponent() {
        T* component = new T();
        type t = type::get(*component);
        std::string component_type_name = t.get_name().to_string();
        component->set_game_object(this);
        if(component_type_instance_map_.find(component_type_name) == component_type_instance_map_.end()) {
            std::vector<Component*> component_vec;
            component_vec.push_back(component);
            component_type_instance_map_[component_type_name] = component_vec;
        }else{
            component_type_instance_map_[component_type_name].push_back(component);
        }
        return component;
    }

    Component* GetComponent(std::string component_type_name);

    std::vector<Component*>& GetComponents(std::string component_type_name);

private:
    std::string name_;
    std::unordered_map<std::string, std::vector<Component*> > component_type_instance_map_;
};


