#version 330 core
layout (location=0)in vec3 pos;

out vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    TexCoords = pos;
    vec4 cpos = projection * view * vec4(pos, 1.0);
    gl_Position = cpos.xyww;
}