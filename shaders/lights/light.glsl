in vec3 viewPosition;
in vec3 viewDirection;
in vec3 fragPos;

uniform float specular_power;
uniform float specular_intensity;

uniform samplerCube envMap;

uniform sampler2D shadowMap;

struct Light
{
    float   intensity;
    vec4    color;
};

struct DirectionalLight
{
    Light   light;
    vec3    direction;
};

vec4 calcLight(Light light, vec3 direction, vec3 normal)
{
    float diffuse_factor = dot(normal, direction);
    vec4 diffuse_color = vec4(0.0);
    vec4 specular_color = vec4(0.0);

    if (diffuse_factor > 0)
       diffuse_color = vec4(light.color.rgb * light.intensity * diffuse_factor, 1.0);

    vec3 direction_to_eye = normalize(viewPosition - fragPos);
    vec3 reflection_direction = normalize(reflect(-direction, normal));

    float specular_factor = pow(dot(direction_to_eye, reflection_direction), specular_power) * diffuse_factor;

    if (specular_factor > 0)
        specular_color = vec4(light.color.rgb * specular_intensity * specular_factor, 1.0);

    return  vec4(diffuse_color.rgb + specular_color.rgb, 1);
}

vec4 calcDirectionalLight(DirectionalLight light, vec3 normal)
{
    return calcLight(light.light, light.direction, normal);
}

float calcBlurredShadow(vec4 lightPosition, int size)
{
    float result = 0.0;

    vec3 coords = lightPosition.xyz / lightPosition.w * 0.5 + 0.5;

    float currentDepth = coords.z;
    float texelSize = 1.0 / 2048.0;

    vec3 clipA = coords - size * texelSize;
    vec3 clipB = coords + size * texelSize;
    if (clipA.z > 1.0 || clipB.z > 1.0)
        return 1;

    for (int x = 0; x <= size * 2 + 1; x++)
    {
        for (int y = 0; y <= size * 2 + 1; y++)
        {
            vec2 offset = vec2(x - size, y - size);
            float closestDepth = texture(shadowMap, coords.xy + offset * texelSize).r;
            result += currentDepth - 0.002 < closestDepth ? 1.0 : 0.0;
        }
    }

    return result / ((size * 2 + 1) * (size * 2 + 1));
}

float calcShadow(vec4 lightPosition)
{
    vec3 projCoords = lightPosition.xyz / lightPosition.w * 0.5 + 0.5;

    float closestDepth = texture(shadowMap, projCoords.xy).r;
    float currentDepth = projCoords.z;

    if (currentDepth > 1.0)
        return 1;

    if (currentDepth > closestDepth + 0.001)
        return 0;
    return 1;
}

vec2 ParallaxMapping(sampler2D bump, vec2 texCoords, vec3 viewDir)
{
    float height =  texture(bump, texCoords).r;
    vec2 p = viewDir.xy / viewDir.z * (height * 1.0);
    return texCoords - p;
}

float calcFresnel(vec3 cameraPosition, vec3 normal, float factor)
{
    vec3 dir = normalize(fragPos - cameraPosition);
    float result = dot(-dir, normal) * factor;
    return 1.0 - clamp(result, 0, 1);
}

vec4 calcPBR(vec4 color, vec3 normal, float roughtness, float metalness)
{
    float rFactor = roughtness * 4.0;
    float mFactor = metalness;

    vec3 reflection = reflect(-normalize(fragPos - viewPosition), normal);
    vec4 env = textureLod(envMap, reflection, rFactor);

    float fresnel = clamp(calcFresnel(viewPosition, normal, 1.0 + roughtness * 2.0), 0, 1) * 0.8;
    float fresnelRougthness = mix(fresnel, fresnel * 0.5, roughtness);

    vec4 reflectiveColor = color * (0.5 + roughtness * 0.48) + env * (0.5 - roughtness * 0.48);

    vec4 fresnelReflection = mix(reflectiveColor, env, fresnelRougthness);
   
    // vec4 metalic = fresnelReflection * fresnel * 0.5;

    return fresnelReflection;
}