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

    float specular_factor = pow(dot(direction_to_eye, reflection_direction), specular_power) * clamp(0, 1, diffuse_factor);

    if (specular_factor > 0)
        specular_color = vec4(light.color.rgb * specular_intensity * specular_factor, 1.0);

    return  vec4(diffuse_color.rgb + specular_color.rgb, 1);
}

vec4 calcDirectionalLight(DirectionalLight light, vec3 normal)
{
    return calcLight(light.light, light.direction, normal);
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
    vec3 reflection = reflect(-normalize(fragPos - viewPosition), normal);
    vec4 env = textureLod(envMap, reflection, roughtness);

    float fresnel = calcFresnel(viewPosition, normal, 1) * 0.4;
    vec4 fresnelReflection = mix(color, env * 0.5, fresnel);

    return fresnelReflection;
}