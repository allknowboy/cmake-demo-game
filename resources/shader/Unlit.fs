#version 330 core
out vec4 FragColor;
uniform float u_time;
uniform sampler2D u_diffuse_texture;
in vec4 v_color;
in vec2 v_uv;
void main()
{
    FragColor = texture2D(u_diffuse_texture, v_uv) * v_color;
}