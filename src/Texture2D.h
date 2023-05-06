#pragma once
#define STB_IMAGE_IMPLEMENTATION
#include <iostream>

#include <glad/glad.h>

class Texture2D
{
private:
    Texture2D(){};
    ~Texture2D(){};
public:
    static Texture2D* LoadFromFile(std::string& image_file_path);
public:
    int width_;
    int height_;

    GLenum gl_texture_format_;
    GLuint gl_texture_id_; //纹理ID
};