#version 330

// Input vertex attributes
in vec3 vertexPosition;
in vec2 vertexTexCoord;

// Input uniform values
uniform mat4 mvp;

// uniform vec2 texOffset1;
// uniform vec2 texOffset2;
// uniform int numberOfRows;

uniform float elapsedTime;
uniform float lifeLength;
uniform int numberOfRows;

// Output vertex attributes (to fragment shader)
out vec2 fragTexCoord1;
out vec2 fragTexCoord2;
out float blend;

// NOTE: Add here your custom variables

void main()
{
    float lifeFactor = elapsedTime / lifeLength;
    int stageCount = int(pow(2, numberOfRows));
    float atlasProgression = lifeFactor * stageCount;
    int index1 = int(floor(atlasProgression));
    int index2 = index1;
    if (index1 < stageCount - 1)
        index2 = index1 + 1;
    blend = atlasProgression - float(index1);
    
    int column1 = index1 % numberOfRows;
    int row1 = index1 / numberOfRows;
    vec2 texOffset1 = vec2(float(column1) / float(numberOfRows), float(row1) / float(numberOfRows));

    int column2 = index2 % numberOfRows;
    int row2 = index2 / numberOfRows;
    vec2 texOffset2 = vec2(float(column2) / float(numberOfRows), float(row2) / float(numberOfRows));

    vec2 texCoord = vertexTexCoord / numberOfRows;

    // Send vertex attributes to fragment shader
    fragTexCoord1 = texCoord + texOffset1;
    fragTexCoord2 = texCoord + texOffset2;

    // Calculate final vertex position
    gl_Position = mvp * vec4(vertexPosition.xyz, 1.0);
}
