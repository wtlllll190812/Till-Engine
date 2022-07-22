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
uniform float cutoff;
uniform vec3 spotLightDir;
uniform sampler2D diffuseMap;
uniform sampler2D specularMap;

void main()
{
    float dis = length(lightPos - FragPos);
    vec3 lightDir = normalize(lightPos - FragPos);

    //float t = dot(normalize(spotLightDir),lightDir);
    float intensity = 1.0f;// / (1.0f + 0.09f * dis + 0.032 * dis * dis);

    vec3 ObjectColor = vec3(texture(diffuseMap,TexCoords));

    // Ambient
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * ObjectColor;
    
    // Diffuse 
    vec3 norm = normalize(Normal);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor * ObjectColor;
    
    // Specular
    float specularStrength = texture(specularMap,TexCoords).x;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    // vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(Normal, halfwayDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;  
    
    
    vec3 result = ambient +( diffuse + specular)*intensity;
    color = vec4(result, 1.0f);
} 