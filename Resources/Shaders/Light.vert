#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;

out vec2 TexCoord;

uniform mat4 vp;
uniform mat4 m;

void main()
{
    gl_Position = vp * m * vec4(position, 1.0);
	TexCoord = texCoord;
}
