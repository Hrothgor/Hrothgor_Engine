#version 330

// Output fragment color
out vec4 out_Pixel;

// Input uniform values
uniform sampler2D texture0;

void main()
{             
    out_Pixel = vec4(vec3(gl_FragCoord.z), 1.0);
}