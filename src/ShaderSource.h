#pragma once

//顶点着色器代码
static const char* vertex_shader_text = R"(
    #version 330 core
    layout(location = 0) in vec3 a_pos;
    layout(location = 1) in vec4 a_color;
    uniform mat4 u_mvp;
    out vec4 v_color;
    void main()
    {
        gl_Position = u_mvp * vec4(a_pos, 1.0);
        v_color = a_color;
    }
)";

//片段着色器代码
static const char* fragment_shader_text = R"(
    #version 330 core
    out vec4 FragColor;
    uniform float u_time;
    in vec4 v_color;
    float random2d(vec2 coord) {
        return fract(sin(dot(coord.xy, vec2(12.9898, 78.233))) * 43758.5453);
    }
    void main()
    {
        // FragColor = v_color * u_time;
        vec2 coord = gl_FragCoord.xy * 0.1;
        vec3 color = vec3(.0);
        coord -= u_time + vec2(sin(coord.y), cos(coord.x));
        float rand01 = fract(random2d(floor(coord)) + u_time / 60.0);
        float rand02 = fract(random2d(floor(coord)) + u_time / 40.0);
        rand01 *= 0.4 - length(fract(coord));
        FragColor = vec4(rand01 * 4.0, rand02 * rand01 * 4.0, .0, 1.0);
    } 
)";