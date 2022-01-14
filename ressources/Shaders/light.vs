#version 330

// Input vertex attributes
in vec3 vertexPosition;
in vec2 vertexTexCoord;
in vec4 vertexColor;
in vec3 vertexNormal;

// Input uniform values
uniform mat4 matView;
uniform mat4 matProjection;
uniform mat4 matModel;

// Output vertex attributes (to fragment shader)
out vec2 fragTexCoords;
out vec4 fragColor;
out vec3 surfaceNormal;
out vec3 toCameraVector;
out vec3 worldPosition;

// NOTE: Add here your custom variables

void main()
{
    vec4 positionXYZW = matModel * vec4(vertexPosition, 1.0);

    // Calculate final vertex position
    gl_Position = matProjection * matView * positionXYZW;

    // Send vertex attributes to fragment shader
    worldPosition = positionXYZW.xyz;
    fragTexCoords = vertexTexCoord;
    fragColor = vertexColor;
    surfaceNormal = (matModel * vec4(vertexNormal, 0.0)).xyz;
    toCameraVector = (inverse(matView) * vec4(0,0,0,1)).xyz - positionXYZW.xyz;

}
