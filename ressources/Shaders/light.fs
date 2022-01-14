#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoords;
in vec4 fragColor;
in vec3 surfaceNormal;
in vec3 toCameraVector;
in vec3 worldPosition;

// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;

// Output fragment color
out vec4 out_Pixel;

// NOTE: Add here your custom variables

#define     MAX_LIGHTS              4
#define     LIGHT_DIRECTIONAL       0
#define     LIGHT_POINT             1

struct Light {
    int enabled;
    int type;
    vec3 position;
    vec3 target;
    vec4 color;
};

// Input lighting values
uniform Light lights[MAX_LIGHTS];

void main(void)
{
    vec3 lightDiffuse = vec3(0.0);
    vec3 specular = vec3(0.0);

    vec3 unitSurfaceNormal = normalize(surfaceNormal);
    vec3 unitToCameraVector = normalize(toCameraVector);

    for (int i = 0; i < MAX_LIGHTS; i++)
    {
        if (lights[i].enabled == 1)
        {
            vec3 unitToLightVector = vec3(0.0);

            if (lights[i].type == LIGHT_DIRECTIONAL)
            {
                unitToLightVector = -normalize(lights[i].target - lights[i].position);
            }

            if (lights[i].type == LIGHT_POINT)
            {
                unitToLightVector = normalize(lights[i].position - worldPosition);
            }

            float NormalLightDot = dot(unitSurfaceNormal, unitToLightVector);
            float brightness = max(NormalLightDot, 0.1);
            lightDiffuse += brightness * lights[i].color.rgb;


            vec3 lightDirection = -unitToLightVector;
            vec3 reflectedLightDirection = reflect(lightDirection, unitSurfaceNormal);

            float specularFactor = dot(reflectedLightDirection, unitToCameraVector);
            specularFactor = max(specularFactor, 0.0);
            vec3 finalSpecular = pow(specularFactor, 16.0) * lights[i].color.rgb;
            specular += finalSpecular;
        }
    }

    out_Pixel = vec4(lightDiffuse, 1.0) * (texture(texture0, fragTexCoords) * colDiffuse * fragColor) + vec4(specular, 1.0);
}
