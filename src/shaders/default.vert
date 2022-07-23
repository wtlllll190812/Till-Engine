#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;



out DefaultOut {
    vec3 FragPos;
    vec2 TexCoords;
    vec3 Normal;
    vec4 FragPosLightSpace;
} defaultOut;
layout(std140)uniform Matrices
{
    mat4 projection;
    mat4 view;
};
uniform mat4 model;
uniform mat4 lightSpaceMat;

void main()
{
    gl_Position = projection * view *  model * vec4(position, 1.0f);
    defaultOut.TexCoords=texCoords;
    defaultOut.FragPos = vec3(model * vec4(position, 1.0f));
    defaultOut.Normal = mat3(transpose(inverse(model))) * normal;//生成正规矩阵(法向量直接乘以模型矩阵缩放变换会导致法向量的变形)
    defaultOut.FragPosLightSpace = lightSpaceMat * vec4(defaultOut.FragPos, 1.0);
} 