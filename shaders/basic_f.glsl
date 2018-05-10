#version 330 core

out vec4 outColor;

uniform vec4 color;
uniform sampler2D albedo;
uniform int hasAlbedo;
uniform sampler2D normal;
uniform int hasNormal;
uniform sampler2D bump;
uniform int hasBump;

uniform vec3 cameraPosition;

in vec3 vNormal;
in vec2 vTexture;
in mat3 TBN;
in vec3 vTangentViewPos;
in vec3 vTangentFragPos;
in vec3 viewPosition;
in vec3 viewDirection;
in vec3 fragPos;

vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir)
{ 
    float height =  texture(bump, texCoords).r;
    vec2 p = viewDir.xy / viewDir.z;
    return texCoords - p * height * 0.01;
} 

float calcFresnel(vec3 cameraPosition, vec3 normal, float factor)
{
    vec3 dir = normalize(fragPos - cameraPosition);
    return dot(-dir, normal) * factor;
}

void main()
{
    vec3 lightDir = normalize(vec3(0, -1, 0.5));

    float fresnel = calcFresnel(viewPosition, vNormal, 1);

    vec2 texCoords;
    if (hasBump == 1)
    {
        vec3 viewDir = normalize(vTangentViewPos - vTangentFragPos);
        texCoords = ParallaxMapping(vTexture, viewDir);
        // if(texCoords.x > 1.0 || texCoords.y > 1.0 || texCoords.x < 0.0 || texCoords.y < 0.0)
        //     discard;
    }
    else
    {
        texCoords = vTexture;
    }

    vec3 tNormal;
    if (hasNormal == 1)
    {
        tNormal = normalize(TBN * (texture(normal, texCoords).rgb * 2.0 - 1.0));
        // tNormal = normalize(tNormal * 2.0 - 1.0);   
        // tNormal = normalize(TBN * tNormal);
    }
    else
    {
        tNormal = vNormal;
    }
    float l = max(dot(tNormal, -lightDir), 0.15f);
    if (hasAlbedo == 1)
    {
         vec4 texColor = texture(albedo, texCoords);
        outColor = (color * texColor) * vec4(l, l, l, 1.0f);
    }
    else
    {
        outColor = color * vec4(l, l, l, 1.0f);
    }

    // outColor = texture(normal, texCoords); //vec4(fresnel, fresnel, fresnel, 1);
}