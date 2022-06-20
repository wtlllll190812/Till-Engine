#version 330 core
in vec3 ourColor;
in vec2 TexCoord;

out vec4 color;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform sampler2D ourTexture;

void main()
{
    color = lightColor*texture(ourTexture, TexCoord);
}