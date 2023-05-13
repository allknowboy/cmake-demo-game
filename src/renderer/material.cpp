#include "material.h"
#include <iostream>
#include <fstream>
#include <glad/glad.h>
#include "shader.h"
#include "texture2d.h"
#include "utils/application.h"
#include <yaml-cpp/yaml.h>

using std::ifstream;
using std::ios;
using std::cout;
using std::endl;

Material::Material() {

}

Material::~Material() {

}

void Material::Parse(string material_path) {
    YAML::Node config = YAML::LoadFile((Application::data_path() + material_path).c_str());
    if (config.IsNull()) {
        return;
    }
    auto mat_node = config["material"];
    if (mat_node.IsNull()) {
        return;
    }
    auto shader_node = mat_node["shader"];
    if (shader_node.IsNull()) {
        return;
    }
    shader_ = Shader::Find(shader_node.as<string>());
    auto texture_node = mat_node["texture"];
    if (texture_node.IsNull()) { 
        return;
    }
    for(auto it = texture_node.begin(); it != texture_node.end(); ++it) {
        auto node = *it;
        if (node.IsNull()) { 
            return;
        }
        auto shader_property_name = node["name"].as<string>();
        auto image_path = node["image"].as<string>();
        textures_.push_back(std::make_pair(shader_property_name, Texture2D::LoadFromFile(image_path)));
    }
}

void Material::SetUniformMatrix4fv(std::string shader_property_name, float *pointer) {
    uniform_matrix4fv_vec.push_back(std::make_pair(shader_property_name, pointer));
}

void Material::SetUniform1i(std::string shader_property_name, int value) {
    uniform_1i_vec.push_back(std::make_pair(shader_property_name, value));
}


