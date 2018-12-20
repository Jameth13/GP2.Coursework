#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;

uniform vec3 lightColor;
uniform vec3 lightPosition;

uniform sampler2D sampler;

void main()
{
	//Ambient
	float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

	//Diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPosition - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	//Result
	vec3 lighting = (ambient + diffuse);
	FragColor = vec4(lighting, 1.0) * texture2D(sampler, TexCoord);
}
