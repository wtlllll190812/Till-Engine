#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out vec2 TexCoords;
out vec3 Normal;
out vec3 FragPos;

layout(std140)uniform Matrices
{
    mat4 projection;
    mat4 view;
};
uniform mat4 model;


void main()
{
    TexCoords=texCoords;
    gl_Position = projection * view *  model * vec4(position, 1.0f);
    FragPos = vec3(model * vec4(position, 1.0f));
    Normal = mat3(transpose(inverse(model))) * normal;//生成正规矩阵(法向量直接乘以模型矩阵缩放变换会导致法向量的变形)
} 