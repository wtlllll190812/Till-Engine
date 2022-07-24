#version 330 core
out vec4 color;

in vec3 FragPos;  
in vec3 Normal;  
in vec2 TexCoords;

layout(std140)uniform LightData
{
    vec3 lightPos; 
    vec3 lightColor;
    vec3 viewPos;
};

in DefaultOut {
    vec3 FragPos;
    vec2 TexCoords;
    vec3 Normal;
    vec4 FragPosLightSpace;
} defaultIn;

uniform float cutoff;
uniform vec3 spotLightDir;
uniform sampler2D diffuseMap;
uniform sampler2D specularMap;
uniform sampler2D shadowMap;


void main()
{
    float dis = length(lightPos - defaultIn.FragPos);
    vec3 lightDir = normalize(lightPos - defaultIn.FragPos);

    //float t = dot(normalize(spotLightDir),lightDir);
    float intensity = 1.0f;// / (1.0f + 0.09f * dis + 0.032 * dis * dis);

    vec3 ObjectColor = vec3(texture(diffuseMap,defaultIn.TexCoords));

    // Ambient
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * ObjectColor;
    
    // Diffuse 
    vec3 norm = normalize(defaultIn.Normal);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor * ObjectColor;
    
    // Specular
    float specularStrength = texture(specularMap,defaultIn.TexCoords).x;
    vec3 viewDir = normalize(viewPos - defaultIn.FragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    // vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(defaultIn.Normal, halfwayDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;  
    
    // 计算阴影

    // 执行透视除法
    vec3 projCoords = defaultIn.FragPosLightSpace.xyz / defaultIn.FragPosLightSpace.w;
    // 变换到[0,1]的范围
    projCoords = projCoords * 0.5 + 0.5;
    // 取得最近点的深度(使用[0,1]范围下的fragPosLight当坐标)
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    // 取得当前片段在光源视角下的深度
    float currentDepth = projCoords.z;
    // 检查当前片段是否在阴影中
    float shadow = currentDepth-0.05 > closestDepth  ? 1.0 : 0.0;    
    vec3 result = ambient +( diffuse + specular)*intensity*(1-shadow);


    color = vec4(vec3(shadow), 1.0f);
} 