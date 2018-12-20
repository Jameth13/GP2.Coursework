#version 330 core

in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D sampler;

void main()
{
	FragColor = vec4(1.1, 1.1, 1.1, 1.0) * texture2D(sampler, TexCoord);
}
