#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord1;
in vec2 fragTexCoord2;

// Input uniform values
uniform sampler2D texture0;
uniform float blend;

// Output fragment color
out vec4 out_Pixel;

// NOTE: Add here your custom variables

void main(void)
{
    vec4 color1 = texture(texture0, fragTexCoord1);
    vec4 color2 = texture(texture0, fragTexCoord2);

	out_Pixel = mix(color1, color2, blend);
}