#pragma once

//顶点着色器代码
static const char* vertex_shader_text = R"(
    #version 330 core
    layout(location = 0) in vec3 a_pos;
    layout(location = 1) in vec4 a_color;
    layout(location = 2) in vec2 a_uv;
    uniform mat4 u_mvp;
    out vec4 v_color;
    out vec2 v_uv;
    void main()
    {
        gl_Position = u_mvp * vec4(a_pos, 1.0);
        v_color = a_color;
        v_uv = a_uv;
    }
)";

//片段着色器代码
static const char* fragment_shader_text = R"(
    #version 330 core
    out vec4 FragColor;
    uniform float u_time;
    uniform sampler2D u_diffuse_texture;
    in vec4 v_color;
    in vec2 v_uv;
    void main()
    {
        FragColor = texture2D(u_diffuse_texture, v_uv);
    } 
)";