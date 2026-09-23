//#shader vertex
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;

out vec2 TexCoords;
out vec3 Normal;
out vec3 FragPos;

out vec3 Tangent;
out vec3 Bitangent;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));

    Normal = mat3(transpose(inverse(model))) * aNormal;

    Tangent = mat3(transpose(inverse(model))) * aTangent;
    Bitangent = mat3(transpose(inverse(model))) * aBitangent;

    TexCoords = aTexCoords;

    gl_Position =projection *view *vec4(FragPos, 1.0);
}


//#shader fragment
#version 330 core

out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

in vec3 Tangent;
in vec3 Bitangent;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_normal1;
uniform sampler2D texture_specular1;

uniform vec3 viewPos;

uniform vec3 dirLightDirection;
uniform vec3 dirLightColor;


uniform vec3 pointLightPosition;
uniform vec3 pointLightColor;

void main()
{
    vec3 color = texture(texture_diffuse1, TexCoords).rgb;

    vec3 normalMap = texture(texture_normal1, TexCoords).rgb;

    normalMap = normalMap * 2.0 - 1.0;

    vec3 T = normalize(Tangent);
    vec3 B = normalize(Bitangent);
    vec3 N0 = normalize(Normal);

    mat3 TBN = mat3(T, B, N0);

    vec3 N = normalize(TBN * normalMap);

    float specular = texture(texture_specular1, TexCoords).r;

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 dir =normalize(-dirLightDirection);

    float diff = max(dot(N, dir), 0.0);

    vec3 diffuse = diff * dirLightColor * color;

    vec3 halfwayDir = normalize(dir + viewDir);

    float spec = pow(max(dot(N, halfwayDir), 0.0),32.0);

    vec3 specularColor = spec * specular * dirLightColor;

    vec3 pointDir = normalize(pointLightPosition - FragPos);
    float pointDiff = max(dot(N, pointDir), 0.0);
    float distance = length(pointLightPosition - FragPos);

    float attenuation = 1.0 / ( 1.0 + 0.09 * distance + 0.032 * distance * distance);

    vec3 pointDiffuse = pointDiff * pointLightColor * color * attenuation;

    vec3 pointHalfway = normalize(pointDir + viewDir);

    float pointSpec = pow( max(dot(N, pointHalfway), 0.0), 32.0);

    vec3 pointSpecular = pointSpec * specular * pointLightColor * attenuation;

    vec3 ambient = 0.15 * color;

    vec3 result = ambient + diffuse + specularColor + pointDiffuse + pointSpecular;

    FragColor = vec4(result, 1.0);
}