#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;

// Input uniform values
uniform sampler2D texture0;

// Output fragment color
out vec4 out_Pixel;

void main()
{       
    vec4 texelColor = texture(texture0, fragTexCoord);

    if (texelColor.a < 0.5) {
        discard;
    }

    out_Pixel = vec4(vec3(gl_FragCoord.z), 1.0);
}