#version 330

// Input vertex attributes
in vec3 vertexPosition;
in vec2 vertexTexCoord;

// Input uniform values
uniform mat4 matModel;
uniform mat4 lightSpaceMatrix;

// Output vertex attributes (to fragment shader)
out vec2 fragTexCoord;

void main()
{
    // Send vertex attributes to fragment shader
    fragTexCoord = vertexTexCoord;

    // Calculate final vertex position
	gl_Position = lightSpaceMatrix * matModel * vec4(vertexPosition, 1.0);
}