#version 330 core
out vec4 fragColor;

in PBROut {
    vec3 FragPos;
    vec2 TexCoords;
    vec3 Normal;
    vec4 FragPosLightSpace;
    mat3 TBN;
} pbrIn;

// lights
layout(std140)uniform LightData
{
    vec3 lightDir; 
    vec3 lightColor;
    vec3 viewPos;
};

// material parameters
uniform vec3  albedo;
uniform float metallic=0.3;
uniform float roughness=0.3;
uniform float ao=1;

const float PI = 3.14159265359;


float CalculateD(vec3 N, vec3 H, float roughness)
{
    float a2=roughness*roughness;
    float NdotH=max(dot(N,H),0.0);
    float NdotH2=NdotH*NdotH;

    float denom=(NdotH2*(a2-1.0)+1.0);
    denom=PI*denom*denom;
    return a2/denom;
}

vec3 CalculateF(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}  

float GeometrySchlickGGX(float NdotV, float k)
{
    float nom   = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return nom / denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float k)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx1 = GeometrySchlickGGX(NdotV, k);
    float ggx2 = GeometrySchlickGGX(NdotL, k);

    return ggx1 * ggx2;
}

void main()
{       
    vec3 nNormal=normalize(pbrIn.Normal);
    vec3 nLightDir=normalize(lightDir);
    vec3 nViewDir=normalize(viewPos-pbrIn.FragPos);

    vec3 halfDir=normalize(nViewDir+nLightDir);
    //反射部分
    vec3 lambert=albedo/PI;
    //折射部分
    vec3 cookTorrance;
    //计算法线分布函数
    float D=CalculateD(nNormal,halfDir,roughness);
    //计算菲涅尔方程
    vec3 F0 = vec3(0.04); 
    F0      = mix(F0, albedo, metallic);
    vec3 F=CalculateF(max(dot(halfDir, nViewDir), 0.0), F0);
    //几何函数
    float G   = GeometrySmith(nNormal, nViewDir, nLightDir, roughness);      


    vec3 kS = F;
    vec3 kD = vec3(1.0) - kS;
    kD *= 1.0 - metallic;   



    vec3 nominator    = D * G * F;
    float denominator = 4.0 * max(dot(nNormal, nViewDir), 0.0) * max(dot(nNormal, nLightDir), 0.0) + 0.001; 
    vec3 specular     = nominator / denominator;
   
    float NdotL = max(dot(nNormal, nLightDir), 0.0); 
    vec3 Lo = (kD * albedo / PI + specular) * NdotL*lightColor;

    vec3 ambient = vec3(0.03) * albedo * ao;
    vec3 color = ambient + Lo;
    color = color / (color + vec3(1.0));
    color = pow(color, vec3(1.0/2.2));  

    fragColor=vec4(color,1.0);
}  