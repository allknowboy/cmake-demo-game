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
    static void CompressImageFile(std::string& image_file_path, std::string& save_image_file_path);
public:
    int mipmap_level_;
    int width_;
    int height_;

    GLenum gl_texture_format_;
    GLuint gl_texture_id_; //纹理ID

    //tcp文件头
    struct CptFileHead
    {
        char type_[3];
        int mipmap_level_;
        int width_;
        int height_;
        int gl_texture_format_;
        int compress_size_;
    };
};