#version 330

// Input vertex attributes (from vertex shader)
in vec3 fragPosition;
in vec2 fragTexCoord;
in vec4 fragColor;
in vec3 fragNormal;

// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;
uniform int nbLights;

// Output fragment color
out vec4 out_Pixel;

// NOTE: Add here your custom variables

#define     MAX_LIGHTS              100
#define     LIGHT_DIRECTIONAL       0
#define     LIGHT_POINT             1

struct Light {
    int type;
    vec3 target;
    vec3 position;
    float range;
    vec4 color;
    float intensity;
};

// Input lighting values
uniform Light lights[MAX_LIGHTS];
uniform vec4 ambient;
uniform vec3 viewPos;

void main()
{
    // Texel color fetching from texture sampler
    vec4 texelColor = texture(texture0, fragTexCoord);
    vec3 normal = normalize(fragNormal);
    vec3 viewD = normalize(viewPos - fragPosition);
    vec3 totalDiffuse = vec3(0.0);
    vec3 totalSpecular = vec3(0.0);

    if (texelColor.a < 0.5) {
        discard;
    }

    // NOTE: Implement here your fragment shader code

    for (int i = 0; i < nbLights; i++)
    {
        vec3 toLight = vec3(0.0);
        float intensity = lights[i].intensity;

        if (lights[i].type == LIGHT_DIRECTIONAL)
        {
            toLight = normalize(lights[i].position - lights[i].target);
        }

        if (lights[i].type == LIGHT_POINT)
        {
            float dist = abs(distance(lights[i].position, fragPosition));
            if (dist > lights[i].range)
            {
                continue;
            }
            toLight = normalize(lights[i].position - fragPosition);
            float attenuation = lights[i].range - dist;
            attenuation /= lights[i].range;
            intensity *= attenuation;
        }

        // Diffuse
        float NdotL = dot(normal, toLight);
        float brightness = max(NdotL, 0.0);
        totalDiffuse += lights[i].color.rgb * brightness * intensity;

        // Specular
        float specCo = 0.0;
        if (NdotL > 0.0)
            specCo = pow(max(dot(viewD, reflect(-(toLight), normal)), 0.0), 16.0); // 16 refers to shine
        totalSpecular += specCo * intensity;
    }

    vec4 finalColor = (texelColor * ((colDiffuse + vec4(totalSpecular, 1.0)) * vec4(totalDiffuse, 1.0)));
    finalColor += texelColor * (ambient/10.0) * colDiffuse;

    // Gamma correction
    out_Pixel = pow(finalColor, vec4(1.0/2.2));
}