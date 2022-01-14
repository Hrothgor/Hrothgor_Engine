#version 330

// Input vertex attributes
in vec3 vertexPosition;
in vec2 vertexTexCoord;

// Input uniform values
uniform mat4 mvp;
uniform vec2 texOffset1;
uniform vec2 texOffset2;
uniform int numberOfRows;

// Output vertex attributes (to fragment shader)
out vec2 fragTexCoord1;
out vec2 fragTexCoord2;

// NOTE: Add here your custom variables

void main()
{
    vec2 texCoord = vertexTexCoord / numberOfRows;

    // Send vertex attributes to fragment shader
    fragTexCoord1 = texCoord + texOffset1;
    fragTexCoord2 = texCoord + texOffset2;

    // Calculate final vertex position
    gl_Position = mvp * vec4(vertexPosition.xyz, 1.0);
}
